#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> subsets(vector<int>& arr) {
  int n = arr.size();
  vector<vector<int>> all_subsets;
  for (int mask = 0; mask < (1 << n); mask++) {
    vector<int> subset;
    for (int i = 0; i < n; i++) {
      if (mask & (1 << i)) {
        subset.push_back(arr[i]);
      }
    }
    all_subsets.push_back(subset);
  }
  return all_subsets;
}
int main() {
  int n; cin >> n;
  vector<int> arr(n);
  for (auto& ai : arr) cin >> ai;

  vector<vector<int>> all_subsets = subsets(arr);

  // printing all subsets
  cout << all_subsets.size() << '\n';
  for (auto& v : all_subsets) {
    for (auto& vi : v) cout << vi << ' ';
    cout << '\n';
  }
  return 0;
}

// iterative
vector<vector<int>> st = {{}};
for (int i = 1; i <= n; i++) {
  vector<vector<int>> temp = st;
  for (auto& v : temp) v.push_back(i);
  for (auto& v : temp) st.push_back(v);
}
for (auto& v : st) {
  for (auto& i : v) cout << i << ' ';
  cout << '\n';
}

// recursive
int arr[20];
bool is_taken[20];
vector<vector<int>> sub_seq;
int n;
void rec(int p) {
  if (p == n) {
    vector<int> temp;
    for (int i = 0; i < n; i++) {
      if (is_taken[i]) temp.push_back(arr[i]);
    }
    sub_seq.push_back(temp);
    return;
  }
  is_taken[p] = false; // do not take p'th position
  rec(p + 1);
  is_taken[p] = true; // take p'th position
  rec(p + 1);
}
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> arr[i];

  rec(0);

  for (auto& vec : sub_seq) {
    for (auto& el : vec) cout << el << ' ';
    cout << '\n';
  }
  return 0;
}