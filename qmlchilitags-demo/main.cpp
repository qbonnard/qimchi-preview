#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Specify where to look for compiled Qimchi plugins
#ifdef Q_OS_ANDROID
    engine.addImportPath("assets:/imports");
#else
    engine.addImportPath("../imports");
#endif

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
