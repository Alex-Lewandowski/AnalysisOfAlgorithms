// build.h
// Alex Lewandowski
// 9/20/20
// CS F411
// Chris Hartman
//

#include <vector>
#include <set>

#ifndef EXHAUSTIVE_SEARCH_BUILD_H
#define EXHAUSTIVE_SEARCH_BUILD_H

using Bridge = std::vector<int>;

template <class T>
std::set<T> vector_to_set(const std::vector<T> & vec);

template <class T>
std::vector<T> subset_from_indices(const std::vector<int> & indices,
                                   const std::vector<T> & tees);

bool two_bridges_intersect(const Bridge & b1,
                           const Bridge & b2);

bool any_bridges_intersect(const std::vector<Bridge> & bridges);

bool any_bridges_share_city(const std::vector<int> & cities_w,
                            const std::vector<int> & cities_e);

std::vector<std::vector<int>> power_set_indices(int n);

int build(int w, int e, const std::vector<Bridge> & bridges);


#endif//EXHAUSTIVE_SEARCH_BUILD_H
