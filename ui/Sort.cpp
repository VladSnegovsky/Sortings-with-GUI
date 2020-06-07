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
template<typename T, template<typename...> typename... Ts>
using container_variant = std::variant<Ts<T>...>;

} // namespace

struct Sort::Impl
{
    /// Type used for demonstration
    using value_type = int;

    /// Possible container type
    using container_type = container_variant<
        value_type,
        std::vector
    >;

    /// Container to be sorted
    container_type container;
    /// Algorithm type
    std::string algorithm;
};

Sort::Sort()
    : QObject{},
      _pimpl{new Impl{}}
{ }

Sort::~Sort() noexcept = default;

void Sort::selectType(const QString type)
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
