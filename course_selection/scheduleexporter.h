#ifndef SCHEDULEEXPORTER_H
#define SCHEDULEEXPORTER_H

#include <QObject>
#include <QJsonObject>
#include <QString>

class ScheduleExporter : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleExporter(QObject *parent = nullptr);
    bool exportSchedule(const QString &filePath, const QJsonObject &scheduleData);

private:
    bool validateScheduleStructure(const QJsonObject &scheduleObj);
};

#endif // SCHEDULEEXPORTER_H