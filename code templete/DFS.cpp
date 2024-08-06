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
      if (parent[u][i - 1] != -1) parent[u][i] = parent[parent[u][i - 1]][i - 1];
      else parent[u][i] = -1;
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
        if (u == -1) return u;
      }
    }
    return u;
  }
};

int main() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n + 1, vector<int> ());
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  DFS tree(1, adj);
  return 0;
}