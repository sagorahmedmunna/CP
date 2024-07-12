// p[0][i] = half length of longest even palindrome around pos i-1, i and starts at i-p[0][i] and ends at i+p[0][i]-1
// p[1][i] = longest odd (half rounded down) palindrome around pos i and starts at i-p[1][i] and ends at i+p[1][i]
vector<vector<int>> manacher(string &s) {
  int n = s.size();
  vector<vector<int>> p(2, vector<int> (n));
  for (int z = 0; z < 2; z++) {
    for (int i = 0, l = 0, r = 0; i < n; i++) {
      int t = r - i + !z;
      if (i < r) {
        p[z][i] = min(t, p[z][l + t]);
      }
      int L = i - p[z][i], R = i + p[z][i] - !z;
      while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) {
        p[z][i]++, L--, R++;
      }
      if (R > r) {
        l = L, r = R;
      }
    }
  }
  return p;
}

// l[2 * i] = len of palindrome centered at s[i]
// l[2*i+1] = len of palindrome centered at s[i], s[i+1]
vector<int> manacher1(string &s) {
  int n = s.size();
  vector<int> l(2 * n); 
  for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0)) {
    while (i >= j && i + j + 1 < n * 2 && s[(i - j) / 2] == s[(i + j + 1) / 2]) ++j;
    l[i] = j;
    for (k = 1; i >= k && j >= k && l[i - k] != j - k; ++k) {
      l[i + k] = min(l[i - k], j - k);
    }
  }
  return l;
}