#pragma once

#include <QMetaType>
#include <QObject>
#include <cstdint>

namespace lab::ui
{

/**
 * @brief Change of two values with given indexes.
 */
class Change
{
    Q_GADGET
    Q_PROPERTY(unsigned int first READ first)
    Q_PROPERTY(unsigned int second READ second)
public:
    Change(const std::size_t first, const std::size_t second) noexcept :
        _first{first},
        _second{second}
    { }

    Change() = default;
    Change(const Change&) = default;
    Change& operator=(const Change&) = default;

    std::size_t first() const noexcept
    {
        return _first;
    }

    std::size_t second() const noexcept
    {
        return _second;
    }

private:
    std::size_t _first{0};
    std::size_t _second{0};
};

} // namespace lab::ui

Q_DECLARE_METATYPE(lab::ui::Change);
