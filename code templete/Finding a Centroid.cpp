#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
vector<int> adj[N];
int sz[N];
int n;

void cal_sz(int u, int p) {
  sz[u] = 1;
  for (auto& v : adj[u]) {
    if (v == p) continue;
    cal_sz(v, u);
    sz[u] += sz[v]; 
  }
}

int get_cen(int u, int p) {
  for (auto& v : adj[u]) {
    if (v == p) continue;
    if (sz[v] > n / 2) {
      return get_cen(v, u);
    }
  }
  return u;
}

int main() {
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cal_sz(1, 1);
  int cen = get_cen(1, 1);
  cout << cen << '\n';
  return 0;
}