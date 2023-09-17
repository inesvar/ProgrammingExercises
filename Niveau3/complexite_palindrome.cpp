#include <iostream>
#include <string>
#include <vector>

/*
Trouver la taille du plus long palindrome dans une chaine de N characteres.

Le code est en O( N ) en utilisant l'algorithme de Manacher. 
*/
using namespace std;

inline int min(int a, int b);
string intercalerCharactere(string mot);

int MAX_LENGTH = 20000;
vector<int> plusLongPalindrome;

int main()
{
    string mot;
    getline(cin, mot);

    mot = intercalerCharactere(mot);

    int taille = mot.length();
    int centre = 0;
    int rayon = 0;
    int longueurMax = 0;

    while (centre < taille)
    {
        int rayonMax = min(centre, taille - 1 - centre);
        while ((rayon < rayonMax) && (mot[centre - rayon - 1] == mot[centre + rayon + 1]))
        {
            rayon++;
        }

        plusLongPalindrome.push_back(rayon);

        if (rayon > longueurMax)
            longueurMax = rayon;

        int precedentCentre = centre;
        int precedentRayon = rayon;
        centre++;
        rayon = 0;

        while (centre <= precedentCentre + precedentRayon)
        {
            int rayonMaxDansPrecedentPalindrome = precedentCentre + precedentRayon - centre;
            int centreMiroir = precedentCentre - (centre - precedentCentre);

            if (plusLongPalindrome[centreMiroir] < rayonMaxDansPrecedentPalindrome)
                plusLongPalindrome.push_back(plusLongPalindrome[centreMiroir]);
            else if (plusLongPalindrome[centreMiroir] > rayonMaxDansPrecedentPalindrome)
                plusLongPalindrome.push_back(rayonMaxDansPrecedentPalindrome);
            else
            {
                rayon = plusLongPalindrome[centreMiroir];
                break;
            }

            centre++;
        }
    }

    cout << longueurMax << endl;

    return 0;
}

inline int min(int a, int b)
{
    return (a < b) ? a : b;
}

string intercalerCharactere(string mot)
{
    string motRemanie = ".";
    for (auto i = mot.begin(); i < mot.end(); ++i)
    {
        motRemanie.push_back(*i);
        motRemanie.push_back('.');
    }
    return motRemanie;
}