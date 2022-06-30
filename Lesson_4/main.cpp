#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QDebug>
#include "schedule.h"

int main(int argc, char *argv[])
{
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
    QGuiApplication app(argc, argv);

    Schedule my_schedule; // Создание объекта

    // Добавим коннект, чтобы отслеживать изменения
    QObject::connect(&my_schedule, &Schedule::nameChanged,
    [](const QString& newName){ qDebug() << "Имя было изменено на "
    << newName; });

    QObject::connect(&my_schedule, &Schedule::colorChanged,
    [](const QString& newColor){ qDebug() << "Цвет был изменен на "
    << newColor; });

    QObject::connect(&my_schedule, &Schedule::typeChanged,
    [](const Schedule::ScheduleTypes& newType){ qDebug() << "Тип графика был изменен на "
    << newType; });


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/scheduleview.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
    QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    // Передача конкретного объекта в QML. Эта переменная будет доступна
    // в QML по имени, указанному в качестве первого параметра
    engine.rootContext()->setContextProperty("my_schedule", &my_schedule);
    engine.load(url);
    // изменим пароль через несколько секунд после начала работы программы из C++ кода
    QTimer::singleShot(2000, &my_schedule, [&my_schedule](){
    my_schedule.setName("testName");});

    return app.exec();
}
