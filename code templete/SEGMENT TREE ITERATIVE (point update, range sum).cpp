// Dynamic Range Sum Queries
// https://cses.fi/problemset/task/1648

#include <bits/stdc++.h>
using namespace std;

struct SegTreeIterative {
  int n = 1;
  vector<long long> st;
  SegTreeIterative(int _n) {
    n = _n;
    int tree_size = 1;
    while (tree_size < n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  void build(vector<int>& a) {
    for (int i = 1; i <= n; ++i) {
      st[n + i] = a[i];
    }
    for (int u = n - 1; u > 0; --u) {
      st[u] = st[u << 1] + st[u << 1 | 1];
    }
  }
  void update(int idx, int val) {
    st[idx += n] = val;
    for (idx /= 2; idx; idx /= 2) {
      st[idx] = st[idx << 1] + st[idx << 1 | 1];
    }
  }
  long long query(int l, int r) {
    long long sum = 0;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)  sum += st[l++];
      if (r & 1)  sum += st[--r];
    }
    return sum;
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, q;
  cin >> n >> q;
  
  SegTreeIterative sg(n);
  for (int i = 1; i <= n; i++) {
    int ai;
    cin >> ai;
    sg.update(i, ai);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int k, u;
      cin >> k >> u;
      sg.update(k, u);
    } else {
      int a, b;
      cin >> a >> b;
      cout << sg.query(a, b) << '\n';
    }
  }
  return 0;
}