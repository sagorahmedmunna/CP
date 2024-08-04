#include <bits/stdc++.h>
using namespace std;

struct DFS {
  int n, k, t = 0;
  vector<int> tin, tout, depth, height, subtree_size;
  vector<bool> is_leaf;
  vector<vector<int>> parent;
  DFS() {}
  DFS(int root, vector<vector<int>>& adj) {
    n = (int)adj.size() + 1;
    k = __lg(n) + 1;
    tin.assign(n, 0), tout.assign(n, 0), depth.assign(n, 0), height.assign(n, 0), subtree_size.assign(n, 0), is_leaf.assign(n, 1);
    parent = vector<vector<int>> (n, vector<int> (k));
    dfs(root, root, adj);
  }
  void dfs(int u, int p, vector<vector<int>>& adj) {
    tin[u] = ++t;
    subtree_size[u] = 1;
    parent[u][0] = p;
    for (int i = 1; i < k; i++) {
      parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (auto& v : adj[u]) {
      if (v != p) {
        depth[v] = depth[u] + 1;
        is_leaf[u] = 0;
        dfs(v, u, adj);
        height[u] = max(height[u], height[v] + 1);
        subtree_size[u] += subtree_size[v];
      }
    }
    tout[u] = ++t;
  }
  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  }
  int kth_parent(int u, int kth) {
    for (int i = k - 1; i >= 0; i--) {
      if (kth & (1 << i)) {
        u = parent[u][i];
      }
    }
    return u;
  }
};

struct LCA {
  DFS tree;
  LCA(int root, vector<vector<int>>& adj) : tree(root, adj) {}
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
  for (int i = 1; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  LCA tree(0, adj);

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