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
    
    int totalCredits=simplesSelect(creditLimit);  //是否够学分安排
        
    if(totalCredits<creditLimit) 
    {qWarning() << "无法选择足够的课程以满足学分要求"<<totalCredits;
        return QJsonObject();}

    // 构建选课方案JSON
    qWarning() << "已经选择足够的课程以满足学分要求:"<<totalCredits;
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
        course.classes = courseObj["offerings"].toArray();

        // 解析前置课程
        QJsonArray prereqs = courseObj["prerequisites"].toArray();
        for (const auto &prereqVal : prereqs) {
            course.prerequisites.insert(prereqVal.toString());
        }

        courseMap[course.id] = course;

        // 解析上课时间信息
        QVector<ClassInfo> classInfos;
        for (const auto &classVal : course.classes) {
            //qWarning()<<course.name <<"有排课！！！";
            QJsonObject classObj = classVal.toObject();
            ClassInfo classInfo;
            //排课id、老师、课程id
            classInfo.id = classObj["id"].toString();
            classInfo.teacher = classObj["teacher"].toString();
            classInfo.courseID=course.id;
            //时间和周
            QJsonObject timeObj = classObj["time"].toObject();
            QJsonArray timesArray = timeObj["times"].toArray();
            for (const auto &timeVal : timesArray) {
                classInfo.times.append(timeVal.toInt());
            }
            classInfo.weeks = timeObj["weeks"].toInt();
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


//简单选课
int CourseAlgorithm::simplesSelect(int min_credits){
        int total_credits=0;
        for(QString courseID:topoQueue){
            qWarning()<<"尝试排课:"<<courseMap[courseID].name;
            bool is_finished=false;//是否这个课安排好了
            if(total_credits >= min_credits){
                break;
            }
            int min_semester = 0;
            bool all_pre_ok = true;
            if(courseMap[courseID].prerequisites.empty()) {qWarning()<<courseMap[courseID].name<<"没有前驱";}
            for (QString prereq_id :courseMap[courseID].prerequisites){//前驱结束
                int sem_for_pre=findCourseSemester(prereq_id);
                qWarning()<<"有前驱"<<courseMap[prereq_id].name<<"安排在"<<sem_for_pre<<"学期";
                if(sem_for_pre!=-1)
                    min_semester = qMax(min_semester, sem_for_pre + 1);
                else
                    {
                        all_pre_ok=false;
                        break;
                    }
                }
                    
                if(all_pre_ok==false || min_semester>8) {qWarning()<<"前驱没有被上";continue;}//先修课未完，或者超出学期的就是可以滚
                bool is_arranged=false;
                 for (int semester=min_semester; semester<8;semester++){
                        //检查学期开课季节（Autumn/Spring）
                           if (!((semester % 2 == 1)^courseMap[courseID].semester)) //不同，就跳过
                                continue;
                    //遍历课程的所有班级
                    qWarning()<<"救命这门课下面的排课有"<<classMap[courseID].size()<<"个";
                    for( ClassInfo eachClass:classMap[courseID]){
                           QString classID= eachClass.id;
                           //可能会有禁止的班要跳过
                            qWarning()<<"找教学班："<<eachClass.teacher;
                          if(hasTimeConflict(semester,eachClass)){ 
                             qWarning()<<"有冲突换一个老师看看";
                              continue;//这个老师的课有冲突，那就重新来换一个老师
                          }
                          //加入课程
                         semesterCourses[semester].append(classID);
                         //建立映射
                         Course_in_sem[courseID]=semester;
                         total_credits += courseMap[courseID].credit;
                         qWarning()<<"成功加入"<<courseMap[courseID].name<<" 老师："<<eachClass.teacher;
                         is_arranged=true;
                         is_finished=true;
                         break;
                    }
                    if(is_arranged) break;
            }
            if(is_finished) continue;;
        }
        return total_credits;
}

//考虑优先级
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

    for (int semester =0; semester <8; ++semester) {
        for (const auto &classID : semesterCourses[semester]) { //每学期的课
        //    if (!courseMap.contains(courseId)) continue; //避免课程错误
            QJsonObject scheduleItem;
            ClassInfo& ThisClass=classDetail[classID];
            scheduleItem["course_id"] = ThisClass.courseID;
            scheduleItem["class_id"] =  ThisClass.id;
            scheduleItem["semester"] = semester;
            scheduleItem["teacher"] =  ThisClass.teacher;
            scheduleItem["week"] = semester+1;//从0开始
            scheduleItem["name"] = courseMap[ThisClass.id].name;
            scheduleItem["required"]=courseMap[ThisClass.id].required;
            scheduleItem["credits"] = courseMap[ThisClass.id].credit;
            QJsonArray jsonArray;
            for (int time :ThisClass.times) {
                    jsonArray.append(time);
                }
            scheduleItem["times"] = jsonArray; // 使用 "times" 作为键名
            //这一门课设置成功，罐装进入scheduleArray
            scheduleArray.append(scheduleItem);
        }
    }

    result["schedule"] = scheduleArray;
    return result;
}

//辅助函数，用来判断是否冲突
bool  CourseAlgorithm:: hasTimeConflict(int semester, const ClassInfo &newClass) { //判断这个课程的有没有可以加入不冲突的课程
    for (QString &existingClassID : semesterCourses[semester]) {//对于当前已经放进当前学期的
        // 1. 检查周次是否重叠
        if ((classDetail[existingClassID ].weeks & newClass.weeks) == 0) {
            continue; // 无周次重叠，跳过
        }
        
        // 2. 检查具体时间是否重叠
        for (int day = 0; day < 7; ++day) {
            // 如果某天至少有一节课重叠（按位与不为0）
            if ((classDetail[existingClassID ].times[day] & newClass.times[day]) != 0) {
                return true; // 冲突！
            }
        }
    }
    return false; // 无冲突
}

// 查找课程已被安排在哪个学期
int CourseAlgorithm::findCourseSemester(const QString &courseId) {
    if(Course_in_sem.find(courseId)!=Course_in_sem.end()) return Course_in_sem[courseId];
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

//考虑优先级的拓扑排序
bool CourseAlgorithm:: topoPriorSort(){
    //填充topoQueue
    topoQueue.clear();
    QMap<QString, int> inDegree;
    QMap<QString, QSet<QString>> graph; // 邻接表：课程 → 后继课程
 
    // 1. 构建图和入度表
    for (const auto &course : courseMap) {
        inDegree[course.id] = 0;
        for (const auto &prereq : course.prerequisites) {
            graph[prereq].insert(course.id);
            inDegree[course.id]++;
        }
    }
 
    // 2. 初始化优先级队列（必修课优先 + 选修课按优先级）
    std::priority_queue<CourseNode> pq;
    for (const auto &course : courseMap) {
        if (inDegree[course.id] == 0) {
            pq.push({course, 0});
        }
    }
 
    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        topoQueue.append(node.course.id);
 
        // 更新后继课程的入度
        for (const auto &nextId : graph[node.course.id]) {
            inDegree[nextId]--;
            if (inDegree[nextId] == 0) {
                pq.push({courseMap[nextId], inDegree[nextId]});
            }
        }
    }
    if(topoQueue.size()<courseMap.size()) return false; //没有完全处理到
    return true;
}