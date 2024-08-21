// Path Queries II
// https://cses.fi/problemset/task/2134/

#include <bits/stdc++.h>
using namespace std;

template <class T> struct SegmentTreeIterative {
  int n = 1;
  vector<T> st;
  SegmentTreeIterative() {}
  SegmentTreeIterative(int n) { Initial(n); }
  SegmentTreeIterative(vector<int>& a) {
    Initial((int)a.size() - 1);
    Build(a);
  }
  void Initial(int _n) {
    n = _n;
    int tree_size = 1;
    while (tree_size < n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  int neutral = 0; #change
  T Merge(T& a, T& b) { #change
    return max(a, b);
  }
  void Build(vector<int>& a) {
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
    T res = neutral;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = Merge(res, st[l++]);
      if (r & 1) res = Merge(res, st[--r]);
    }
    return res;
  }
};

struct HeavyLightDecomposition {
  int t = 0;
  vector<int> tin, depth, subtree_size, parent, heavy, head, euler;
  SegmentTreeIterative<int> sg;
  HeavyLightDecomposition(int root, vector<vector<int>>& adj, vector<int>& values) {
    int n = (int)adj.size() + 1;
    tin.resize(n), depth.resize(n), subtree_size.resize(n), parent.resize(n), heavy.assign(n, -1), head.resize(n), euler.resize(n);
    Dfs(root, root, adj);
    Decompose(root, root, adj, values);
    sg = SegmentTreeIterative<int> (euler);
  }
  void Dfs(int u, int p, vector<vector<int>>& adj) {
    subtree_size[u] = 1;
    parent[u] = p;
    for (auto& v : adj[u]) {
      if (v != p) {
        depth[v] = depth[u] + 1;
        Dfs(v, u, adj);
        subtree_size[u] += subtree_size[v];
        if (heavy[u] == -1 || subtree_size[heavy[u]] < subtree_size[v]) {
          heavy[u] = v;
        }
      }
    }
  }
  void Decompose(int u, int h, vector<vector<int>>& adj, vector<int>& values) {
    tin[u] = ++t;
    euler[t] = values[u];
    head[u] = h;
    if (heavy[u] != -1) {
      Decompose(heavy[u], h, adj, values);
    }
    for (auto& v : adj[u]) {
      if (v != parent[u] && v != heavy[u]) {
        Decompose(v, v, adj, values);
      }
    }
  }
  void Update(int u, int val) {
    sg.Update(tin[u], val);
  }
  int neutral = 0; #change
  int Merge(int a, int b) {
    return max(a, b); #change
  }
  int PathQuery(int a, int b) {
    int res = neutral;
    for (; head[a] != head[b]; b = parent[head[b]]) {
      if (depth[head[a]] > depth[head[b]]) {
        swap(a, b);
      }
      res = Merge(res, sg.Query(tin[head[b]], tin[b]));
    }
    if (depth[a] > depth[b]) {
      swap(a, b);
    }
    res = Merge(res, sg.Query(tin[a], tin[b]));
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    int ai;
    cin >> ai;
    a[i] = ai;
  }
  vector<vector<int>> adj(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  HeavyLightDecomposition hld(1, adj, a);
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int u, val;
      cin >> u >> val;
      hld.Update(u, val);
    } else {
      int u, v;
      cin >> u >> v;
      cout << hld.PathQuery(u, v) << ' ';
    }
  }
  cout << '\n';
  return 0;
}