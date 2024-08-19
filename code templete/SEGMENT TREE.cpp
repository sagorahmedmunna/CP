// Subarray Sum Queries
// https://cses.fi/problemset/task/1190

#include <bits/stdc++.h>
using namespace std;
 
struct SegmentTree {
  struct node { #change
    long long sum, pref, suff, ans;
    node() {
      sum = pref = suff = ans = 0;
    }
  };
  int size = 1;
  vector<node> st;
  SegmentTree(int n) {
    size = n;
    int tree_size = 1;
    while (tree_size < n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  node make_node(int val) { #change
    node res;
    res.sum = val;
    res.pref = res.suff = res.ans = max(0, val);
    return res;
  }
  node Merge(node& l, node& r) { #change
    node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
  }
  void build(int u, int s, int e, vector<int>& a) {
    if (s == e) { #change
      st[u] = make_node(a[s]);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    build(v, s, m, a);
    build(w, m + 1, e, a);
    st[u] = Merge(st[v], st[w]);
  }
  void build(vector<int>& a) {
    build(1, 1, size, a);
  }
  void update(int u, int s, int e, int k, int val) {
    if (s == e) { #change
      st[u] = make_node(val);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    if (k <= m) update(v, s, m, k, val);
    else update(w, m + 1, e, k, val);
    st[u] = Merge(st[v], st[w]);
  }
  void update(int k, int val) {
    update(1, 1, size, k, val);
  }
  node query(int u, int s, int e, int l, int r) {
    if (e < l || r < s) { #change
      return node();
    }
    if (l <= s && e <= r) return st[u];
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    node lsum = query(v, s, m, l, r);
    node rsum = query(w, m + 1, e, l, r);
    return Merge(lsum, rsum);
  }
  node query(int l, int r) {
    return query(1, 1, size, l, r);
  }
};
 
int main() {
  int n, q; cin >> n >> q;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
 
  SegmentTree sg(n);
  sg.build(a);
 
  while (q--) {
    int k, v; cin >> k >> v;
    sg.update(k, v);
    cout << sg.st[1].ans << '\n';
  }
}