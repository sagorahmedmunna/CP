#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
vector<int> adj[N], col(N), ans(N);
set<int> st[N];

void dfs(int u, int p) {
	st[u].insert(col[u]);
	for (auto& v : adj[u]) {
		if (v == p) continue;
		dfs(v, u);
		if (st[v].size() > st[u].size()) swap(st[v], st[u]);
		for (auto& c : st[v]) st[u].insert(c);
	}
	ans[u] = st[u].size();
}

int main() {
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		col[i] = x;
	}

	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, 1);

	for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}