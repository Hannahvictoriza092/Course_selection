/**
 * @file courseparser.h
 * @brief 课程数据解析器
 * 
 * 负责从JSON文件加载课程数据，并进行结构化验证。包含以下核心功能：
 * 1. 解析课程文件并验证JSON结构
 * 2. 验证课程基本字段完整性
 * 3. 验证教学班时间数据结构
 * 
 * 关键数据结构：
 * - CourseParser：提供解析入口方法parseCourseFile
 */

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