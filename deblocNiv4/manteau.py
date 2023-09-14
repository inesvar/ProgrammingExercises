# passes tests 1 to 4 and 15 to 17, all others fail bc of slowness
# NB_COATS ** 2 complexity
# other tries had complexity related to the size difference which was slow

# INITIALIZATION
NB_COATS = int(input())
interval_to_nb_coats = dict()
interval_sizes = set()

# COUNTING THE NUMBER OF COATS DEPENDING ON THEIR INTERVAL
for coat in range(NB_COATS):
    inf, sup = map(int, input().split())
    if not interval_sizes.__contains__(sup - inf):
        interval_sizes.add(sup - inf)
        interval_to_nb_coats[sup - inf] = {inf: 1}
        #print(interval_to_nb_coats)
    else:
        new_nb = interval_to_nb_coats[sup - inf].get(inf, 0)
        interval_to_nb_coats[sup - inf][inf] = new_nb + 1

# UTILS
def nb_strictly_contained(size: int, inf: int) -> int:
    if not size:
        return 0
    
    nb_strictly_contained = 0

    for size_index in range(size - 1, -1, -1):
        smaller_size_coats = interval_to_nb_coats.get(interval_sizes[size_index])

        #print("smaller size coats ", smaller_size_coats)
        for i in smaller_size_coats.keys():
            if i >= inf and i + interval_sizes[size_index] <= inf + interval_sizes[size]:
                nb_strictly_contained += smaller_size_coats[i]

    #print("stricly contained ", nb_strictly_contained)
    return nb_strictly_contained


interval_sizes = sorted(interval_sizes)
#print("interval sizes ", interval_sizes)
#print("dictionary ", interval_to_nb_coats)

# RECURSIVELY UPDATING THE NUMBER OF INFERIOR COATS
max_level = 0
for (size_index, size) in enumerate(interval_sizes):
    for inf in interval_to_nb_coats[size].keys():
        #print("size, inf ", size, inf)
        new_nb = interval_to_nb_coats[size][inf] + nb_strictly_contained(size_index, inf)
        if new_nb > max_level:
            max_level = new_nb



#print("dictionary ", interval_to_nb_coats)
#print("max_level ", max_level)
print(max_level - 1)


