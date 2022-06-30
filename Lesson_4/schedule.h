#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QString>

class Schedule: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(ScheduleTypes type READ getType WRITE setType NOTIFY typeChanged)

public:
    enum ScheduleTypes
    {
        PIE_CHART,
        LINE_SERIES,
        SCATTER_PLOT,
        BAR_SERIES
    };

    Schedule(QObject* parent = nullptr) : QObject(parent) {};

    QString getName() const { return name; }
    QString getColor() const { return color; }
    ScheduleTypes getType() { return type; }

    void setName(const QString& m_name) {
        if (name == m_name)
            return;

        name = m_name;
        emit nameChanged(name);
    }

    void setColor(const QString& m_color) {
        if (color == m_color)
            return;

        color = m_color;
        emit colorChanged(color);
    }

    void setType(const ScheduleTypes& m_type) {

        if (type == m_type)
            return;

        type = m_type;
        emit typeChanged(type);
    }

    Q_SIGNAL void nameChanged(const QString& name);
    Q_SIGNAL void colorChanged(const QString& color);
    Q_SIGNAL void typeChanged(const ScheduleTypes& type);

private:
    QString name{"MySchedule"};
    QString color{"red"};
    ScheduleTypes type{LINE_SERIES};
};

#endif // SCHEDULE_H
