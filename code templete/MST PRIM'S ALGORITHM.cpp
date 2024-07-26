// https://cses.fi/problemset/task/1675/
// Road Reparation
// 1 based index

#include <bits/stdc++.h>
using namespace std;

array<long long, 2> prims(int n, vector<array<int, 2>>* adj) {
  priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;
  long long cost = 0, sz = 0;
  vector<int> vis(n + 1);
  vis[1] = 1;
  for (auto& [v, w] : adj[1]) {
    pq.push({w, 1, v});
  }
  while (!pq.empty()) {
    auto [w, u, v] = pq.top();
    pq.pop();
    if (vis[u] && vis[v]) continue;
    if (vis[u]) swap(u, v);
    vis[u] = 1;
    cost = cost + w;
    sz++;
    for (auto& [u_v, u_w] : adj[u]) {
      if (!vis[u_v]) {
        pq.push({u_w, u, u_v});
      }
    }
  }
  return {sz, cost};
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, m; cin >> n >> m;
  vector<array<int, 2>> adj[n + 1];
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  auto [sz, cost] = prims(n, adj);

  if (sz == n - 1) {
    cout << cost << '\n';
  } else {
    cout << "IMPOSSIBLE" << '\n';
  }
  return 0;
}