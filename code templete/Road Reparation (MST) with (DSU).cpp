#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
int parent[N], sz[N];

void make(int u) {
  parent[u] = u;
  sz[u] = 1;
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

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, m; cin >> n >> m;
  vector<tuple<int, int, int>> edges(m);
  for (auto& [w, u, v] : edges) {
    cin >> u >> v >> w;
    if (u > v) swap(u, v);
  }
  sort(edges.begin(), edges.end());
  for (int i = 1; i <= n; i++) make(i);
  long long cost = 0;
  for (auto& [w, u, v] : edges) {
    if (is_connected(u, v)) continue;
    Union(u, v);
    cost = cost + w;
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    cnt += i == find(i);
  }
  if (cnt > 1) {
    cout << "IMPOSSIBLE" << '\n';
  } else {
    cout << cost << '\n';
  }
  return 0;
}