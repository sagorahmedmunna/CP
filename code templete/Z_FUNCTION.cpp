#include <bits/stdc++.h>
using namespace std;

vector<int> get_z(string& s) { // 0 based
  int n = s.size(), l = 0, r = 0;
  vector<int> z(n);
  z[0] = n;
  for(int i = 1; i < n; i++) {
    if(i < r) z[i] = min(r - i, z[i - l]);
    while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if(i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}

int main() {
  string s; cin >> s;
  vector<int> z = get_z(s);
  for (int i = 0; i < s.size(); i++) cout << z[i] << ' ';
  cout << '\n';
  return 0;
}