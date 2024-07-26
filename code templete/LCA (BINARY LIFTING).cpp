const int N = 2e5 + 10, K = 20;
vector<int> adj[N], tin(N), tout(N), depth(N);
int t, par[N][K];

void dfs(int u, int p) {
  tin[u] = t++;
  par[u][0] = p;
  for (int k = 1; k < K; k++) {
    par[u][k] = par[par[u][k - 1]][k - 1];
  }
  for (auto& v : adj[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
  tout[u] = t++;
}

bool is_anc(int u, int v) {
  return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
  if (is_anc(u, v)) return u;
  for (int k = K - 1; k >= 0; k--) {
    if (!is_anc(par[u][k], v)) {
      u = par[u][k];
    }
  }
  return par[u][0];
}

int dis(int u, int v) {
  return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

// another approach
// make u and v to same depth then lift
int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int k = depth[u] - depth[v];
  for (int i = K - 1; i >= 0; i--) {
    if (k & (1 << i)) {
      u = par[u][i];
    }
  }
  if (u == v) return u;
  for (int i = K - 1; i >= 0; i--) {
    if (par[u][i] != par[v][i]) {
      u = par[u][i];
      v = par[v][i];
    }
  }
  return par[u][0];
}