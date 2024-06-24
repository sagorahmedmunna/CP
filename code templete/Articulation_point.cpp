#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
vector<int> adj[N];
int t = 0;
vector<int> tin(N, -1), low(N), ap;
void dfs (int u, int p) {
  tin[u] = low[u] = t++;
  int is_ap = 0, child = 0;
  for (int v: adj[u]) {
    if (v != p) {
      if (tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
      } else {
        child++;
        dfs(v, u);
        if (tin[u] <= low[v]) {
          is_ap = 1;
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
  if ((u != p or child > 1) and is_ap) {
    ap.push_back(u);
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

  for (auto& i : ap) cout << i << ' ';
  cout << '\n';
	
  return 0;
}