# failing tests 15 to 20 included because of slowness

# INITIALIZING
NB_LIGNES, NB_COLONNES  = map(int, input().split())

base_map = [[] for i in range(NB_LIGNES)]

for ligne in range(NB_LIGNES):
    m = map(int, input().split())
    m = map(lambda a : 1 - a, m)
    m = list(m)
    base_map[ligne] = m

# VARIABLES
map = base_map
biggest_square = 0
nb_lignes = NB_LIGNES
nb_colonnes = NB_COLONNES

# RECURSION
while any(any(element == 1 for element in sublist) for sublist in map):
    #print("map ", map)
    biggest_square += 1
    nb_lignes -= 1
    nb_colonnes -= 1

    if NB_LIGNES < biggest_square or NB_COLONNES < biggest_square :
        break
    
    new_map = [[map[ligne][colonne] * map[ligne][colonne + 1] 
               for colonne in range(nb_colonnes)] for ligne in range(nb_lignes + 1)]
    map = [[new_map[ligne][colonne] * new_map[ligne + 1][colonne] 
               for colonne in range(nb_colonnes)] for ligne in range(nb_lignes)]


print(biggest_square)



