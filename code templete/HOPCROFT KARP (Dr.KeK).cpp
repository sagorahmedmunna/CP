// Dr.KeK (1 based)
// add_edge(u, v) -> u = left graph, r = right graph
// O(√V * E)
struct HopcroftKarp {
  int n, m;
  vector<vector<int>> graph;
  vector<int> pairU, pairV, dist;
  HopcroftKarp(int n, int m) : n(n), m(m) {
    graph.resize(n + 1);
    pairU.assign(n + 1, -1);
    pairV.assign(m + 1, -1);
    dist.resize(n + 1);
  }
  void add_edge(int u, int v) {
    graph[u].push_back(v);
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (pairU[u] == -1) {
        dist[u] = 0;
        q.push(u);
      } else {
        dist[u] = -1;
      }
    }
    bool found_augmenting_path = false;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : graph[u]) {
        if (pairV[v] == -1) {
          found_augmenting_path = true;
        } else if (dist[pairV[v]] == -1) {
          dist[pairV[v]] = dist[u] + 1;
          q.push(pairV[v]);
        }
      }
    }
    return found_augmenting_path;
  }
  bool dfs(int u) {
    for (int v : graph[u]) {
      if (pairV[v] == -1 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
        pairU[u] = v;
        pairV[v] = u;
        return true;
      }
    }
    dist[u] = -1;
    return false;
  }
  int max_matching() {
    int matching = 0;
    while (bfs()) {
      for (int u = 1; u <= n; u++) {
        if (pairU[u] == -1 && dfs(u)) {
          matching++;
        }
      }
    }
    return matching;
  }
};