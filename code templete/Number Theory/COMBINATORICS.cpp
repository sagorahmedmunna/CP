const int mod = (int)1e9 + 7;
const int N = (int)2e5 + 9;

struct Combinatorics {
  vector<long long> fact, inv, ifact;
  Combinatorics(int n) {
    fact.assign(n + 1, 1), inv.assign(n + 1, 1), ifact.assign(n + 1, 1);
    inv[0] = 0;
    for (int i = 2; i <= n; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
    for (int i = 2; i <= n; i++) {
      inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    }
    for (int i = 2; i <= n; i++) {
      ifact[i] = (ifact[i - 1] * inv[i]) % mod;
    }
  }
  int nPr(int n, int r) { // Permutations
    if (n < r) return 0;
    return (fact[n] * ifact[n - r]) % mod;
  }
  int nCr(int n, int r) { // Combinations
    return (nPr(n, r) * ifact[r]) % mod;
  }
} comb(N);