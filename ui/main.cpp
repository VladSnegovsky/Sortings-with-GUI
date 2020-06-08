#include "Sort.hpp"
#include "Change.hpp"

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app{argc, argv};
    QQmlApplicationEngine engine;
    lab::ui::Sort sort;

    qmlRegisterUncreatableType<lab::ui::change::Swap>("Lab.Change", 1, 0, "Swap", "");
    qmlRegisterUncreatableType<lab::ui::change::SelectPivot>("Lab.Change", 1, 0, "SelectPivot", "");
    qmlRegisterUncreatableType<lab::ui::change::SelectSubrange>("Lab.Change", 1, 0, "SelectSubrange", "");
    qmlRegisterUncreatableType<lab::ui::change::MergeSubranges>("Lab.Change", 1, 0, "MergeSubranges", "");
    qmlRegisterUncreatableType<lab::ui::change::Compare>("Lab.Change", 1, 0, "Compare", "");

    engine.rootContext()->setContextProperty("sort", &sort);
    engine.load(QUrl{QStringLiteral("qrc:/main.qml")});

    return QGuiApplication::exec();
}
