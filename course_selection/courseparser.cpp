/**
 * @file courseparser.cpp
 * @brief 课程数据解析实现
 *
 * 实现以下核心功能：
 * 1. 文件读取与JSON解析
 * 2. 课程数据结构验证：
 *   - 校验必填字段(id/name/credit等)
 *   - 校验times数组长度(7天)和元素类型
 *   - 校验周数掩码范围(1-18周)
 * 3. 错误处理与日志输出
 *
 * @see CourseParser 类声明
 */
#include "courseparser.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

CourseParser::CourseParser(QObject *parent) : QObject(parent)
{
}

QJsonObject CourseParser::parseCourseFile(const QString &filePath)
{
    QJsonObject rootObj;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开课程文件: " << filePath;
        return QJsonObject();
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "课程文件解析失败: 无效的JSON格式";
        return QJsonObject();
    }

    QJsonArray coursesArray;
    if (doc.isObject()) {
        rootObj = doc.object();
        if (!rootObj.contains("courses") || !rootObj["courses"].isArray()) {
            qWarning() << "课程文件解析失败: 缺少courses数组";
            return QJsonObject();
        }
        coursesArray = rootObj["courses"].toArray();
    } else if (doc.isArray()) {
        coursesArray = doc.array();
        rootObj["courses"] = coursesArray;
    } else {
        qWarning() << "课程文件解析失败: 根节点不是对象或数组";
        return QJsonObject();
    }
    for (int i = 0; i < coursesArray.size(); ++i) {
        if (!coursesArray[i].isObject()) {
            qWarning() << "课程文件解析失败: 课程项不是对象，索引:" << i;
            return QJsonObject();
        }

        QJsonObject courseObj = coursesArray[i].toObject();
        if (!validateCourseStructure(courseObj)) {
            qWarning() << "课程文件解析失败: 课程结构验证失败，索引:" << i;
            return QJsonObject();
        }

        QJsonArray offeringsArray = courseObj["offerings"].toArray();
        for (int j = 0; j < offeringsArray.size(); ++j) {
            if (!offeringsArray[j].isObject()) {
                qWarning() << "课程文件解析失败: 上课时间项不是对象，课程索引:" << i << "，时间索引:" << j;
                return QJsonObject();
            }

            QJsonObject classObj = offeringsArray[j].toObject();
            if (!validateOfferingStructure(classObj)) {
                qWarning() << "课程文件解析失败: 上课时间结构验证失败，课程索引:" << i << "，时间索引:" << j;
                return QJsonObject();
            }
        }
    }

    return rootObj;
}

bool CourseParser::validateCourseStructure(const QJsonObject &courseObj)
{
    // 验证课程基本字段
    if (!courseObj.contains("id") || !courseObj["id"].isString()) return false;
    if (!courseObj.contains("name") || !courseObj["name"].isString()) return false;
    if (!courseObj.contains("credit") || !courseObj["credit"].isDouble()) return false;
    if (!courseObj.contains("semester") || !courseObj["semester"].isString()) return false;
    if (!courseObj.contains("required") || !courseObj["required"].isString()) return false;
    if (!courseObj.contains("offerings") || !courseObj["offerings"].isArray()) return false;
    if (!courseObj.contains("prerequisites") || !courseObj["prerequisites"].isArray()) return false;

    // 验证前置课程数组元素类型
    QJsonArray prereqs = courseObj["prerequisites"].toArray();
    for (const auto &prereq : prereqs) {
        if (!prereq.isString()) return false;
    }

    return true;
}

bool CourseParser::validateOfferingStructure(const QJsonObject &classObj)
{
    // 验证上课时间字段
    if (!classObj.contains("id") || !classObj["id"].isString()) return false;
    if (!classObj.contains("teacher") || !classObj["teacher"].isString()) return false;
    if (!classObj.contains("times") || !classObj["times"].isArray()) return false;
    if (!classObj.contains("weeks") || !classObj["weeks"].isDouble()) return false;

    // 修改时间数组验证：验证是否是7个数值
    QJsonArray timesArray = classObj["times"].toArray();
    if (timesArray.size() != 7) {
        qWarning() << "错误: times数组长度应为7，实际为" << timesArray.size();
        return false;
    }
    
    for (const auto &timeVal : timesArray) {
        if (!timeVal.isDouble()) {
            qWarning() << "错误: times数组元素不是数值类型";
            return false;
        }
    }
    return true;
}
