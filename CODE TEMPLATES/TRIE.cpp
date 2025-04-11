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
int nxt[N][A], pref_cnt[N], word_cnt[N], node = 2;
void add(string& s) {
  int u = 1;
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) nxt[u][idx] = node++;
    u = nxt[u][idx];
    pref_cnt[u]++;
  }
  word_cnt[u]++;
}
int cnt_pref(string& s) {
  int u = 1;
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) return 0;
    u = nxt[u][idx];
  }
  return pref_cnt[u];
}
int find(string& s) {
  int u = 1;
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) return 0;
    u = nxt[u][idx];
  }
  return word_cnt[u];
}
void erase(string& s) {
  if (find(s) == 0) return;
  int u = 1;
  for (auto& c : s) {
    int idx = c - 'a';
    int v = nxt[u][idx];
    if(--pref_cnt[v] == 0) {
      nxt[u][idx] = 0 ;
      return;
    }
    u = v;
  }
}

// trie integer iterative (max xor)
const int N = 2e5 * 31 + 9, A = 2;
int nxt[N][A], pref_cnt[N], int_cnt[N], node = 2;
void add_int(int num) {
  int u = 1;
  for (int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    if (!nxt[u][idx]) nxt[u][idx] = node++;
    u = nxt[u][idx];
    pref_cnt[u]++;
  }
  int_cnt[u]++;
}
int find(int num) {
  int u = 1;
  for (int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    if (!nxt[u][idx]) return 0;
    u = nxt[u][idx];
  }
  return int_cnt[u];
}
void erase_int(int num) {
  if (find(num) == 0) return;
  int u = 1;
  for(int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    int v = nxt[u][idx];
    if(--pref_cnt[v] == 0) {
      nxt[u][idx] = 0 ;
      return;
    }
    u = v;
  }
}
int max_xor(int num) {
  int res = 0, u = 1;
  for (int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    int flip = idx ^ 1;
    if (nxt[u][flip] && pref_cnt[nxt[u][flip]]) {
      res += (1 << bit);
      u = nxt[u][flip];
    } else {
      u = nxt[u][idx];
    }
  }
  return res;
}