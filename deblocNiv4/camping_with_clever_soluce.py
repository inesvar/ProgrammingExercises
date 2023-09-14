# SUCCESS ON ALL TESTS !
# thank you PascalOrtiz https://openclassrooms.com/forum/sujet/installation-du-camping

# INITIALIZING
NB_LINES, NB_COLUMNS  = map(int, input().split())
base_map = [[1 - int(a) for a in input().split()] for _ in range(NB_LINES)]

# LOOKING FOR THE BIGGEST SQUARE OF ONES
for line in range(NB_LINES):
    for column in range(NB_COLUMNS):
        if line * column:
            if base_map[line][column] > 0:
                base_map[line][column] = \
                (1 + min(base_map[line - 1][column - 1], base_map[line - 1][column], base_map[line][column - 1]))
            # the time doesn't really change when we switch the if statement for a multiplication
print(max(map(max, base_map)))



