// String Matching
// https://cses.fi/problemset/task/1753/

#include <bits/stdc++.h>
using namespace std;

/* some primes
1000000007, 1000000009
1000999949, 1001999939
1000999927, 1000999943
1909999999, 1999990999
1999999943, 1999909991
*/

const int MAX = int(1e6) + 9;
vector<long long> MOD = {1909999999, 1999990999};
vector<array<long long, 2>> pw(MAX), ipw(MAX);
array<long long, 2> bs = {137, 277};

long long BinExp(long long a, long long b, int t) {
  long long res = 1;
  while (b) {
    if (b & 1LL) (res *= a) %= MOD[t];
    (a *= a) %= MOD[t];
    b /= 2;
  }
  return res;
}

void Preprocess() {
  pw[0][0] = pw[0][1] = 1;
  for (int i = 1; i < MAX; i++) {
    (pw[i][0] = pw[i - 1][0] * bs[0]) %= MOD[0];
    (pw[i][1] = pw[i - 1][1] * bs[1]) %= MOD[1];
  }
  ipw[0][0] = ipw[0][1] = 1;
  long long ip1 = BinExp(bs[0], MOD[0] - 2, 0);
  long long ip2 = BinExp(bs[1], MOD[1] - 2, 1);
  for (int i = 1; i < MAX; i++) {
    ipw[i][0] = (ipw[i - 1][0] * ip1) % MOD[0];
    ipw[i][1] = (ipw[i - 1][1] * ip2) % MOD[1];
  }
}

struct Hashing {
  int n;
  vector<array<long long, 2>> hs;
  Hashing (string& s) {
    n = s.size();
    hs.resize(n + 1);
    for (int i = 0; i < n; i++) {
      (hs[i + 1][0] = hs[i][0] + (pw[i][0] * s[i]) % MOD[0]) %= MOD[0];
      (hs[i + 1][1] = hs[i][1] + (pw[i][1] * s[i]) % MOD[1]) %= MOD[1];
    }
  }
  array<long long, 2> get_hash(int l, int r) { // query 0 based
    l++, r++; // 1 basaed hash values
    long long res1 = ((hs[r][0] - hs[l - 1][0]) + MOD[0]) % MOD[0];
    long long res2 = ((hs[r][1] - hs[l - 1][1]) + MOD[1]) % MOD[1];
    (res1 *= ipw[l - 1][0]) %= MOD[0];
    (res2 *= ipw[l - 1][1]) %= MOD[1];
    return {res1, res2};
  }
};

auto Hash_Merge(array<long long, 2> left, array<long long, 2> right, int left_sz) {
  for (int i = 0; i < 2; i++) {
    (right[i] *= pw[left_sz][i]) %= MOD[i];
    (left[i] += right[i]) %= MOD[i];
  }
  return left;
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  string s, t; cin >> s >> t;
  int n = s.size(), m = t.size();
  Preprocess();
  Hashing sh(s), th(t);
  auto [t1, t2] = th.get_hash(0, m - 1);
  int cnt = 0;
  for (int i = 0; i + m <= n; i++) {
    auto [s1, s2] = sh.get_hash(i, i + m - 1);
    if (s1 == t1 && s2 == t2) cnt++;
  }
  cout << cnt << '\n';
  return 0;
}