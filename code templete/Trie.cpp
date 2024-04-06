const int N = 1e6 + 9, A = 26;
int nxt[N][A], cnt[N], node = 2;

void add(string& s) {
  int u = 1;
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) nxt[u][idx] = node++;
    u = nxt[u][idx];
    cnt[u]++;
  }
}

int cnt_pref(string& s) {
  int u = 1;
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) return 0;
    u = nxt[u][idx];
  }
  return cnt[u];
}