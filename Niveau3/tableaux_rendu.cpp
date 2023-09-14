#include <iostream>

using namespace std;

int NB_LIGNES, NB_COLONNES;
int NB_RECTANGLES;

int main()
{

    cin >> NB_LIGNES >> NB_COLONNES;
    cin >> NB_RECTANGLES;

    char grille[NB_LIGNES][NB_COLONNES];
    for (int i = 0; i < NB_LIGNES; i++)
    {
        for (int j = 0; j < NB_COLONNES; j++)
        {
            grille[i][j] = '.';
        }
    }

    int deb_ligne, fin_ligne, deb_col, fin_col;
    char texture;

    for (int rect = 0; rect < NB_RECTANGLES; rect++)
    {
        cin >> deb_ligne >> deb_col >> fin_ligne >> fin_col >> texture;

        for (int i = deb_ligne; i <= fin_ligne; i++)
        {
            for (int j = deb_col; j <= fin_col; j++)
            {
                grille[i][j] = texture;
            }
        }
    }

    for (int i = 0; i < NB_LIGNES; i++)
    {
        for (int j = 0; j < NB_COLONNES; j++)
        {
            cout << grille[i][j];
        }

        cout << '\n';
    }
};