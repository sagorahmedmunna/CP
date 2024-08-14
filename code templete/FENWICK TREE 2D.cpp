// Forest Queries II
// https://cses.fi/problemset/task/1739/

#include <bits/stdc++.h>
using namespace std;
 
struct FenWick2D {
  int n, m;
  vector<vector<long long>> ft;
  FenWick2D() {}
  FenWick2D(int _n, int _m) {
    n = _n, m = _m;
    ft.assign(n + 1, vector<long long> (m + 1));
  }
  void Add(int x, int y, long long val) {
    for(int i = x; i <= n; i += i & -i) {
      for(int j = y; j <= m; j += j & -j) {
        ft[i][j] += val;
      }
    }
  }
  long long Csum(int x, int y) {
    long long res = 0;
    for(int i = x; i > 0; i -= i & -i) {
      for(int j = y; j > 0; j -= j & -j) {
        res += ft[i][j];
      }
    }
    return res;
  }
  long long Rsum(int x1, int y1, int x2, int y2) {
    return Csum(x2, y2) - Csum(x1 - 1, y2) - Csum(x2, y1 - 1) + Csum(x1 - 1, y1 - 1);
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, q;
  cin >> n >> q;
  FenWick2D fw2d(n, n);
  vector<vector<int>> a(n + 1, vector<int> (n + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c; cin >> c;
      if (c == '*') {
        a[i][j] = 1;
        fw2d.Add(i, j, 1);
      }
    }
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int x, y;
      cin >> x >> y;
      if (a[x][y] == 1) {
        fw2d.Add(x, y, -1);
        a[x][y] = 0;
      } else {
        fw2d.Add(x, y, 1);
        a[x][y] = 1;
      }
    } else {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      cout << fw2d.Rsum(x1, y1, x2, y2) << '\n';
    }
  }
  return 0;
}