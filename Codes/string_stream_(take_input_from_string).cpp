#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  string s;
  getline(cin, s);
  stringstream custom_in(s);
  string word;
  int count_word = 0;
  while (custom_in >> word) {
    count_word++;
  }
  cout << count_word << '\n';
  return 0;
}