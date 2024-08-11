// D - Cuboid Sum Query
// https://atcoder.jp/contests/abc366/tasks/abc366_d

#include <bits/stdc++.h>
using namespace std;

struct PrefixSum3D { // 1 based
  vector<vector<vector<long long>>> pf;
  PrefixSum3D(vector<vector<vector<int>>> &a) {
    int x = a.size(), y = a[0].size(), z = a[0][0].size();
    pf = vector<vector<vector<long long>>> (x, vector<vector<long long>> (y, vector<long long> (z)));
    for (int i = 1; i < x; i++) {
      for (int j = 1; j < y; j++) {
        for (int k = 1; k < z; k++) {
          pf[i][j][k] = a[i][j][k];
          pf[i][j][k] += pf[i - 1][j][k] + pf[i][j - 1][k] + pf[i][j][k - 1];
          pf[i][j][k] -= pf[i - 1][j - 1][k] + pf[i - 1][j][k - 1] + pf[i][j - 1][k - 1];
          pf[i][j][k] += pf[i - 1][j - 1][k - 1];
        }
      }
    }
  }
  long long query(int x1, int y1, int z1, int x2, int y2, int z2) {
    long long sum = pf[x2][y2][z2];
    sum -= pf[x1 - 1][y2][z2] + pf[x2][y1 - 1][z2] + pf[x2][y2][z1 - 1];
    sum += pf[x1 - 1][y1 - 1][z2] + pf[x1 - 1][y2][z1 - 1] + pf[x2][y1 - 1][z1 - 1];
    sum -= pf[x1 - 1][y1 - 1][z1 - 1];
    return sum;
  }
};

int main() {
  int n;
  cin >> n;
  vector<vector<vector<int>>> a(n + 1, vector<vector<int>> (n + 1, vector<int> (n + 1)));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        cin >> a[i][j][k];
      }
    }
  }
  PrefixSum3D ps3(a);
  int q;
  cin >> q;
  while (q--) {
    int lx, rx, ly, ry, lz, rz;
    cin >> lx >> rx >> ly >> ry >> lz >> rz;
    cout << ps3.query(lx, ly, lz, rx, ry, rz) << '\n';
  }
  return 0;
}
