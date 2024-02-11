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
  ios_base::sync_with_stdio(0), cin.tie(0);
  
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