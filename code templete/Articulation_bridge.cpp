#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
vector<int> adj[N];
int t = 0;
vector<int> tin(N, -1), low(N);
vector<array<int, 2>> ab;

void dfs (int u, int p) {
  tin[u] = low[u] = t++;
  for (int v: adj[u]) {
    if (v != p) {
      if (tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
      } else {
        dfs(v, u);
        if (tin[u] < low[v]) {
          ab.push_back({u, v});
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n, m; cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 1);

  for (auto& [i, j] : ab) {
    cout << i + 1 << ' ' << j + 1 << '\n';
  }

  return 0;
}