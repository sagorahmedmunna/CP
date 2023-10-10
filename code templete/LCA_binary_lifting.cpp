#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, K = 20;
vector<int> adj[N], tin(N), tout(N), dep(N);
int t, par[N][K];

void dfs(int u, int p) {
    tin[u] = t++;
    par[u][0] = p;
    for (int k = 1; k < K; k++) {
        par[u][k] = par[par[u][k - 1]][k - 1];
    }
    for (auto& v : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
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
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}