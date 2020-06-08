#pragma once

#include <QVariantList>
#include <QObject>
#include <QString>
#include <memory>

namespace lab::ui {

/**
 * @brief Main class mapped into QML to interact with
 *  actual implementation of sorting.
 */
class Sort final: public QObject
{
    Q_OBJECT
public:
    Sort();
    ~Sort() noexcept;

public slots:
    void selectContainerType(QString type);
    void selectOrderType(QString type);
    void selectSortType(QString type);
    void addValue(QString value);
    QVariantList execute();
    void clear();

private:
    struct Impl;
    std::unique_ptr<Impl> _pimpl;
};

} // namespace lab::ui
