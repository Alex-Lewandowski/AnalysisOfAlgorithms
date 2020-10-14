// inversions.hpp
// Alex Lewandowski
// 10/12/20
// CS F411 - Chris Hartman
// HW3
//
// based on merge_sort.cpp
// by Glenn G. Chappell
// 9 Oct 2015
// Merge Sort using Iterators

#ifndef EXHAUSTIVE_SEARCH_INVERSIONS_HPP
#define EXHAUSTIVE_SEARCH_INVERSIONS_HPP

#include <iostream>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <type_traits>

using std::remove_reference;

template<typename RAIter>
size_t inversions(RAIter first, RAIter last);


template<typename RAIter>
size_t stableMerge(RAIter first, RAIter middle, RAIter last) {
    // ** C++03:
    using Value = typename std::iterator_traits<RAIter>::value_type;

    // Buffer for temporary copy of data
    std::vector<Value> buffer(distance(first, last));
    RAIter in1 = first;         // Read location in 1st half
    RAIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    size_t count = 0;

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last) {
        if (*in2 < *in1) {// Must do comparison this way, to be stable.
            *out++ = *in2++;
            // add the number of items left in the first half
            count += middle - in1;
        } else {
            *out++ = *in1++;
        }

    }
    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    copy(in1, middle, out);
    copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    copy(buffer.begin(), buffer.end(), first);
    return count;
}


// Leverages mergeSort to count inversions in a sequence
// Sorts a sequence, using Merge Sort.
// Recursive.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template<typename RAIter>
size_t inversions(RAIter first, RAIter last) {

    // Compute size of sequence
    size_t size = distance(first, last);
    // BASE CASE
    if (size <= 1)
        return 0;

    // RECURSIVE CASE
    RAIter middle = first;
    advance(middle, size / 2);  // middle is iterator to middle of range

    // Recursively sort the two lists, accumulating an inversion count
    auto count = inversions(first, middle);
    count += inversions(middle, last);

    // And merge them, while topping off the inversion count
    count += stableMerge(first, middle, last);
    return count;
}

#endif//EXHAUSTIVE_SEARCH_INVERSIONS_HPP
