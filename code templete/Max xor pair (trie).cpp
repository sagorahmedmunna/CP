struct trie {
  trie* right = NULL;
  trie* left = NULL;
};

void insert(int num, trie* head) {
  trie* curr = head;
  for (int bit = 31; bit >= 0; bit--) {
    if ((num & (1 << bit)) == 0) {
      if (curr->left == NULL) curr->left = new trie();
      curr = curr->left;
    } else {
      if (curr->right == NULL) curr->right = new trie();
      curr = curr->right;
    }
  }
}

int max_xor(vector<int>& nums, trie* head) {
  int n = nums.size();
  int mx = 0;
  for (int i = 0; i < n; i++) {
    int curr_mx = 0;
    trie* curr = head;
    for (int bit = 31; bit >= 0; bit--) {
      bool take = 0;
      if ((nums[i] & (1 << bit)) == 0) {
        if (curr->right) {
          curr = curr->right;
          take = 1;
        } else {
          curr = curr->left;
        }
      } else {
        if (curr->left) {
          curr = curr->left;
          take = 1;
        } else {
          curr = curr->right;
        }
      }
      if (take) curr_mx += (1 << bit);
    }
    mx = max(mx, curr_mx);
  }
  return mx;
}

int findMaximumXOR(vector<int>& nums) {
  trie* head = new trie();
  int n = nums.size();
  for (int i = 0; i < n; i++) {
    insert(nums[i], head);
  }
  return max_xor(nums, head);
}