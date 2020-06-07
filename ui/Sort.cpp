#include "Sort.hpp"
#include "Change.hpp"

#include <Sort/Sort.hpp>
#include <Sort/Type.hpp>
#include <type_traits>
#include <variant>
#include <vector>

namespace lab::ui {
namespace {

/**
 * @brief Helper to simplify boilerplate typing.
 */
template<typename T, template<typename...> typename... Cs>
struct variant_storage
{
    template<template<typename...> typename C, typename... Args>
    void store() noexcept
    {
        data.template emplace<C<T, Args...>>();
    }

    std::variant<Cs<T>...> data;
};

} // namespace

struct Sort::Impl
{
    /// Type used for demonstration
    using value_type = int;

    /// Possible container type
    using container_type = variant_storage<
        value_type,
        std::vector,
        std::list
    >;

    /// Possible order type
    using order_type = variant_storage<
        value_type,
        std::less,
        std::greater
    >;

    /// Data to be sorted
    std::vector<value_type> data;
    /// Container to be sorted
    container_type container;
    /// Possible order type
    order_type order;
    /// Algorithm type
    /// TODO
    std::string algorithm;
};

Sort::Sort()
    : QObject{},
      _pimpl{new Impl{}}
{ }

Sort::~Sort() noexcept = default;

void Sort::selectContainerType(const QString type)
{
    if (type == "Vector") {
        return _pimpl->container.store<std::vector>();
    }

    if (type == "List") {
        return _pimpl->container.store<std::list>();
    }
}

void Sort::selectOrderType(const QString type)
{
    if (type == "Asc") {
        return _pimpl->order.store<std::less>();
    }

    if (type == "Desc") {
        return _pimpl->order.store<std::greater>();
    }
}

void Sort::selectSortType(const QString type)
{
    _pimpl->algorithm = type.toStdString();
}

void Sort::addValue(const QString value)
{
    /// TODO
}

QVariantList Sort::execute()
{
    /// TODO
}

void Sort::clear()
{
    /// TODO
}

} // namespace lab::ui
