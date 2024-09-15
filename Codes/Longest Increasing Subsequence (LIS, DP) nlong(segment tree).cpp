#include <bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 9;
int st[N * 4];
 
void update(int u, int s, int e, int k, int val) {
  if (s == e) {
    st[u] = val;
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  if (k <= m) update(v, s, m, k, val);
  else update(w, m + 1, e, k, val);
  st[u] = max(st[v], st[w]);
}

int query(int u, int s, int e, int l, int r) {
  if (e < l || r < s) return 0;
  if (l <= s && e <= r) return st[u];
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  long long lmax = query(v, s, m, l, r);
  long long rmax = query(w, m + 1, e, l, r);
  return max(lmax, rmax);
}
 
void compress(vector<int> &a) {
  auto b = a;
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  for (auto &ai: a) {
    ai = lower_bound(b.begin(), b.end(), ai) - b.begin() + 1;
  }
}
 
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n; cin >> n;
  vector<int> a(n);
  for (auto& i : a) cin >> i;
  
  compress(a);
 
  for (int i = 0; i < n; i++) {
    int mx = query(1, 1, n, 1, a[i] - 1) + 1;
    update(1, 1, n, a[i], mx);
  }
  cout << st[1] << '\n';
  return 0;
}