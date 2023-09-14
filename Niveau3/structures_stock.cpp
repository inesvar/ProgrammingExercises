#include <iostream>

using namespace std;

int main()
{

    int nb_produits;
    cin >> nb_produits;

    int stock[nb_produits];
    for (int i = 0; i < nb_produits; i++)
    {
        cin >> stock[i];
    }

    int nb_operations;
    cin >> nb_operations;

    int produit, quantite;
    for (int _ = 0; _ < nb_operations; _++)
    {
        cin >> produit >> quantite;
        stock[produit - 1] += quantite;
    }

    for (int i = 0; i < nb_produits; i++)
    {
        cout << stock[i] << " ";
    }
    cout << endl;

    return 0;
}