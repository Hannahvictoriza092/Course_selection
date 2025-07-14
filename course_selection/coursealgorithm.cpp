#include "coursealgorithm.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <algorithm>
#include <queue>
#include <bitset>


//构造函数
CourseAlgorithm::CourseAlgorithm(QObject *parent) : QObject(parent), totalCredits(0)
{
    semesterCourses.resize(8); // 初始化8个学期
}

//生成课程安排
QJsonObject CourseAlgorithm::genSimSchedule(const QJsonObject &courseData, int creditLimit) //最终课程安排只是，依赖于总学分
{
    // 重置状态
    courseMap.clear();
    classMap.clear();
    classDetail.clear();
    semesterCourses.assign(8, QVector<QString>());
    totalCredits = 0;

    // 初始化课程数据
    if (!initializeCourseData(courseData)) { //如果不行
        return QJsonObject(); //空对象
    }

    // 拓扑排序处理先后关系处理topoQueue
    if (!topologicalSort()) {
        qWarning() << "课程先修关系存在循环依赖，无法生成选课方案";
        return QJsonObject();
    }

    // 选择课程以不冲突
    
    if (!simplesSelect(0,0,creditLimit)) { //是否够学分安排
        qWarning() << "无法选择足够的课程以满足学分要求";
        return QJsonObject();
    }

    // 构建选课方案JSON
    return buildScheduleJson();
}

bool CourseAlgorithm::initializeCourseData(const QJsonObject &courseData) //处理courseMap、classMap，所有的信息已经填充上车了
{
    if (!courseData.contains("courses") || !courseData["courses"].isArray()) {
        return false;
    }
    //单纯先填充所有课程名，然后每个课程下面的各种time、前驱什么的再填充
    QJsonArray courses = courseData["courses"].toArray();
    for (const auto &courseVal : courses) {
        QJsonObject courseObj = courseVal.toObject();
        CourseInfo course;
        course.id = courseObj["id"].toString();
        course.name = courseObj["name"].toString();
        course.credit = courseObj["credit"].toInt();
        if(courseObj["semester"]=="spring"){
                course.semester=0; //偶数学期
        }
        else course.semester=1; //奇数学期
        course.required = courseObj["required"].toBool();
        course.classes = courseObj["classes"].toArray();

        // 解析前置课程
        QJsonArray prereqs = courseObj["prerequisites"].toArray();
        for (const auto &prereqVal : prereqs) {
            course.prerequisites.insert(prereqVal.toString());
        }

        courseMap[course.id] = course;

        // 解析上课时间信息
        QVector<ClassInfo> classInfos;
        for (const auto &classVal : course.classes) {
            QJsonObject classObj = classVal.toObject();
            ClassInfo classInfo;
            classInfo.id = classObj["id"].toString();
            classInfo.teacher = classObj["teacher"].toString();

            QJsonObject timeObj = classObj["time"].toObject();
            classInfo.weeks = timeObj["weeks"].toInt();

            QJsonArray timesArray = timeObj["times"].toArray();
            for (const auto &timeVal : timesArray) {
                classInfo.times.append(timeVal.toInt());
            }
            classDetail[classInfo.id]=classInfo;
            classInfos.append(classInfo);
        }
        //同一个课程对应这些教学班列表
        classMap[course.id] = classInfos;
    }

    return true;
}

//对topoQueue进行初始化
bool CourseAlgorithm::topologicalSort() 
{
    //先把拓扑排序给清空
    topoQueue.clear();

    QMap<QString, int> inDegree;//入度
    QMap<QString, QVector<QString>> adjList; //邻接表<节点，邻居们>
    // 初始化入度和邻接表
    for (const auto &course : courseMap) {  
        inDegree[course.id] = course.prerequisites.size(); //入度数量（得到前缀数量）
        for (const auto &prereq : course.prerequisites) { //根据入度构造邻接表
            adjList[prereq].append(course.id);
        }
    }

    // 拓扑排序队列
    std::queue<QString> q;
    for (const auto &entry : inDegree.toStdMap()) { //Qmap变成标准map就可以用for-each
        if (entry.second == 0) { //入度变成0,可以处理——放进q
            q.push(entry.first);
        }
    }

    //进入q的只有indegree==0
    while (!q.empty()) {
        QString u = q.front();
        q.pop();
        topoQueue.append(u);

        for (const auto &v : adjList[u]) { //处理后继的入度减一
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v); //记得减完以后检查0入度
            }
        }
    }
    // 检查是否存在循环依赖
    if (topoQueue.size() != courseMap.size()) { //是否所有点都被处理到
        return false;
    }
   return true;
}


//简单选课，需要进行回溯，
bool CourseAlgorithm::simplesSelect(int courseIndex,int curCredits,int Limit){

    
    // 终止条件1：学分已达标
    if (curCredits >= Limit) 
        return true;
    
    // 终止条件2：所有课程处理完毕仍未达标
    if (courseIndex >= topoQueue.size()) 
        return false;
    QString courseId = topoQueue[courseIndex];
    const CourseInfo &course = courseMap[courseId];
    

    // 计算前置课程的最晚学期,如果前置课程被跳过了，那一定是这个也会失败，选不了
    int PossibleSemester;
    int lastPre=0;
    //前置约束，根据已经安排好的前置来安排自己
    for (const QString &prereq : course.prerequisites) {
        int prereqSemester = findCourseSemester(prereq);
        //前置课程没有上完，这个课不能上，必须跳过，进入下一个递归看看能不能凑够学分，仍不能，说明此路不通
        if(prereqSemester==-1) return simplesSelect(courseIndex + 1, curCredits,Limit);
        lastPre = qMax(lastPre, prereqSemester);
    }
    //调整学期到可以开始的起点
    if((lastPre+1)%2==course.semester)//满足处于该学期的奇偶性
    {
        PossibleSemester=lastPre+1;
    }
    else PossibleSemester=lastPre+2;
     // 遍历每个可能合适的学期
    for (int sem = PossibleSemester; sem < 8 ; sem+=2) { //如果时间冲突了就是换下一个学年，不会进入下一轮递归
        for(const ClassInfo& classInfo:classMap[courseId]){
            //先判断这门课所有的排课，这个学期是否有可以安排的
            if(!hasTimeConflict(sem,classInfo)){  //没有时间冲突
                //这门课的这个老师的课暂时加入没问题，
                qDebug() << "尝试安排课程" << classInfo.id << "到学期" << sem;
                semesterCourses[sem].append(classInfo.id);//
                // 递归尝试下一门课
                if (simplesSelect(courseIndex + 1, curCredits+2*courseMap[courseId].credit,Limit)) //如果后面的路径成功，那就直接return true
                        return true;
                //后面的路径失败，就进行回溯
                qDebug() << "撤回课程" << classInfo.id << "从学期" << sem;
                semesterCourses[sem].removeLast(); //撤回这个老师的课，等下个老师
            }
            //继续迭代得到下一个老师的课
            
    }
    // 只有这门课后面路怎么都走不通或者时间有矛盾才会走到这里，直接跳过这门课，看看之后的路通不通
      if(simplesSelect(courseIndex + 1, curCredits,Limit)){
        return true;//如果跳过这门课以后成功了，那就直接return 不必再递归了，如果失败了，哈哈哈，你得再换一个学期
      }
}
        return false;//到这一步，一定是失败彻底了
}

//考虑必修和选修
bool CourseAlgorithm::compulsoryBasedSelect(int courseIndex,int curCredits,int Limit) 
{
    // 终止条件1：学分达标
    if (curCredits >= Limit) return true;
    
    // 终止条件2：所有课程处理完毕
    if (courseIndex >= topoQueue.size()) return false;

    QString courseId = topoQueue[courseIndex];
    const CourseInfo &course = courseMap[courseId];

    // ===== 分层处理：必修课优先 =====
    if (course.required) {
        // 情况1：尝试安排必修课
        if (tryArrangeCourse(courseId, courseIndex, curCredits, Limit)) {
            return true;
        }
        // 必修课必须安排，不能跳过
        return false; 
    } else {
        // 情况2：选修课可跳过
        // 先尝试安排
        if (tryArrangeCourse(courseId, courseIndex, curCredits, Limit)) {
            return true;
        }
        // 再尝试跳过
        return compulsoryBasedSelect(courseIndex + 1, curCredits, Limit);
    }
}

bool CourseAlgorithm::tryArrangeCourse(const QString& courseId, int courseIndex, int& curCredits, int Limit) {
    const CourseInfo &course = courseMap[courseId];
    int earliestSem = 0;
    
    // 检查前置课程
    for (const QString &prereq : course.prerequisites) {
        int prereqSem = findCourseSemester(prereq);
        if (prereqSem == -1) return false; // 前置未完成
        earliestSem = qMax(earliestSem, prereqSem + 1);
    }

    // 调整学期奇偶性
    if ((earliestSem % 2) != (course.semester % 2)) earliestSem++;

    // 尝试每个可能的学期
    for (int sem = earliestSem; sem < 8; sem += 2) {
        for (const ClassInfo &classInfo : classMap[courseId]) {
            if (!hasTimeConflict(sem, classInfo)) {
                // 做出选择
                semesterCourses[sem].append(courseId);

                curCredits += course.credit;

                // 递归
                if (compulsoryBasedSelect(courseIndex + 1, curCredits, Limit)) {
                    return true;
                }

                // 回溯撤销
                semesterCourses[sem].removeLast();

                curCredits -= course.credit;
            }
        }
    }
    return false;
}

int CourseAlgorithm::calculateTotalCredits() //所有课的学分
{
    int total = 0;
    for (const auto &semester : semesterCourses) {
        for (const auto &courseId : semester) {
            if (courseMap.contains(courseId)) {
                total += courseMap[courseId].credit;
            }
        }
    }
    return total;
}

QJsonObject CourseAlgorithm::buildScheduleJson() //建立新的Json文件
{
    QJsonObject result;
    QJsonArray scheduleArray;

    for (int semester = 0; semester < 8; ++semester) {
        for (const auto &courseId : semesterCourses[semester]) { //每学期的课
            if (!courseMap.contains(courseId)) continue; //避免课程错误

            QJsonObject scheduleItem;
            scheduleItem["course_id"] = courseId;
            // 简单起见，选择第一个班级
            if (!classMap[courseId].isEmpty()) {
                scheduleItem["class_id"] = classMap[courseId].first().id; //选择第一个班级的id
            } else {//若此种课程没有开课，就把这门课的class_id设为null
                scheduleItem["class_id"] = QJsonValue::Null;
            }
            scheduleItem["semester"] = semester;
            scheduleArray.append(scheduleItem);
            //这一门课设置成功，罐装进入scheduleArray
        }
    }

    result["schedule"] = scheduleArray;
    return result;
}


//辅助函数，用来判断是否冲突
bool  CourseAlgorithm:: hasTimeConflict(int semester, const ClassInfo &newClass) { //判断这个课程的有没有可以加入不冲突的课程
    for (const auto &existingClass : semesterCourses[semester]) {//对于当前已经放进当前学期的
        // 1. 检查周次是否重叠
        if ((classDetail[existingClass].weeks & newClass.weeks) == 0) {
            continue; // 无周次重叠，跳过
        }

        // 2. 检查具体时间是否重叠
        for (int day = 0; day < 7; ++day) {
            // 如果某天至少有一节课重叠（按位与不为0）
            if ((classDetail[existingClass].times[day] & newClass.times[day]) != 0) {
                return true; // 冲突！
            }
        }
    }
    return false; // 无冲突
}

// 查找课程已被安排在哪个学期
int CourseAlgorithm::findCourseSemester(const QString &courseId) {
    for (int sem = 0; sem < 8; ++sem) {
        if (semesterCourses[sem].contains(courseId)) {
            return sem;
        }
    }
    return -1; // 未找到
}

//输入课程数据和学分上限，还有一个必修选修，输出生成的课程表
QJsonObject CourseAlgorithm:: genCompulsorySchedule(const QJsonObject &courseData, int creditLimit){
    // 重置状态
    courseMap.clear();
    classMap.clear();
    classDetail.clear();
    semesterCourses.assign(8, QVector<QString>());
    totalCredits = 0;

    // 初始化课程数据
    if (!initializeCourseData(courseData)) { //如果不行
        return QJsonObject(); //空对象
    }

    // 拓扑排序处理先后关系处理topoQueue
    if (!topologicalSort()) {
        qWarning() << "课程先修关系存在循环依赖，无法生成选课方案";
        return QJsonObject();
    }

    // 选择课程以不冲突
    
    if (!compulsoryBasedSelect(0,0,creditLimit)) { //是否够学分安排
        qWarning() << "无法选择足够的课程以满足学分要求";
        return QJsonObject();
    }

    // 构建选课方案JSON
    return buildScheduleJson();
}