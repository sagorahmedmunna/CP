const int mod = (int)1e9 + 7;
const int N = (int)2e5 + 9;

int BinExp(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1) res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}

struct NCR {
  vector<long long> fact, inv;
  NCR(int n) {
    fact.assign(n + 1, 0), inv.assign(n + 1, 0);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
    inv[n] = BinExp(fact[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
      inv[i] = (inv[i + 1] * (i + 1)) % mod;
    }
  }
  int ncr(int n, int r) {
    if (n == r) return 1;
    if (n < r) return 0;
    return ((fact[n] * inv[r]) % mod * inv[n - r]) % mod;
  }
} comb(N);