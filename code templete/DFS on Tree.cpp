#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, K = 20;
vector<int> adj[N], tin(N), tout(N), dep(N), height(N), parent(N);
vector<int> is_leaf(N, 1),subtree_size(N);
int one_cut_subtree_size_difference = -1;
int t, n;

void dfs(int u, int p) {
    tin[u] = t++;
    parent[u] = p;
    for (auto& v : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        is_leaf[u] = 0;
        dfs(v, u);
        height[v] = max(height[v], height[u] + 1);
        subtree_size[u] += subtree_size[v] + 1;
    }
    one_cut_subtree_size_difference = min(abs(subtree_size[u] - (n - subtree_size[u])), one_cut_subtree_size_difference);
    tout[u] = t++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}