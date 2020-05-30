#include "Sort.hpp"

#include <Sort/bubble.hpp>
#include <Sort/heap.hpp>
#include <Sort/insertion.hpp>
#include <Sort/merge.hpp>
#include <Sort/quick.hpp>
#include <Sort/selection.hpp>
#include <Utils/Range.hpp>
#include <QDebug>
#include <QVector>
#include <type_traits>
#include <optional>
#include <cassert>
#include <variant>
#include <vector>

namespace lab::ui {
namespace {

/**
 * @brief Helper to simplify boilerplate typing.
 */
template<typename T, template<typename...> typename... Ts>
using container_variant = std::variant<Ts<T>...>;

/**
 * @brief
 */
template<typename Container, typename It = typename Container::iterator>
using function = void(It first, It last);

/**
 * @brief
 */
template<typename Container>
constexpr auto algorithm_from_string(const std::string_view name) noexcept -> function<Container>*
{
    using iterator = typename Container::iterator;

    if (name == "BubbleSort") {
        return sort::bubble<iterator>;
    }

    if (name == "HeapSort") {
        return sort::heap<iterator>;
    }

    if (name == "InsertionSort") {
        return sort::insertion<iterator>;
    }

    if (name == "MergeSort") {
        return sort::merge<iterator>;
    }

    if (name == "QuickSort") {
        return sort::quick<iterator>;
    }

    if (name == "SelectionSort") {
        return sort::selection<iterator>;
    }

    return nullptr;
}

} // namespace


struct Sort::Impl
{
    /// Type used for demonstration
    using value_type = int;

    /// Possible container type
    using container_type = container_variant<
        value_type,
        std::vector,
        std::list
    >;

    /// Container to be sorted
    container_type container;
    /// Algorithm type
    std::string algorithm;
};

Sort::Sort()
    : _pimpl{new Impl{}}
{ }

void Sort::selectType(const QString type)
{
    _pimpl->algorithm = type.toStdString();
}

void Sort::addValue(const QString value)
{
    std::visit([&](auto& container) {
            container.push_back(value.toInt());
        },
        _pimpl->container
    );
}

void Sort::start()
{
    // std::visit([&](auto& container) {
    //         utils::Range range{container};
    //         range.set_change_handler([] (auto) {});

    //         const auto sort = algorithm_from_string<decltype(range)>(_pimpl->algorithm);

    //         if (sort) {
    //             return;
    //         }

    //         sort(range.begin(), range.end());

    //         container.clear();
    //     },
    //     _pimpl->container
    // );

    // emit sendChange(0, 1);
    emit sendChange(0, 2);
}

void Sort::speedUp()
{

}

void Sort::speedDown()
{

}

} // namespace lab::ui
