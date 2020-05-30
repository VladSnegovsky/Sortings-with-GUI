#pragma once

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QQmlComponent>
#include <QTimer>
#include <QTime>
#include <QThread>

namespace lab::ui
{

class Sort final : public QObject
{
    Q_OBJECT

signals:
    void sendToQml(int id1, int id2, QString name1, QString name2);
    void returnText(QString num);

public slots:
    void makeArray(QString newNum);
    void startSort(QString sortType);
    void speedUp();
    void speedDown();
};

} // namespace lab::ui
