#ifndef COURSEALGORITHM_H
#define COURSEALGORITHM_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QSet>
#include <vector>
#include <tuple>

class CourseAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit CourseAlgorithm(QObject *parent = nullptr);

    //输入课程数据和学分上限，输出生成的课程表
    QJsonObject generateSchedule(const QJsonObject &courseData, int creditLimit);

private:
    
    //定义一个课程结构体
    struct CourseInfo {
        QString id;
        QString name;
        int credit;
        int semester;
        bool required;
        QSet<QString> prerequisites;//可以避免重复
        QJsonArray classes;
    };

    //教学班信息
    struct ClassInfo {
        QString id;
        QString teacher;
        QVector<int> times;
        int weeks;
    };

    //课程名称对应，课程的信息
    QMap<QString, CourseInfo> courseMap;
    //课程ID：各个老师的这门课信息
    QMap<QString, QVector<ClassInfo>> classMap;
     // 8个学期的课程安排
    QVector<QVector<QString>> semesterCourses;//应有八个
    //总学分
    int totalCredits;
    
    //函数，初始化课程数据
    bool initializeCourseData(const QJsonObject &courseData);
    //拓扑排序
    bool topologicalSort();
    //检查时间冲突
    bool checkTimeConflict(const QString &courseId, const QString &classId, int semester);
    //选择课程
    bool selectCourses(int creditLimit);
    //建立课程安排
    QJsonObject buildScheduleJson();
    //计算总学分
    int calculateTotalCredits();
    //辅助函数，任checkTimeConflict调用，检查同学期的冲突
    bool CourseAlgorithm::hasTimeConflict(const QVector<ClassInfo> &existingClasses, const ClassInfo &newClass) ;
};

#endif // COURSEALGORITHM_H