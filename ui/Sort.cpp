#include "Sort.hpp"
#include "Change.hpp"

#include <Sort/bubble.hpp>
#include <Sort/heap.hpp>
#include <Sort/insertion.hpp>
#include <Sort/merge.hpp>
#include <Sort/quick.hpp>
#include <Sort/selection.hpp>
#include <Utils/Range.hpp>
#include <QDebug>
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

/**
 * @brief Alias to help compiler deduce return type.
 */
template<typename It, typename Comp>
using function = void(It first, It last, Comp comp);

/**
 * @brief Convert name to algorithm.
 */
template<typename It, typename Comp>
constexpr auto algorithm_from_string(const std::string_view name) noexcept -> function<It, Comp>*
{
    if (name == "BubbleSort") {
        return sort::bubble<It, Comp>;
    }

    if (name == "HeapSort") {
        return sort::heap<It, Comp>;
    }

    if (name == "InsertionSort") {
        return sort::insertion<It, Comp>;
    }

    if (name == "MergeSort") {
        return sort::merge<It, Comp>;
    }

    if (name == "QuickSort") {
        return sort::quick<It, Comp>;
    }

    if (name == "SelectionSort") {
        return sort::selection<It, Comp>;
    }

    return nullptr;
}

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
    _pimpl->data.push_back(value.toInt());
}

QVariantList Sort::execute()
{
    QVariantList result;

    std::visit([&](auto& container) {
            std::move(
                _pimpl->data.begin(),
                _pimpl->data.end(),
                std::back_inserter(container)
            );

            utils::Range range{container};

            range.set_change_handler([&] (auto change) mutable {
                const auto index = [&] (const auto it) {
                    return static_cast<std::size_t>(std::distance(container.begin(), it));
                };

                QVariant variant;
    
                variant.setValue(Change{index(change.first), index(change.second)});
                result.push_back(std::move(variant));
            });

            const auto comparator = [&order = _pimpl->order] (const auto& lhs, const auto& rhs) {
                return std::visit([&] (const auto & order) {
                        return order(lhs, rhs);
                    },
                    order.data
                );
            };

            /// Choose sort type
            const auto sort = algorithm_from_string<typename decltype(range)::iterator, decltype(comparator)>(_pimpl->algorithm);
            if (!sort) {
                return;
            }

            /// Invoke sort & aggregate changes
            sort(range.begin(), range.end(), comparator);
            /// Move sorted container back to data
            std::move(
                container.begin(),
                container.end(),
                _pimpl->data.begin()
            );
            /// Clear container
            container.clear();
        },
        _pimpl->container.data
    );

    return result;
}

void Sort::clear()
{
    _pimpl->data.clear();
}

} // namespace lab::ui
