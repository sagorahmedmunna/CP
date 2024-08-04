#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
int a[N], st[N * 4];

void update(int u, int s, int e, int k, int val) {
  if (s == e) {
    st[u] += val;
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  if (k <= m) update(v, s, m, k, val);
  else update(w, m + 1, e, k, val);
  st[u] = st[v] + st[w];
}

int query(int u, int s, int e, int l, int r) {
  if (e < l || r < s) return 0;
  if (l <= s && e <= r) return st[u];
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  int lsum = query(v, s, m, l, r);
  int rsum = query(w, m + 1, e, l, r);
  return lsum + rsum;
}

int main() {
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<tuple<int, int, int>> queries(q);
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    queries[i] = {r, l, i};
  }
  sort(queries.begin(), queries.end());

  vector<int> ans(q);
  map<int, int> last_idx;
  int curr_idx = 1;

  for (int i = 0; i < q; i++) {
    int l = get<1>(queries[i]);
    int r = get<0>(queries[i]);
    int idx = get<2>(queries[i]);
    while (curr_idx <= r) {
      if (last_idx[a[curr_idx]] != 0) {
        update(1, 1, n, last_idx[a[curr_idx]], -1);
        last_idx[a[curr_idx]] = curr_idx;
      }
      last_idx[a[curr_idx]] = curr_idx;
      update(1, 1, n, curr_idx, 1);
      curr_idx++;
    }
    ans[idx] = query(1, 1, n, l, r);
  }
  
  for (auto& i : ans) cout << i << '\n';
  return 0;
}