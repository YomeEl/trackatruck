#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dataprovider.h"
#include "lists/orderslist.h"

#include <QObject>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<ClientsList>("types", 1, 0, "ClientsList");
    qmlRegisterType<DriversList>("types", 1, 0, "DriversList");
    qmlRegisterType<RefuelingsList>("types", 1, 0, "RefuelingsList");
    qmlRegisterType<TrucksList>("types", 1, 0, "TrucksList");
    qmlRegisterType<OrdersList>("types", 1, 0, "OrdersList");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);  

    engine.rootContext()->setContextProperty("DataProvider", DataProvider::Instance());
    engine.load(url);

    return app.exec();
}
