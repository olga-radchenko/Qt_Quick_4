#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtCharts>
#include <QTimer>
#include <QDebug>
#include "schedule.h"

int main(int argc, char *argv[])
{
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/scheduleview.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    qmlRegisterType<Schedule>("myTest", 1, 0, "Schedule");

    engine.load(url);

    return app.exec();
}
