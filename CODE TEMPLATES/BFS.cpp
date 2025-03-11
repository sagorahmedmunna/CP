const int N = 2e5 + 9;
vector<int> adj[N];
int depth[N], parent[N];
bool vis[N];

void bfs(int root) {
  queue<int> q;
  q.push(root);
  vis[root] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto& v : adj[u]) {
      if (vis[v]) continue;
      vis[v] = 1;
      depth[v] += depth[u] + 1;
      parent[v] = u;
      q.push(v);
    }
  }
}