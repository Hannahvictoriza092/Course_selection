#include "coursealgorithm.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <algorithm>
#include <queue>
#include <bitset>

CourseAlgorithm::CourseAlgorithm(QObject *parent) : QObject(parent), totalCredits(0)
{
    semesterCourses.resize(8); // 初始化8个学期
}

QJsonObject CourseAlgorithm::generateSchedule(const QJsonObject &courseData, int creditLimit)
{
    // 重置状态
    courseMap.clear();
    classMap.clear();
    semesterCourses.assign(8, QVector<QString>());
    totalCredits = 0;

    // 初始化课程数据
    if (!initializeCourseData(courseData)) {
        return QJsonObject();
    }

    // 拓扑排序处理先修关系
    if (!topologicalSort()) {
        qWarning() << "课程先修关系存在循环依赖，无法生成选课方案";
        return QJsonObject();
    }

    // 选择课程以满足学分要求
    if (!selectCourses(creditLimit)) {
        qWarning() << "无法选择足够的课程以满足学分要求";
        return QJsonObject();
    }

    // 构建选课方案JSON
    return buildScheduleJson();
}

bool CourseAlgorithm::initializeCourseData(const QJsonObject &courseData)
{
    if (!courseData.contains("courses") || !courseData["courses"].isArray()) {
        return false;
    }

    QJsonArray courses = courseData["courses"].toArray();
    for (const auto &courseVal : courses) {
        QJsonObject courseObj = courseVal.toObject();
        CourseInfo course;
        course.id = courseObj["id"].toString();
        course.name = courseObj["name"].toString();
        course.credit = courseObj["credit"].toInt();
        course.semester = courseObj["semester"].toInt();
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
        classMap[course.id] = classInfos;
    }

    return true;
}

bool CourseAlgorithm::topologicalSort()
{
    QMap<QString, int> inDegree;
    QMap<QString, QVector<QString>> adjList;

    // 初始化入度和邻接表
    for (const auto &course : courseMap) {
        inDegree[course.id] = course.prerequisites.size();
        for (const auto &prereq : course.prerequisites) {
            adjList[prereq].append(course.id);
        }
    }

    // 拓扑排序队列
    std::queue<QString> q;
    for (const auto &entry : inDegree.toStdMap()) {
        if (entry.second == 0) {
            q.push(entry.first);
        }
    }

    QVector<QString> result;
    while (!q.empty()) {
        QString u = q.front();
        q.pop();
        result.append(u);

        for (const auto &v : adjList[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 检查是否存在循环依赖
    if (result.size() != courseMap.size()) {
        return false;
    }

    // 按拓扑顺序安排课程到建议学期
    for (const auto &courseId : result) {
        const CourseInfo &course = courseMap[courseId];
        int suggestedSemester = course.semester;

        // 如果课程有建议学期，尝试安排在该学期
        if (suggestedSemester >= 0 && suggestedSemester < 8) {
            semesterCourses[suggestedSemester].append(courseId);
        } else {
            // 否则安排在第一个可用学期
            for (int i = 0; i < 8; ++i) {
                semesterCourses[i].append(courseId);
                break;
            }
        }
    }

    return true;
}

bool CourseAlgorithm::checkTimeConflict(const QString &courseId, const QString &classId, int semester)
{
    // 查找要检查的课程的上课时间
    ClassInfo targetClass;
    bool found = false;
    for (const auto &classInfo : classMap[courseId]) {
        if (classInfo.id == classId) {
            targetClass = classInfo;
            found = true;
            break;
        }
    }
    if (!found) return true; // 未找到班级信息，视为冲突

    // 检查该学期已选课程是否有时间冲突
    for (const auto &selectedCourseId : semesterCourses[semester]) {
        if (selectedCourseId == courseId) continue;

        for (const auto &classInfo : classMap[selectedCourseId]) {
            // 简化的时间冲突检查逻辑
            // 实际应用中需要根据times和weeks字段进行详细的时间冲突判断
            // 这里仅作示例，返回false表示无冲突
            return false;
        }
    }

    return false;
}

bool CourseAlgorithm::selectCourses(int creditLimit)
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

int CourseAlgorithm::calculateTotalCredits()
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

QJsonObject CourseAlgorithm::buildScheduleJson()
{
    QJsonObject result;
    QJsonArray scheduleArray;

    for (int semester = 0; semester < 8; ++semester) {
        for (const auto &courseId : semesterCourses[semester]) {
            if (!courseMap.contains(courseId)) continue;

            QJsonObject scheduleItem;
            scheduleItem["course_id"] = courseId;
            // 简单起见，选择第一个班级
            if (!classMap[courseId].isEmpty()) {
                scheduleItem["class_id"] = classMap[courseId].first().id;
            } else {
                scheduleItem["class_id"] = QJsonValue::Null;
            }
            scheduleItem["semester"] = semester;
            scheduleArray.append(scheduleItem);
        }
    }

    result["schedule"] = scheduleArray;
    return result;
}