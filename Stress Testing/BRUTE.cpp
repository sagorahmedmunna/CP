#include <bits/stdc++.h>
using namespace std;

bool prime(int n) {
  if (n == 1) return 0;
  for (int i = 2; i * 1ll * i <= n; i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << (prime(n) ? "YES" : "NO") << '\n';
  }
  return 0;
}