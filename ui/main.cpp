#include "Sort.hpp"

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app{argc, argv};
    QQmlApplicationEngine engine;
    lab::ui::Sort sort;

    engine.rootContext()->setContextProperty("sort", &sort);
    engine.load(QUrl{QStringLiteral("qrc:/main.qml")});

    return QGuiApplication::exec();
}
