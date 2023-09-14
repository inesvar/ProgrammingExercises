# failing tests because it uses numpy

import numpy as np

# INITIALIZING

NB_LIGNES, NB_COLONNES  = map(int, input().split())

base_map = np.zeros((NB_LIGNES, NB_COLONNES), dtype=int)

for ligne in range(NB_LIGNES):
    m = map(int, input().split())
    base_map[ligne, :] = 1 - np.fromiter(m, dtype=int)

map = base_map
biggest_square = 0
nb_lignes = NB_LIGNES
nb_colonnes = NB_COLONNES

# UTILS

while np.any(map):
    biggest_square += 1
    nb_lignes -= 1
    nb_colonnes -= 1

    if NB_LIGNES <= biggest_square or NB_COLONNES <= biggest_square :
        break
    
    new_map = np.multiply(map[:, :-1], map[:, 1:])
    map = np.multiply(new_map[:-1, :], new_map[1:, :])
    #print(map)


print(biggest_square)



