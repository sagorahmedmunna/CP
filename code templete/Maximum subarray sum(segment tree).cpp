#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
int a[N];

struct item {
  long long sum, pref, suff, ans;
};

item st[N * 4];

item merge(item l, item r) {
  item res;
  res.sum = l.sum + r.sum;
  res.pref = max(l.pref, l.sum + r.pref);
  res.suff = max(r.suff, r.sum + l.suff);
  res.ans = max({l.ans, r.ans, l.suff + r.pref});
  return res;
}

item make_item(int val) {
  item res;
  res.sum = val;
  res.pref = res.suff = res.ans = max(0, val);
  return res;
}

void build(int u, int s, int e) {
  if (s == e) {
    st[u] = make_item(a[s]);
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  build(v, s, m);
  build(w, m + 1, e);
  st[u] = merge(st[v], st[w]);
}

void update(int u, int s, int e, int k, int val) {
  if (s == e) {
    st[u] = make_item(val);
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  if (k <= m) update(v, s, m, k, val);
  else update(w, m + 1, e, k, val);
  st[u] = merge(st[v], st[w]);
}

item query(int u, int s, int e, int l, int r) {
  if (e < l || r < s) {
    item mx = make_item(0);
    return mx;
  }
  if (l <= s && e <= r) return st[u];
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  item lsum = query(v, s, m, l, r);
  item rsum = query(w, m + 1, e, l, r);
  return merge(lsum, rsum);
}

int main() {
	int n, q; cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];

	build(1, 1, n);

	while (q--) {
    int type; cin >> type;
    if (type == 1) {
      int k, v; cin >> k >> v;
      update(1, 1, n, k, v);
    } else {
      int l, r; cin >> l >> r;
      cout << query(1, 1, n, l, r).ans << '\n';
    }
	}
}