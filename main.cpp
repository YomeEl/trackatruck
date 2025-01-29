#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dataprovider.h"
#include "lists/orderslist.h"
#include "types.h"

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

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

    qmlRegisterType<OrdersList>("types", 1, 0, "OrdersList");

    engine.rootContext()->setContextProperty("DataProvider", DataProvider::Instance());
    engine.load(url);

    return app.exec();
}
