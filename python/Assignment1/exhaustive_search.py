import math


def two_bridges_intersect(b1: list, b2: list) -> bool:
    return (b2[0] > b1[0] and b2[1] < b1[1]) or \
           (b2[0] < b1[0] and b2[1] > b1[1])


def any_bridges_intersect(bridges: list) -> bool:
    for i in range(0, len(bridges) - 1):
        for j in range(1, len(bridges)):
            if two_bridges_intersect(bridges[i], bridges[j]):
                return True
    return False


def any_bridges_share_city(bridges) -> bool:
    cities_w = [item[0] for item in bridges]
    cities_e = [item[1] for item in bridges]
    return len(cities_e) != len(set(cities_e)) or \
           len(cities_w) != len(set(cities_w))


def power_set_indices(list_len):
    p_set = []
    power_set_len = 1 << list_len  # 2^n
    for i in range(1, power_set_len):
        subset = []
        for j in range(0, list_len):
            # Check if jth bit in i is set with a
            # bitwise AND between counter and 2^j.
            if (i & (1 << j)) > 0:
                subset.append(j)
            if subset and subset not in p_set:
                p_set.append(subset)
    return p_set


def build(bridges):
    pwr_set_indices = power_set_indices(len(bridges))
    for p in pwr_set_indices:
        print(p)
    toll_totals = dict()
    for subset in pwr_set_indices:
        sub = [bridges[index] for index in subset]
        if not (any_bridges_intersect(sub) or any_bridges_share_city(sub)):
            tolls = math.fsum([index[2] for index in sub])
            toll_totals.update({tolls: sub})
    return [max(toll_totals), toll_totals[max(toll_totals)]]

ex2 = [[0, 1, 3],
       [1, 1, 5],
       [1, 2, 4],
       [2, 0, 8],
       [2, 2, 6]]

ex3 = [[0, 0, 3],
       [1, 1, 5],
       [2, 2, 4],
       [3, 3, 8],
       [4, 4, 6]]

ex4 = [[0, 0, 3],
       [1, 1, 5],
       [2, 2, 4],
       [3, 3, 8],
       [4, 2, 6]]

ex5 = [[0, 0, 9],
       [0, 3, 8],
       [0, 0, 15]]

# pwr_set = power_set_indices(len(ex2))
# print(pwr_set)
# print(len(pwr_set))

# print(any_bridges_share_city(ex2))
# print(any_bridges_share_city(ex3))

# print(f"any_bridges_intersect(ex2): {any_bridges_intersect(ex2)}")
# print(f"any_bridges_intersect(ex3): {any_bridges_intersect(ex3)}")
# print(f"any_bridges_intersect(ex4): {any_bridges_intersect(ex4)}")

best_bridges = build(ex5)
print(f"Max toll is ${best_bridges[0]}0, using bridges {best_bridges[1]}")
