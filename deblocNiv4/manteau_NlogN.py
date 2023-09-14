
# NB_COATS * log NB_COATS complexity, FALSE

# INITIALIZATION
MAX_TEMP = 500_000_000
NB_COATS = int(input())

class CoatsCounter:

    def __init__(self):
        self.bound = [0, MAX_TEMP + 1]
        self.level = [0]
        self.nb_bounds = 2

    
    def add_coat(self, min_temp, max_temp):
        min_index = self.__add_bound(min_temp)
        max_index = self.__add_bound(max_temp)
        self.__add_level(min_index, max_index)

    def print(self):
        print("bounds ", self.bound)
        print("levels ", self.level)
        print()
        print()

    def max_level(self):
        return max(self.level) - 1

    def __add_bound(self, temp):
        closest_inferior_index = self.__find_closest_inferior_bound(temp)
        if self.bound[closest_inferior_index] == temp:
            return closest_inferior_index
        else:
            self.nb_bounds += 1
            self.bound.insert(closest_inferior_index + 1, temp)
            level = self.level[closest_inferior_index]
            self.level.insert(closest_inferior_index + 1, level)
            return closest_inferior_index + 1

    def __add_level(self, min_index, max_index):
        self.level[min_index : max_index] = \
            [1 + value for value in self.level[min_index : max_index]]


    def __find_closest_inferior_bound(self, temp):
        min_index = 0
        max_index = self.nb_bounds - 1
        while not max_index - min_index <= 1:
            mean_index = int(min_index / 2 + max_index / 2)
            if self.bound[mean_index] <= temp:
                min_index = mean_index
            else:
                max_index = mean_index

        return min_index
    
# COUNTING THE NUMBER OF COATS DEPENDING ON THEIR INTERVAL
coats_counter = CoatsCounter()
for coat in range(NB_COATS):
    inf, sup = map(int, input().split())
    coats_counter.add_coat(inf, sup)
    coats_counter.print()

print(coats_counter.max_level() )