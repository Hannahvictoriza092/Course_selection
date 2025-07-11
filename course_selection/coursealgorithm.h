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
    QJsonObject generateSchedule(const QJsonObject &courseData, int creditLimit);

private:
    struct CourseInfo {
        QString id;
        QString name;
        int credit;
        int semester;
        bool required;
        QSet<QString> prerequisites;
        QJsonArray classes;
    };

    struct ClassInfo {
        QString id;
        QString teacher;
        QVector<int> times;
        int weeks;
    };

    QMap<QString, CourseInfo> courseMap;
    QMap<QString, QVector<ClassInfo>> classMap;
    QVector<QVector<QString>> semesterCourses; // 8个学期的课程安排
    int totalCredits;

    bool initializeCourseData(const QJsonObject &courseData);
    bool topologicalSort();
    bool checkTimeConflict(const QString &courseId, const QString &classId, int semester);
    bool selectCourses(int creditLimit);
    QJsonObject buildScheduleJson();
    int calculateTotalCredits();
};

#endif // COURSEALGORITHM_H