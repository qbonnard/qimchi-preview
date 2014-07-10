#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../qmlchilitags/chilitagscamera.h"
#include "../qmlchilitags/chilitagsobject.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //TODO there should be a way to avoid having to do that manually
    qmlRegisterType<ChilitagsCamera>("Chilitags", 1, 0, "ChilitagsCamera");
    qmlRegisterType<ChilitagsObject>("Chilitags", 1, 0, "ChilitagsObject");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
