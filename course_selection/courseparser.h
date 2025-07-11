#ifndef COURSEPARSER_H
#define COURSEPARSER_H

#include <QObject>
#include <QJsonObject>
#include <QString>

class CourseParser : public QObject
{
    Q_OBJECT
public:
    explicit CourseParser(QObject *parent = nullptr);
    QJsonObject parseCourseFile(const QString &filePath);

private:
    bool validateCourseStructure(const QJsonObject &courseObj);
    bool validateOfferingStructure(const QJsonObject &classObj);
};

#endif // COURSEPARSER_H