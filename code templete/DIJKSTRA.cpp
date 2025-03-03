// Shortest Routes I
// https://cses.fi/problemset/task/1671/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1.1e17;

vector<ll> Dijkstra(vector<vector<array<ll, 2>>>& adj, int source = 1) {
  int n = (int)adj.size();
  vector<ll> dis(n, INF);
  vector<bool> vis(n);
  dis[source] = 0;
  priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
  pq.push({0, source});
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto& [v, c] : adj[u]) {
      if (dis[v] > d + c) {
        dis[v] = d + c;
        pq.push({dis[v], v});
      }
    }
  }
  return dis;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, m;
  cin >> n >> m;
  vector<vector<array<long long, 2>>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    adj[u].push_back({v, c});
    // #for undirected
    //adj[v].push_back({u, c});
  }
  auto dis = Dijkstra(adj);
  for (int i = 1; i <= n; i++) {
    cout << dis[i] << ' ';
  }
  cout << '\n';
  return 0;
}