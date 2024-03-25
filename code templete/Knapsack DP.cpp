#include <bits/stdc++.h>
using namespace std;

const int N = 2009;
int weight[N], val[N];
int dp[N][N];
int n, total_weight;

int cal(int idx, int weight_left) {
  if (idx == n || weight_left == 0) return 0;
  if (dp[idx][weight_left] != -1) return dp[idx][weight_left];
  int ans = cal(idx + 1, weight_left);
  if (weight[idx] <= weight_left) {
    ans = max(ans, cal(idx + 1, weight_left - weight[idx]) + val[idx]);
  }
  return dp[idx][weight_left] = ans;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  memset(dp, -1, sizeof(dp));
  cin >> total_weight >> n;
  for (int i = 0; i < n; i++) {
    cin >> weight[i] >> val[i];
  }
  cout << cal(0, total_weight) << '\n';
  return 0;
}