#ifndef ARRSORT_H
#define ARRSORT_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QQmlComponent>
#include <QTimer>
#include <QTime>
#include <QThread>

class arrSort: public QObject
{
    Q_OBJECT

public:
    arrSort();

signals:
    void sendToQml(int id1, int id2, QString name1, QString name2);
    void returnText(QString num);

public slots:
    void createArr(QString newNum);
    void startSort(QString sortType);
    void speedlower();
    void speedhigher();
};

#endif // ARRSORT_H
