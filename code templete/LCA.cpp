#include <bits/stdc++.h>
using namespace std;

struct DFS {
  int n, k, t = 0;
  vector<int> tin, tout, depth;
  vector<vector<int>> parent;
  DFS() {}
  DFS(vector<vector<int>>& adj, int root = 1) {
    n = (int)adj.size() + 1, k = __lg(n) + 1;
    tin.assign(n, 0), tout.assign(n, 0), depth.assign(n, 0);
    parent = vector<vector<int>> (n, vector<int> (k));
    dfs(root, root, adj);
  }
  void dfs(int u, int p, vector<vector<int>>& adj) {
    tin[u] = ++t;
    parent[u][0] = p;
    for (int i = 1; i < k; i++) {
      if (parent[u][i - 1] != -1) parent[u][i] = parent[parent[u][i - 1]][i - 1];
      else parent[u][i] = -1;
    }
    for (auto& v : adj[u]) {
      if (v != p) {
        depth[v] = depth[u] + 1;
        dfs(v, u, adj);
      }
    }
    tout[u] = ++t;
  }
  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  }
};

struct LCA {
  DFS tree;
  LCA(vector<vector<int>>& adj, int root = 1) : tree(adj, root) {}
  int lca(int u, int v) {
    if (tree.is_ancestor(u, v)) return u;
    for (int i = tree.k - 1; i >= 0; i--) {
      if (!tree.is_ancestor(tree.parent[u][i], v)) {
        u = tree.parent[u][i];
      }
    }
    return tree.parent[u][0];
  }
  int dis(int u, int v) {
    return tree.depth[u] + tree.depth[v] - 2 * tree.depth[lca(u, v)];
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n + 1, vector<int> ());
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  LCA tree(adj, 1);

  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << tree.lca(u, v) << '\n';
  }
  return 0;
}

// another approach
// make u and v to same depth then lift
// a little time consuming
int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int dis = depth[u] - depth[v];
  // kth parent
  for (int i = k - 1; i >= 0; i--) {
    if (dis & (1 << i)) {
      u = par[u][i];
    }
  }
  if (u == v) return u;
  for (int i = k - 1; i >= 0; i--) {
    if (par[u][i] != par[v][i]) {
      u = par[u][i];
      v = par[v][i];
    }
  }
  return par[u][0];
}