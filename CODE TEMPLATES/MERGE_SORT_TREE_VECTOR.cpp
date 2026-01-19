struct MergeSortTree {
  int size = 1;
  vector<vector<int>> st;
  vector<vector<long long>> pref;
  MergeSortTree(int n) {
    size = n;
    int tree_size = 1;
    while (tree_size < n) tree_size *= 2;
    st.resize(tree_size * 2);
    pref.resize(tree_size * 2);
  }
  void build(int u, int s, int e, vector<int>& a) {
    if (s == e) {
      st[u].push_back(a[s]);
      pref[u].push_back(0);
      pref[u].push_back(a[s]);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    build(v, s, m, a);
    build(w, m + 1, e, a);
    st[u].resize(st[v].size() + st[w].size());
    merge(st[v].begin(), st[v].end(), st[w].begin(), st[w].end(), st[u].begin());
    pref[u].resize(st[v].size() + st[w].size() + 1);
    for (int i = 0; i < st[v].size() + st[w].size(); i++) {
      pref[u][i + 1] = pref[u][i] + st[u][i];
    }
  }
  void build(vector<int>& a) {
    build(1, 1, size, a);
  }
  long long query(int u, int s, int e, long long l, long long r, long long val) {
    if (e < l || r < s) {
      return 0LL;
    }
    if (l <= s && e <= r) {
      int i = upper_bound(st[u].begin(), st[u].end(), val) - st[u].begin();
      return pref[u][i];
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    long long lsum = query(v, s, m, l, r, val);
    long long rsum = query(w, m + 1, e, l, r, val);
    return lsum + rsum;
  }
  long long query(long long l, long long r, long long val) {
    return query(1, 1, size, l, r, val);
  }
};