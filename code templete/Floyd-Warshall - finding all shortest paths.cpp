const INF = 1e9 + 9;
vector<vector<int>> d(n, vector<int> (n, INF));
for (int i = 0; i < m; i++) {
  int u, v, dis; cin >> u >> v >> dis;
  d[u][v] = d[v][u] = dis;
}
for (int k = 0; k < n; ++k) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      // d[i][i] = 0; #if doesn’t have self loop
    }
  }
}
// distance from i to j = d[i][j]