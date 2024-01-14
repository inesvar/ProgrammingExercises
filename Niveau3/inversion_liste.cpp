#include <iostream>
#include <string>

using namespace std;

int main() {
   int n;
   cin >> n;

   string titre[n];
   getline(cin, titre[0]);
   for (int i = 0; i < n; i++) {
      getline(cin, titre[i]);
   }
   for (int i = n - 1; i >= 0; i--) {
      cout << titre[i] << endl;
   }
}