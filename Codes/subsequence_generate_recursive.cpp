#include <bits/stdc++.h>
using namespace std;

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