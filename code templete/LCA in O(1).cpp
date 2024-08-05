// Company Queries II
// https://cses.fi/problemset/task/1688/
// Eulerian Method 

#include <bits/stdc++.h>
using namespace std;

struct RMQ {
  int n = 1, LOG = 1;
  vector<vector<array<int, 2>>> st;
  RMQ() {}
  RMQ(vector<array<int, 2>>& a) {
    n = a.size();
    LOG = __lg(n) + 1;
    st = vector<vector<array<int, 2>>> (n, vector<array<int, 2>> (LOG));
    for (int j = 0; j < LOG; j++) {
      for (int i = 0; i + (1 << j) - 1 < n; i++) {
        if (j == 0) st[i][j] = a[i];
        else st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int query(int l, int r) {
    int log = __lg(r - l + 1);
    return min(st[l][log], st[r - (1 << log) + 1][log])[1];
  }
};

struct LCAinO1 {
  int n, LOG, t = 0;
  vector<int> tin, depth;
  vector<array<int, 2>> euler;
  RMQ st;
  LCAinO1(int root, vector<vector<int>>& adj) {
    n = (int)adj.size() + 1;
    tin.assign(n, 0), depth.assign(n, 0), euler.assign(2 * n, {0, 0});
    dfs(root, root, adj);
    st = RMQ(euler);
  }
  void dfs(int u, int p, vector<vector<int>>& adj) {
    tin[u] = ++t;
    euler[t] = {depth[u], u};
    for (auto& v : adj[u]) {
      if (v != p) {
        depth[v] = depth[u] + 1;
        dfs(v, u, adj);
        euler[++t] = {depth[u], u};
      }
    }
  }
  int lca(int u, int v) {
    int l = tin[u], r = tin[v];
    if (l > r) swap(l, r);
    return st.query(l, r);
  }
  int dis(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n + 1);
  for (int u = 2; u <= n; u++) {
    int v;
    cin >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  LCAinO1 tree(1, adj);

  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << tree.lca(a, b) << '\n';
  }
  return 0;
}