#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "passwordmodel.h"
#include "filestorage.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<PasswordModel>("passwordmodel",1,0,"PasswordModel");

    qmlRegisterUncreatableType<IStorage>("filestorage", 1, 0, "IStorage", "This is an interface");
    qmlRegisterType<FileStorage>("filestorage",1,0,"FileStorage");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
