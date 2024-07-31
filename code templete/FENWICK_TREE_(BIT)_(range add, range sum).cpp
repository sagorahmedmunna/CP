// Range Update Queries
// https://cses.fi/problemset/task/1651/

#include <bits/stdc++.h>
using namespace std;
 
struct FenWick {
  int size;
  vector<long long> bit;
  FenWick() {}
  FenWick(int n) {
    size = n;
    bit.assign(n + 1, 0);
  }
  void add(int idx, long long val) {
    while (idx <= size) {
      bit[idx] += val;
      idx += idx & -idx;
    }
  }
  void add(int l, int r, long long val) {
    add(l, val);
    add(r + 1, -val);
  }
  long long query(int idx) {
    long long res = 0;
    while (idx > 0) {
      res += bit[idx];
      idx -= idx & -idx;
    }
    return res;
  }
  long long query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

struct FenWickLazy {
  FenWick bitAdd, bitSub;
  FenWickLazy(int n) : bitAdd(n), bitSub(n) {}
  void add(int l, int r, int val) {
    bitAdd.add(l, r, val);
    bitSub.add(l, r, 1LL * (l - 1) * val);
    bitSub.add(r + 1, 1LL * (-r + l - 1) * val);
  }
  long long query(int idx) {
    return idx * bitAdd.query(idx) - bitSub.query(idx);
  }
  long long query(int l, int r) {
    return query(r) - query(l - 1);
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

  FenWickLazy sg(n);
  for (int i = 1; i <= n; i++) {
    sg.add(i, i, a[i]);
  }
 
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r, val;
      cin >> l >> r >> val;
      sg.add(l, r, val);
    } else {
      int k;
      cin >> k;
      cout << sg.query(k, k) << '\n';
    }
  }
  return 0;
}