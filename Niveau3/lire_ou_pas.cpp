#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {

   int nb_of_books;
   cin >> nb_of_books;
   cin.ignore();

   vector<string> titles;
   string title;
   getline(cin, title);
   titles.push_back(title);
   for (int i = 1; i < nb_of_books; i++) {
      getline(cin, title);
      if (title > titles.back()) {
         titles.push_back(title);
      }
   }

   for (auto i = titles.begin(); i != titles.end(); i++) {
    cout << *i << endl;
   }
   return 0;
}