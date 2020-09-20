//
// Created by alex on 9/20/20.
//

#include "build.h"

#include <vector>
using std::vector;
#include <bits/stdc++.h>
using std::accumulate;
#include <set>
using std::set;
#include <algorithm>
using std::find;
using std::max_element;

using Bridge = vector<int>;


bool two_bridges_intersect(const Bridge & b1,
                           const Bridge & b2) {
    return (b2[0] > b1[0] && b2[1] < b1[1])
           || (b2[0] < b1[0] && b2[1] > b1[1]);
}


bool any_bridges_intersect(const vector<Bridge> & bridges) {
    if(size(bridges) > 1) {
        for (auto i = 0; i < size(bridges)-1; ++i) {
            for (auto j = 1; j < size(bridges); ++j) {
                if (two_bridges_intersect(bridges[i], bridges[j])) {
                    return true;
                }
            }
        }
    }
    return false;
}


template <class T>
set<T> vector_to_set(const vector<T> & vec) {
    set<T> s;
    for(auto i : vec){
        s.insert(i);
    }
    return s;
}


bool any_bridges_share_city(const vector<int> & cities_w,
                            const vector<int> & cities_e) {
    auto set_w = vector_to_set(cities_w);
    auto set_e = vector_to_set(cities_e);
    return size(cities_e) != size(set_e) ||
           size(cities_w) != size(set_w);
}


vector<vector<int>> power_set_indices(int n) {
    auto pwr_set_length = 1 << n; // 2^n
    auto pwr_set = vector<vector<int>>{};
    for(auto i=1; i<pwr_set_length; ++i) {
        auto subset = vector<int>{};
        for(auto j=0; j<n; ++j) {
            if((i & 1 << j) > 0) {
                subset.push_back(j);
            }
            if(!((find(pwr_set.begin(), pwr_set.end(), subset) != pwr_set.end())
                 || subset.empty())) {
                pwr_set.push_back(subset);
            }
        }
    }
    return pwr_set;
}


template <class T>
vector<T> subset_from_indices(const vector<int> & indices, const vector<T> & tees) {
    auto subset = vector<T>(size(indices));
    for(auto i=0; i<size(indices); ++i) {
        subset[i] = tees[indices[i]];
    }
    return subset;
}


int build(int w, int e, const vector<Bridge> & bridges){
    auto cities_w = vector<int>{};
    auto cities_e = vector<int>{};
    auto tolls = vector<int>{};
    auto toll_sum = 0;
    for(auto i=0; i<size(bridges); ++i){
        cities_w.push_back(bridges[i][0]);
        cities_e.push_back(bridges[i][1]);
        tolls.push_back(bridges[i][2]);
    }
    auto pwr_set_indices = power_set_indices(size(bridges));
    auto toll_totals = vector<int>{};
    for(const auto& i : pwr_set_indices) {
        vector<Bridge> subset = subset_from_indices(i, bridges);
        if(!(any_bridges_intersect(subset) or
             any_bridges_share_city(subset_from_indices(i, cities_w),
                                    subset_from_indices(i, cities_e)))) {
            auto tolls_sub = subset_from_indices(i, tolls);
            toll_sum = accumulate(tolls_sub.begin(), tolls_sub.end(), 0);
            toll_totals.push_back(toll_sum);
        }
    }
    if(size(toll_totals) < 1){
        return 0;
    }
    return *max_element(toll_totals.begin(), toll_totals.end());
}
