// Dynamic Range Minimum Queries
// https://cses.fi/problemset/task/1649/

#include <bits/stdc++.h>
using namespace std;

template <class T> struct SegTreeIterative {
  int n = 1, neutral = INT_MAX; #change
  vector<T> st;
  SegTreeIterative(int _n) {
    n = _n;
    int tree_size = 1;
    while (tree_size < n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  T Merge(T& a, T& b) {
    return min(a, b);
  }
  void Build(vector<T>& a) { #change
    for (int i = 1; i <= n; ++i) {
      st[n + i] = a[i];
    }
    for (int u = n - 1; u > 0; --u) {
      st[u] = Merge(st[u << 1], st[u << 1 | 1]);
    }
  }
  void Update(int idx, int val) {
    st[idx += n] = val;
    for (idx /= 2; idx; idx /= 2) {
      st[idx] = Merge(st[idx << 1], st[idx << 1 | 1]);
    }
  }
  T Query(int l, int r) {
    T sum = neutral;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)  sum = Merge(sum, st[l++]);
      if (r & 1)  sum = Merge(sum, st[--r]);
    }
    return sum;
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
  
  SegTreeIterative<int> sg(n);
  sg.Build(a);

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int k, u;
      cin >> k >> u;
      sg.Update(k, u);
    } else {
      int a, b;
      cin >> a >> b;
      cout << sg.Query(a, b) << '\n';
    }
  }
  return 0;
}