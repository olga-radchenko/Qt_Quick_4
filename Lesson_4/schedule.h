#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDebug>
#include <math.h>
#include <algorithm>

class ScheduleTypes
{
    Q_GADGET
public:
    explicit ScheduleTypes();

    enum Type {
        TYPE_NULL,
        TYPE_X,
        TYPE_SIN_X,
        TYPE_POW_X,
        TYPE_LOG_X,
        TYPE_MODULE_X
    };
    Q_ENUM(Type)
};
typedef ScheduleTypes::Type ScheduleType;

class Schedule: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(ScheduleType type READ getType WRITE setType NOTIFY typeChanged)

    Q_PROPERTY(QVector<qreal> x_vec READ getX_vec)
    Q_PROPERTY(QVector<qreal> y_vec READ getY_vec)

    Q_PROPERTY(qreal x_max READ getX_max)
    Q_PROPERTY(qreal x_min READ getX_min)
    Q_PROPERTY(qreal y_max READ getY_max)
    Q_PROPERTY(qreal y_min READ getY_min)

public:


    Schedule(QObject* parent = nullptr) : QObject(parent)
    {
        for(float i = 0.0; i <= 5; i+=0.1) { x_vec.append(i); }
    };

    Q_INVOKABLE QString        getName()  const { return name;  }
    Q_INVOKABLE QString        getColor() const { return color; }
    Q_INVOKABLE ScheduleType   getType()  const { return type;  }
    Q_INVOKABLE QVector<qreal> getX_vec() const { return x_vec; }
    Q_INVOKABLE QVector<qreal> getY_vec() const { return y_vec; }

    Q_INVOKABLE qreal getX_max() const { return *std::max_element(x_vec.constBegin(), x_vec.constEnd());}
    Q_INVOKABLE qreal getX_min() const { return *std::min_element(x_vec.constBegin(), x_vec.constEnd());}
    Q_INVOKABLE qreal getY_max() const { return *std::max_element(y_vec.constBegin(), y_vec.constEnd());}
    Q_INVOKABLE qreal getY_min() const { return *std::min_element(y_vec.constBegin(), y_vec.constEnd());}

    Q_INVOKABLE void setName(const QString& m_name) {
        if (name == m_name)
            return;

        name = m_name;
        emit nameChanged(name);
    }

    Q_INVOKABLE void setColor(const QString& m_color) {
        if (color == m_color)
            return;

        color = m_color;
        emit colorChanged(color);
    }

    Q_INVOKABLE void setType(const ScheduleType& m_type) {

        if (type == m_type)
            return;

        type = m_type;
        count_Y();
        emit typeChanged(type);
    }

    Q_SIGNAL void nameChanged (const QString&  name);
    Q_SIGNAL void colorChanged(const QString& color);
    Q_SIGNAL void typeChanged (const ScheduleType& type);

private:
    QString name{"Null"};
    QString color{"red"};
    ScheduleType type{ScheduleType::TYPE_NULL};
    QVector<qreal> x_vec;
    QVector<qreal> y_vec;

    void count_Y() {
        y_vec.clear();

        if(type == ScheduleType::TYPE_X)
        {
             for(int i = 0; i < x_vec.size(); i++) { y_vec.append(x_vec[i]); }
             setName("y = x");
        }
        else if(type == ScheduleType::TYPE_SIN_X)
        {
             for(int i = 0; i < x_vec.size(); i++) { y_vec.append(sin(x_vec[i])); }
             setName("y = sin(x)");
        }
        else if (type == ScheduleType::TYPE_POW_X)
        {
            for(int i = 0; i < x_vec.size(); i++) { y_vec.append( pow(x_vec[i],2) ); }
            setName("y = x^2");
        }
        else if (type == ScheduleType::TYPE_LOG_X)
        {
            for(int i = 0; i < x_vec.size(); i++) { y_vec.append( log2f(x_vec[i]) ); }
            setName("y = log2(x)");
        }
        else if (type == ScheduleType::TYPE_MODULE_X)
        {
            for(int i = 0; i < x_vec.size(); i++) { y_vec.append( abs(x_vec[i]-2.5) ); }
            setName("y = |x-2.5|");
        }
    }
};

#endif // SCHEDULE_H
