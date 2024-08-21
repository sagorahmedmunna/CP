// Range Update Queries
// https://cses.fi/problemset/task/1651/

#include <bits/stdc++.h>
using namespace std;
 
struct FenWickTree {
  int n;
  vector<long long> ft;
  FenWickTree() {}
  FenWickTree(int n) { Initial(n); }
  FenWickTree(vector<int>& a) {
    Initial((int)a.size());
    Build(a);
  }
  void Initial(int _n) {
    n = _n;
    ft.assign(n + 1, 0);
  }
  void Build(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
      Add(i, i, a[i]); #change
    }
  }
  void Add(int idx, long long val) {
    for (int i = idx; i <= n; i += i & -i) {
      ft[i] += val;
    }
  }
  void Add(int l, int r, long long val) {
    Add(l, val);
    Add(r + 1, -val);
  }
  long long Csum(int idx) {
    long long res = 0;
    for (int i = idx; i > 0; i -= i & -i) {
      res += ft[i];
    }
    return res;
  }
  long long Rsum(int l, int r) {
    return Csum(r) - Csum(l - 1);
  }
};

struct FenWickTreeLazy {
  FenWickTree bitAdd, bitSub;
  FenWickTreeLazy(int n) : bitAdd(n), bitSub(n) {}
  void Add(int l, int r, int val) {
    bitAdd.Add(l, r, val);
    bitSub.Add(l, r, 1LL * (l - 1) * val);
    bitSub.Add(r + 1, 1LL * (-r + l - 1) * val);
  }
  long long Query(int idx) {
    return idx * bitAdd.Csum(idx) - bitSub.Csum(idx);
  }
  long long Query(int l, int r) {
    return Query(r) - Query(l - 1);
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  FenWickTreeLazy sg(n);
  for (int i = 1; i <= n; i++) {
    sg.Add(i, i, a[i]);
  }
 
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r, val;
      cin >> l >> r >> val;
      sg.Add(l, r, val);
    } else {
      int k;
      cin >> k;
      cout << sg.Query(k, k) << '\n';
    }
  }
  return 0;
}