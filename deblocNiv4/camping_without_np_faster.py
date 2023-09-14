# failing tests 13 to 20 included because of slowness

# INITIALIZING
NB_LINES, NB_COLUMNS  = map(int, input().split())

base_map = [[] for _ in range(NB_LINES)]

for ligne in range(NB_LINES):
    m = map(int, input().split())
    m = list(m)
    base_map[ligne] = m

# VARIABLES
MAX_SQUARE_SIDE = min(NB_LINES, NB_COLUMNS)
max_square_side, min_square_side = MAX_SQUARE_SIDE + 1, 0

# UTILS
def exist_square(base_map, square_side: int) -> bool:
    if NB_LINES < square_side or NB_COLUMNS < square_side :
        return False
    
    if not square_side:
        return all(all(element == 1 for element in sublist[column: column + square_side])
                    for sublist in base_map[line: line + square_side])

    
    nb_lines = NB_LINES - square_side + 1
    nb_columns = NB_COLUMNS - square_side + 1

    for line in range(nb_lines):
        for column in range(nb_columns):
            if all(all(element == 0 for element in sublist[column: column + square_side])
                    for sublist in base_map[line: line + square_side]):
                return True

    return False

# DICHOTOMY
while max_square_side != min_square_side + 1:
    mean = int((max_square_side + min_square_side) * 2 / 3)
    if exist_square(base_map, mean):
        min_square_side = mean
    else:
        max_square_side = mean


print(min_square_side)



