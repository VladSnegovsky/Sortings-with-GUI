#pragma once

#include <Utils/Range.hpp>

#include <QObject>
#include <QString>
#include <memory>

namespace lab::ui
{

/**
 * @brief Main class mapped into QML to interact with
 *        actual implementation of sorting.
 */
class Sort final: public QObject
{
    Q_OBJECT
public:
    Sort();

public slots:
    void selectType(QString type);
    void addValue(QString value);
    void start();
    void speedUp();
    void speedDown();

signals:
    void sendChange(int first, int second);

private:
    void _finish();

private:
    struct Impl;
    /// Qt classes aren't C++11 & move semantic aware, so we have to use
    /// shared pointer here instead of unique_ptr
    std::shared_ptr<Impl> _pimpl;
};

} // namespace lab::ui
