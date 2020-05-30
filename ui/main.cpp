#include "Sort.hpp"

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app{argc, argv};
    QQmlApplicationEngine engine;
    lab::ui::Sort mainSort;
    const QUrl url{QStringLiteral("qrc:/main.qml")};

    engine.rootContext()->setContextProperty("sorting", &mainSort);
    QObject::connect(
        &engine, 
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url = QUrl{QStringLiteral("qrc:/main.qml")}] (auto* object, const QUrl& objectUrl) {
            if (!object && url == objectUrl) {
                QCoreApplication::exit(-1);
            }
        }, 
        Qt::QueuedConnection
    );
    engine.load(url);

    return app.exec();
}
