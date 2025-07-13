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
QJsonObject CourseAlgorithm::generateSchedule(const QJsonObject &courseData, int creditLimit) //最终课程安排只是，依赖于总学分
{
    // 重置状态
    courseMap.clear();
    classMap.clear();
    semesterCourses.assign(8, QVector<QString>());
    totalCredits = 0;

    // 初始化课程数据
    if (!initializeCourseData(courseData)) { //如果不行
        return QJsonObject(); //空对象
    }

    // 拓扑排序处理先后关系
    if (!topologicalSort()) { //是否违背
        qWarning() << "课程先修关系存在循环依赖，无法生成选课方案";
        return QJsonObject();
    }

    // 选择课程以满足学分要求
    if (!selectCourses(creditLimit)) { //是否够学分安排
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
                course.semester=1;
        }
        else course.semester=0;
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

            classInfos.append(classInfo);
        }
        //同一个课程对应这些教学班列表
        classMap[course.id] = classInfos;
    }

    return true;
}

bool CourseAlgorithm::topologicalSort() //待修改
{
    int curCredits=0;//当前学分
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

    QVector<QString> result;
    //进入q的只有indegree==0
    while (!q.empty()) {
        QString u = q.front();
        q.pop();
        result.append(u);

        for (const auto &v : adjList[u]) { //处理后继的入度减一
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v); //记得减完以后检查0入度
            }
        }
    }

    

    // 检查是否存在循环依赖
    if (result.size() != courseMap.size()) { //是否所有点都被处理到
        return false;
    }
        /*-----生成的result中的序列已经是所有课程的拓扑排序（不讨论教学班）-------*/

    // 按拓扑顺序将课程分配学期
    for (const QString &courseId : result) {
        const CourseInfo &course = courseMap[courseId];
        
        // 计算前置课程的最晚学期,前置课程一定已经被安排过了
        int earliestPossibleSemester = course.semester;//本来起点就是这样的，上学期0，下学期1
        int lastPre=0;
        for (const QString &prereq : course.prerequisites) {//这门课程的前置们
            int prereqSemester = findCourseSemester(prereq);
            lastPre = qMax(lastPre, prereqSemester);
        }//找到最晚的学期

        // 结合建议学期和前置约束
        
        if (targetSemester < 0 || targetSemester < earliestPossibleSemester) {
            targetSemester = earliestPossibleSemester;
        }

        // 寻找实际可安排的学期（考虑总学分上限和时间冲突，在同一个学期里面的课，周冲撞了，那么就不能天也冲撞）
        bool placed = false;
        for (int sem = targetSemester; sem < 8 && !placed; ++sem) {
            QString classID;
            //先判断时间会不会冲突
            bool classID=canAddCourseToSemester(courseId, sem,classID); //如果能返回一个
            //再判断学分会不会超
            
            if () {
                semesterCourses[sem].append(classID);
                placed = true;
                curCredits+=2*courseMap[can]
            }
        }

        if (!placed) {
            qWarning() << "无法安排课程:" << courseId;
           return false; //就是一个前置完成吧，但是如果已经满足学分
        
        }
    }
    return true;
}

bool CourseAlgorithm::checkTimeConflict(const QString &courseId, const QString &classId, int semester) //待修改，检查冲突逻辑
{
    // 查找要检查的课程的上课时间
    ClassInfo targetClass;
    bool found = false;
    //某一个课程的开课班级情况
    for (const auto &classInfo : classMap[courseId]) {
        if (classInfo.id == classId) { //在这个课程id下面找到了同样的开课id
            targetClass = classInfo;
            found = true;
            break;
        }
    }
    if (!found) return true; // 未找到班级信息，视为冲突

    // 已找到了班级信息，检查该学期已选课程是否有‘时间’冲突
    for (const auto &selectedCourseId : semesterCourses[semester]) { //该学期的这门课！！
        if (selectedCourseId == courseId) continue; //遇到自己就跳过

        for (const auto &classInfo : classMap[selectedCourseId]) { //同一个课程里的所有课
            // 简化的时间冲突检查逻辑
            // 实际应用中需要根据times和weeks字段进行详细的时间冲突判断
            // 这里仅作示例，返回false表示无冲突
            //classInfo里面的week和time都是解析好的
             if (hasTimeConflict(existingClasses, newClass)) {
            return true; // 存在冲突
        }
        }
    }

    return false;
}

bool CourseAlgorithm::selectCourses(int creditLimit) //选修课选择是随机的
{
    // 简单的课程选择逻辑：优先选择必修课，然后选择选修课直到达到学分要求
    QVector<QString> selectedCourses;

    // 先选择所有必修课
    for (const auto &course : courseMap) {
        if (course.required) {
            selectedCourses.append(course.id);
            totalCredits += course.credit;
        }
    }

    // 如果必修课已满足学分要求，直接返回
    if (totalCredits >= creditLimit) {
        return true;
    }

    // 否则添加选修课直到满足学分要求
    for (const auto &course : courseMap) {
        if (!course.required) {
            selectedCourses.append(course.id);
            totalCredits += course.credit;
            if (totalCredits >= creditLimit) {
                break;
            }
        }
    }

    return totalCredits >= creditLimit;
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
        if ((courseMap[existingClass].weeks & newClass.weeks) == 0) {
            continue; // 无周次重叠，跳过
        }

        // 2. 检查具体时间是否重叠
        for (int day = 0; day < 7; ++day) {
            // 如果某天至少有一节课重叠（按位与不为0）
            if ((existingClass.times[day] & newClass.times[day]) != 0) {
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

// 检查课程能否加入某学期,只判断时间冲突
bool CourseAlgorithm::canAddCourseToSemester(const QString &courseId, int semester,QString& classID) {

    // 检查时间冲突
    for (const ClassInfo &classInfo : classMap[courseId]) {
        if (!hasTimeConflict(int semester, classInfo)) {
            return true; // 至少有一个班级无冲突
        }
    }
    return false;
}