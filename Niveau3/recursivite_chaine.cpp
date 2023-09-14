#include <iostream>
#include <string>

using namespace std;

void retourne_affiche(string mot);

int main()
{
    string mot;
    getline(cin, mot);
    retourne_affiche(mot);
    cout << endl;
    return 0;
}

void retourne_affiche(string mot)
{
    if (mot.length() > 1)
    {
        retourne_affiche(mot.substr(1));
    }
    cout << mot[0];
}