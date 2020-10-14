// contigsum.hpp
// Alex Lewandowski
// 10/10/20
// CS F411 - Chris Hartman
// HW3
//

#include <iostream>
#include <vector>
#include <algorithm>

#ifndef EXHAUSTIVE_SEARCH_CONTIGSUM_HPP
#define EXHAUSTIVE_SEARCH_CONTIGSUM_HPP

template<typename RAIter>
int contigSum(RAIter first, RAIter last);

template<typename RAIter>
int gcs_first_or_last(RAIter first, RAIter last, bool forwards);


template<typename RAIter>
int gcs_first_or_last(RAIter first, RAIter last, bool from_first) {
    /**
     * from_first: true returns greatest contiguous sum including first element
     *             false returns greatest contiguous sum including last element
     */
    const auto len = last - first;
    auto sum = 0;
    auto max = 0;
    for (auto i = 0; i < len; ++i) {
        if (from_first) {
            sum += *(first + i);
        } else {
            sum += *(last - 1 - i);
        }
        max = std::max(sum, max);
    }
    return max;
}

template<typename RAIter>
int contigSum(RAIter first, RAIter last) {
    /**
     * returns the greatest contiguous sum in a container with random iterators
     */
    const auto len = last - first;
    const auto half_len = len / 2;
    if (first == last || *(std::max_element(first, last)) < 1) {
        return 0;
    }
    if (len == 1) {
        return std::max(0, *first);
    }
    std::vector<int> max = {0, 0, 0};
    max[0] = std::max(max[0], contigSum(first, first + half_len));
    max[1] = std::max(max[1], contigSum(first + half_len, last));
    max[2] = std::max(max[2], gcs_first_or_last(first, first + half_len, false) +
                              gcs_first_or_last(first + half_len, last, true));
    return *(std::max_element(max.begin(), max.end()));
}

#endif//EXHAUSTIVE_SEARCH_CONTIGSUM_HPP
