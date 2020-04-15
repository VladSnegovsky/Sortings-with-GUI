#include "operations.hpp"

/**
 * Swapper - function to swap two values from container
 * Comparator - function to compare values in container
 * changeI changeJ - fuction will be called when i and j pointers are changed
*/

namespace sorting {
    
    template<typename It, typename Swapper_t , typename Comparator_t, typename changeI_t, typename changeJ_t>
    /**
     * Sorts area in begin->end with insertion sort algorithm
     * @note begin and end mus be type of Bidirectional iterator
    */
    void insertionSort(It begin, It end, 
                       const Swapper_t &Swapper, 
                       const Comparator_t &Comparator, 
                       const changeI_t &changeI, 
                       const changeJ_t &changeJ
                      )
    {
        while (begin != end) {
            changeI(begin);
            changeJ(begin);
            auto it = begin + 1;
            while (it !=end) {
                changeI(it);
                if (Comparator(*begin, *it)) {
                    Swapper(*begin, *it);
                }
                it++;
            }
            begin++;
        }
    }
} // sorting end
