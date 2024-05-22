using ll = long long;
const ll INF = 1e18 + 9;
const int N = 2e5 + 9;
vector<vector<pair<ll, ll>>> a(N);
vector<ll> dis(N, INF);
bool vis[N];

void dijkstra(int source) {
  dis[source] = 0;
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
  pq.push({0, source});

  while (!pq.empty()) {
    auto [w_u, u] = pq.top();
    pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto& [v, w_v] : a[u]) {
      if (w_u + w_v < dis[v]) {
        dis[v] = w_u + w_v;
        pq.push({dis[v], v});
      }
    }
  }
}