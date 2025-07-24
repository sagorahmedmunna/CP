// 0 based
array<vector<int>, 2> distinctElementFromI(vector<int>& a) {
  int n = a.size(), mxidx = -1;
  map<int, int> mp;
  vector<int> l(n);
  for (int i = 0; i < n; i++) {
    if (mp.count(a[i])) mxidx = max(mxidx, mp[a[i]]);
    mp[a[i]] = i, l[i] = i - mxidx;
  }
  mp.clear(), mxidx = n;
  vector<int> r(n);
  for (int i = n - 1; i >= 0; i--) {
    if (mp.count(a[i])) mxidx = min(mxidx, mp[a[i]]);
    mp[a[i]] = i, r[i] = mxidx - i;
  }
  return {l, r};
}