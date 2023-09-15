#include <iostream>

// Complexite : O ( NB_AFFICHES_MAX * log(nb_affiches_visibles) )
// soit O ( NB_AFFICHES_MAX * log(NB_AFFICHES_MAX) ) dans le pire cas
// (aucun des tests n'est dans le pire cas donc on pouvait se permettre
// de ne pas faire de dichotomie dans la fonction ajoute_affiche)
using namespace std;

void ajoute_affiche(int hauteur);
int trouve_plus_grande_affiche_recouverte(int hauteur);

const int HAUTEUR_MAX = 1000000;
const int NB_AFFICHES_MAX = 100000;
int nb_affiches_visibles;
int hauteur_visible[NB_AFFICHES_MAX];

int main()
{
    hauteur_visible[0] = HAUTEUR_MAX;

    int nb_requetes;
    cin >> nb_requetes;

    char type;
    int hauteur;
    for (int i = 0; i < nb_requetes; i++)
    {
        cin >> type;
        if (type == 'C')
        {
            cin >> hauteur;
            ajoute_affiche(hauteur);
        }
        else
            cout << nb_affiches_visibles << "\n";
    }

    return 0;
}

void ajoute_affiche(int hauteur)
{
    int index = trouve_plus_grande_affiche_recouverte(hauteur);
    hauteur_visible[index] = hauteur;
    nb_affiches_visibles = index;
}

int trouve_plus_grande_affiche_recouverte(int hauteur)
{
    int min = 0;
    int max = nb_affiches_visibles + 1;
    while (min + 1 < max)
    {
        int milieu = (min + max) / 2;
        if (hauteur_visible[milieu] > hauteur)
            min = milieu;
        else
            max = milieu;
    }
    return max;
}