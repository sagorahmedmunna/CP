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
  int Find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = Find(parent[u]);
  }
  bool Is_connected(int u, int v) {
    return Find(u) == Find(v);
  }
  void Merge(int u, int v) {
    u = Find(u), v = Find(v);
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
    if (d.Is_connected(u, v)) continue;
    d.Merge(u, v);
    cost = cost + w;
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    cnt += i == d.Find(i);
  }
  if (cnt > 1) {
    cout << "IMPOSSIBLE" << '\n';
  } else {
    cout << cost << '\n';
  }
  return 0;
}