const int mod = 1e9 + 7;

int BinExp(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = (ans * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return ans;
}

struct NCR{
  vector<long long> fact, inv;
  int sz;
  void init(int n) {
    sz = n;
    fact.assign(sz, 0);
    inv.assign(sz, 0);
    fact[0] = 1;
    for(int i = 1; i < sz; i++){
      fact[i] = fact[i - 1] * i;
      fact[i] %= mod;
    }
    inv[n - 1] = BinExp(fact[n - 1], mod - 2);
    for(int i = sz - 2; i >= 0; i--){
      inv[i] = inv[i + 1] * (i + 1);
      inv[i] %= mod;
    }
  }
  int ncr(int n, int r){
    if(n == r)return 1;
    if(n < r)return 0;
    return ((fact[n] * inv[r]) % mod * inv[n - r]) % mod;
  }
};