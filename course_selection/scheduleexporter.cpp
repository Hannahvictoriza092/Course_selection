#include "scheduleexporter.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ScheduleExporter::ScheduleExporter(QObject *parent) : QObject(parent)
{
}

bool ScheduleExporter::exportSchedule(const QString &filePath, const QJsonObject &scheduleData)
{
    QJsonArray result;

    //先进行检查
    if (!validateScheduleStructure(scheduleData)) {
        qWarning() << "选课方案数据结构验证失败";
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件进行写入: " << filePath;
        return false;
    }
    //再提取
    QJsonArray scheduleArray = scheduleData["schedule"].toArray();
    for (const QJsonValue &courseVal : scheduleArray) {
        if (!courseVal.isObject()) continue; // 跳过非对象项
 
        QJsonObject course = courseVal.toObject();
        QJsonObject extractedCourse;
 
        // 提取目标字段（如果字段不存在，设为默认值）
        extractedCourse["class_id"] = course.value("class_id").toString("");
        extractedCourse["course_id"] = course.value("course_id").toString("");
        extractedCourse["semester"] = ((course.value("semester").toInt(-1))-1)%2; // 默认 -1
 
        result.append(extractedCourse);
    }

    QJsonDocument doc(result);
    QByteArray data = doc.toJson(QJsonDocument::Indented);
    if (file.write(data) == -1) {
        qWarning() << "文件写入失败";
        return false;
    }




    return true;
}




    


 
bool ScheduleExporter::validateScheduleStructure(const QJsonObject &scheduleObj)
{
    if (!scheduleObj.contains("schedule") ) {
        qWarning() << "选课方案缺少schedule标签";
        return false;
    }
    if(!scheduleObj["schedule"].isArray()){
        qWarning() << "选课方案schedule不是数组";
        return false;
    }

    QJsonArray scheduleArray = scheduleObj["schedule"].toArray();
    for (int i = 0; i < scheduleArray.size(); ++i) {
        if (!scheduleArray[i].isObject()) {
            qWarning() << "选课方案项不是对象，索引:" << i;
            return false;
        }

        QJsonObject itemObj = scheduleArray[i].toObject();
        if (!itemObj.contains("course_id") || !itemObj["course_id"].isString()) {
            qWarning() << "选课方案项缺少有效的course_id，索引:" << i;
            return false;
        }

        if (!itemObj.contains("class_id") || (!itemObj["class_id"].isString() && !itemObj["class_id"].isNull())) {
            qWarning() << "选课方案项缺少有效的class_id，索引:" << i;
            return false;
        }

        if (!itemObj.contains("semester") || !itemObj["semester"].isDouble()) {
            qWarning() << "选课方案项缺少有效的semester，索引:" << i;
            return false;
        }

        int semester = itemObj["semester"].toInt();
        if (semester != -1 && (semester < 1 || semester > 8)) {
            qWarning() << "选课方案项semester值无效，索引:" << i;
            return false;
        }
    }

    return true;
}