#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
const int mod = 1e9 + 7;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  // calculate prefix difference
  vector<int> a;
  a.push_back(1);
  while (a.size() < N) {
    int n = a.size();
    while (true) {
      n /= 2;
      for (int i = n, j = 0; j < n; i++, j++) {
        a.push_back((a[i] * 2) % mod);
      }
      if (n == 0) break;
    }
    a.push_back(2);
  }
  // prefix sum
  for (int i = 1; i < N; i++) {
    a[i] = (a[i] + a[i - 1]) % mod;
  }

  // test case
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    cout << a[n] << '\n';
  }
  return 0;
}