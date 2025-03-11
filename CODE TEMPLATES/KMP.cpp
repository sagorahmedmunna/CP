vector<int> get_pi(string& s) {
  int n = s.size();
  vector<int> pi(n);
  for (int i = 1, j = 0; i < n; i++) {
    if (s[i] == s[j]) pi[i] = ++j;
    else if (j == 0) pi[i] = 0;
    else j = pi[j - 1], i--;
  }
  return pi;
}

// count the number of p occurs in s
string s, p;
s = p + "#" + s;
vector<int> pi = get_pi(s);
int ans = 0;
for (auto& i : pi) ans += (i == p.size());