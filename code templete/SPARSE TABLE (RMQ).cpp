// https://cses.fi/problemset/task/1647/
// Static Range Minimum Queries

#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
  int n = 1, LOG = 1;
  vector<vector<int>> st;
  SparseTable(vector<int>& a) {
    n = a.size();
    while ((1 << LOG) <= n) LOG++;
    st = vector<vector<int>> (n, vector<int> (LOG));
    for (int j = 0; j < LOG; j++) {
      for (int i = 0; i + (1 << j) - 1 < n; i++) {
        if (j == 0) st[i][j] = a[i];
        else st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int query(int l, int r) {
    int log = __lg(r - l + 1);
    return min(st[l][log], st[r - (1 << log) + 1][log]);
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, q; cin >> n >> q;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  SparseTable st(a);

  while (q--) {
    int l, r; cin >> l >> r;
    cout << st.query(l, r) << '\n';
  }
  return 0;
}