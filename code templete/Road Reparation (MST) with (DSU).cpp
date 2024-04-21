#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int size = 1;
  vector<int> parent, sz;
  void init(int n) {
    size = n;
    parent.resize(n + 1);
    sz.resize(n + 1);
    for (int u = 1; u <= n; u++) {
      parent[u] = u;
      sz[u] = 1;
    }
  }
  int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }
  bool is_connected(int u, int v) {
    return find(u) == find(v);
  }
  void Union(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (sz[u] < sz[v]) swap(u, v);
      parent[v] = u;
      sz[u] += sz[v];
    }
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
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
    d.Union(u, v);
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