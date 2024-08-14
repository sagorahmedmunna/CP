// Forest Queries
// https://cses.fi/problemset/task/1652/
 
#include <bits/stdc++.h>
using namespace std;

struct PrefixSum2D { // 1 based
  vector<vector<long long>> pf;
  PrefixSum2D(vector<vector<int>> &a) {
    int x = a.size(), y = a[0].size();
    pf.assign(x, vector<long long> (y));
    for (int i = 1; i < x; i++) {
      for (int j = 1; j < y; j++) {
        pf[i][j] = a[i][j];
        pf[i][j] += pf[i][j - 1] + pf[i - 1][j] - pf[i - 1][j - 1];
      }
    }
  }
  long long query(int x1, int y1, int x2, int y2) {
    return pf[x2][y2] - pf[x1 - 1][y2] - pf[x2][y1 - 1] + pf[x1 - 1][y1 - 1];
  }
};
 
int main() {
  int n, q;
  cin >> n >> q;
  vector<vector<int>> a(n + 1, vector<int> (n + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c; cin >> c;
      a[i][j] = (c == '*');
    }
  }
  PrefixSum2D ps2(a);
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << ps2.query(x1, y1, x2, y2) << '\n';
  }
  return 0;
}