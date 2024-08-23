// Shortest Routes II
// https://cses.fi/problemset/task/1672/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1.1e17;

void FloydWarshall(vector<vector<long long>>& adj) {
  int n = (int)adj.size();
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        adj[i][i] = 0;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, m, q;
  cin >> n >> m >> q;
  vector<vector<long long>> adj(n + 1, vector<long long> (n + 1, INF));
  for (int i = 0; i < m; i++) {
    long long a, b, c;
    cin >> a >> b >> c;
    adj[a][b] = adj[b][a] = min(adj[a][b], c);
  }
  FloydWarshall(adj);
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << (adj[a][b] == INF ? -1 : adj[a][b]) << '\n';
  }
  return 0;
}