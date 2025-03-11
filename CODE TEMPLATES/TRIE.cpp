struct Trie {
  struct node {
    int word_cnt, pref_cnt;
    node* nxt[26];
    node() {
      word_cnt = pref_cnt = 0;
      for (int i = 0; i < 26; i++) {
        nxt[i] = NULL;
      }
    }
  };
  node* root;
  Trie() {
    root = new node();
  }
  void add(string& s) {
    node* it = root;
    for (auto& si : s) {
      int idx = si - 'a';
      if (it->nxt[idx] == NULL) {
        it->nxt[idx] = new node();
      }
      it = it->nxt[idx];
      it->pref_cnt++;
    }
    it->word_cnt++;
  }
  // returns the count of string
  int find(string& s) {
    node* it = root;
    for (auto& si : s) {
      int idx = si - 'a';
      if (it->nxt[idx] == NULL) return 0;
      it = it->nxt[idx];
    }
    return it->word_cnt;
  }
  int count_prefix(string& s) {
    node* it = root;
    for (auto& si : s) {
      int idx = si - 'a';
      if (it->nxt[idx] == NULL) return 0;
      it = it->nxt[idx];
    }
    return it->pref_cnt;
  }
  void erase(string& s) {
    if (find(s) == 0) return;
    node* it = root;
    for (auto& si : s) {
      int idx = si - 'a';
      it = it->nxt[idx];
      it->pref_cnt--;
    }
    it->word_cnt--;
  }
};

// iterative
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