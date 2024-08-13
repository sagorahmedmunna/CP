// Road Reparation
// https://cses.fi/problemset/task/1675

#include <bits/stdc++.h>
using namespace std;

struct DSU {
  vector<int> parent, sz;
  DSU(int n) {
    parent.resize(n + 1), sz.resize(n + 1, 1);
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }
  bool is_connected(int u, int v) {
    return find(u) == find(v);
  }
  void Merge(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
      if (sz[u] < sz[v]) swap(u, v);
      parent[v] = u;
      sz[u] += sz[v];
    }
  }
};

int main() {
  int n, m; cin >> n >> m;
  vector<tuple<int, int, int>> edges(m);
  for (auto& [w, u, v] : edges) {
    cin >> u >> v >> w;
    if (u > v) swap(u, v);
  }
  sort(edges.begin(), edges.end());
  
  DSU d;
  d.init(n);
  long long cost = 0;
  for (auto& [w, u, v] : edges) {
    if (d.is_connected(u, v)) continue;
    d.Merge(u, v);
    cost = cost + w;
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    cnt += i == d.find(i);
  }
  if (cnt > 1) {
    cout << "IMPOSSIBLE" << '\n';
  } else {
    cout << cost << '\n';
  }
  return 0;
}