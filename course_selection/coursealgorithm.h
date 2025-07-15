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
    QJsonObject genSimSchedule(const QJsonObject &courseData, int creditLimit);
    //输入课程数据和学分上限，还有一个必修选修，输出生成的课程表
    QJsonObject genPriorSchedule(const QJsonObject &courseData, int creditLimit);

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
        int priority=2; // 0=高, 1=中, 2=低（仅选修课有效，默认为最低）
    };

    //教学班信息
    struct ClassInfo {
        QString id;
        QString teacher;
        QString courseID;
        QVector<int> times;
        int weeks;
    };
    //考虑优先级的节点结构
    struct CourseNode {
    CourseInfo course;
    int inDegree; // 入度（依赖未完成的课程数）
    bool operator<(const CourseNode &other) const {
        // 必修课优先
        if (course.required != other.course.required) {
            return course.required; // true（必修）排前面
        }
        // 同为必修或选修时，按优先级排序
        if (course.required) {
            return false; // 必修课之间不区分优先级（或可按其他规则）
        } else {
            return course.priority > other.course.priority; // 选修课：priority小的优先
        }
    }
    };
    
    //课程名称对应，课程的信息
    QMap<QString, CourseInfo> courseMap;
    //课程ID：各个老师的这门课信息
    QMap<QString, QVector<ClassInfo>> classMap;
    //排课ID对应这个老师的课信息
     QMap<QString,ClassInfo> classDetail;
     // 8个学期的课程安排，就是完成把课程分配到学期的任务（按照先导关系拓扑，与学分无关）
    QVector<QVector<QString>> semesterCourses;
    //总学分
    int totalCredits;
    //拓扑排序后的结果
    QVector<QString> topoQueue;
    //课程和学期的映射
    QMap<QString,int> Course_in_sem;
    
    //函数，初始化课程数据
    bool initializeCourseData(const QJsonObject &courseData);
    //拓扑排序
    bool topologicalSort();
    //考虑优先级的拓朴排序
    bool topoPriorSort();
    //选择课程
    int simplesSelect(int Limit);
    bool compulsoryBasedSelect(int courseIndex,int curCredits,int Limit);
    //建立课程安排
    QJsonObject buildScheduleJson();
    //计算总学分
    int calculateTotalCredits();
    //辅助函数，任checkTimeConflict调用，检查同学期的冲突
    bool hasTimeConflict(int semester, const ClassInfo &newClass) ;

    //辅助函数,查找课程已经被安排在哪个学期
    int findCourseSemester(const QString &courseId);
    //辅助函数，帮助递归寻找小课
    bool tryArrangeCourse(const QString& courseId, int courseIndex, int& curCredits, int Limit);

};

#endif // COURSEALGORITHM_H