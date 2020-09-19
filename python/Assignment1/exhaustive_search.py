

def bridges_intersect(b1: list, b2: list) -> bool:
    return (b2[0] > b1[0] and b2[1] < b1[1]) or \
           (b2[0] < b1[0] and b2[1] > b1[1])


def power_set(my_list):
    p_set = list()
    power_set_len = 1 << len(my_list) # 2^n
    for counter in range(0, power_set_len):
        subset = []
        for j in range(0, len(my_list)):
            # Check if jth bit in the counter is set with a
            # bitwise and between counter and 2**j.
            if (counter & (1 << j)) > 0:
                subset.append(my_list[j])
            if subset and subset not in p_set:
                p_set.append(subset)
    return p_set


bridge_1 = [4, 8]
bridge_2 = [6, 6]
print(bridges_intersect(bridge_1, bridge_2))

ex2 = [[0, 1, 3],
       [1, 1, 5],
       [1, 2, 4],
       [2, 0, 8],
       [2, 2, 6]]

print(power_set([i for i, _ in enumerate(ex2)]))
print(len(power_set([i for i, _ in enumerate(ex2)])))