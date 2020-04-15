#include <type_traits>

namespace operations {
    /*
        You can put code in place of comments
    */

    /// Swaps two values
    template <typename T>
    void swap(T &first, T &second) {
        /*
            Values are swapped
        */
        std::swap(first, second);
    }

    /**
     * Compares two values
     * @return true, if second < first
     */
    template <typename T>
    bool comparator(T first, T second) {
        /*
            Values are being compared
        */
        static const auto comparator = std::less<>();
        return comparator(second, first);
    }

    /// Signals that I pointer changed
    template <typename It>
    void changeI(It iterator) {
        /*
            I index changed to <iterator>
        */
    }

    /// Signals that J pointer changed
    template <typename It>
    void changeJ(It iterator) {
        /*
            J index changed to <iterator>
        */
    }
} // operations end
