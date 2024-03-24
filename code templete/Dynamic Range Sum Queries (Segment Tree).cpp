#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
long long a[N], st[4 * N];

void build(int u, int s, int e) {
  if (s == e) {
    st[u] = a[s];
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  build(v, s, m);
  build(w, m + 1, e);
  st[u] = st[v] + st[w];
}

void update(int u, int s, int e, int k, int val) {
  if (s == e) {
    st[u] = a[s] = val;
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  if (k <= m) update(v, s, m, k, val);
  else update(w, m + 1, e, k, val);
  st[u] = st[v] + st[w];
}

long long query(int u, int s, int e, int l, int r) {
  if (e < l || r < s) return 0;
  if (l <= s && e <= r) return st[u];
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  long long lsum = query(v, s, m, l, r);
  long long rsum = query(w, m + 1, e, l, r);
  return lsum + rsum;
}

int main() {
	int n, q; cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];

	build(1, 1, n);

	while (q--) {
    int type; cin >> type;
    if (type == 2) {
      int l, r; cin >> l >> r;
      cout << query(1, 1, n, l, r) << '\n';
    } else {
      int k, u; cin >> k >> u;
      update(1, 1, n, k, u);
    }
	}
}