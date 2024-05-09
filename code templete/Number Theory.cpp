const int N = 1e6 + 9;
vector<int> lpf(N), gpf(N);
map<int, int> factors[N];

// sieve for finding lowest prime and highest prime upto N
for (int i = 2; i < N; i++) {
  if (lpf[i] == 0) {
    for (int j = i; j < N; j += i) {
      gpf[j] = i;
      if (!lpf[j]) lpf[j] = i;
    }
  }
}
// find all factors upto N
for (int i = 2; i < N; i++) {
  int num = i;
  while (num > 1) {
    factors[i][lpf[num]]++;
    num /= lpf[num];
  }
}
int num = 10;
int total_divisors = 1;
long long sum_of_divisors = 1;
for (auto& [p, c] : factors[num]) {
  total_divisors *= (c + 1);
  sum_of_divisors *= (pow(p, c + 1) - 1) / (p - 1);
}


// (a * b) % p   (Binary Multiplication)
int BinMul(long long a, long long b, int mod) {
  int ans = 0;
  while (b) {
    if (b & 1) ans = (ans + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return ans;
}
// (a ^ b) % p   (Binary Exponentiation)
int BinExp(long long a, long long b, int mod) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = (ans * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return ans;
}
// (a / b) % p
BinMul(a, BinExp(b, p - 2, p), p);
// (a ^ (b ^ c)) % p
BinExp(a, BinExp(b, c, p - 1), p);

// NCR
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

// phi of single integer
int n = 10;
long long num = n;
long long phi_of_n = n;
for (long long i = 2; i * i <= num; i++) {
  if (num % i == 0) {
    while (num % i == 0) num /= i;
    phi_of_n -= phi_of_n / i;
  }
}
if (num > 1) phi_of_n -= phi_of_n / num;

// phi upto N
vector<int> phi(N);
// initial 0 to N
iota(phi.begin(), phi.end(), 0);
for (int i = 2; i < N; i++) {
  if (phi[i] == i) {
    for (int j = i; j < N; j += i) {
      phi[j] -= phi[j] / i;
    }
  }
}

// gcd sum -> ∑ gcd(i, n) for 1 <= i <= n; (n <= 1e9)
// gcd(1, n) + gcd(2, n) + .. + gcd(n, n)
long long sum = 0;
for (int i = 1; 1LL * i * i <= n; i++) {
  if (n % i == 0) {
    sum += i * phi(n / i);
    if (n / i != i) sum += (n / i) * phi(n / (n / i));
  }
}
// all pair gcd sum from 1 to N (N <= 4e6)
// ∑ i to n - 1, ∑ j + 1 to n [gcd(i, j)]
for (int i = 1; i < N; i++) {
  for (int j = i; j < N; j += i) sum[j] += i * phi[j / i];
}
for (int i = 1; i < N; i++) sum[i] += sum[i - 1] - i;


// lcm sum -> ∑ lcm(i, n) for 1 <= i <= n; (n <= 1e6)
// lcm(1, n) + lcm(2, n) + .. + lcm(n, n)
phi[1] = 2; // phi[1] should be 2 for this algorithm
for (int i = 1; i < N; i++) {
  for (int j = i; j < N; j += i) lcm_sum[j] += 1LL * j * phi[i] * i / 2;
}
// all pair lcm sum from 1 to N (N <= 1e6)
// ∑ i to n - 1, ∑ j + 1 to n [lcm(i, j)]
phi[1] = 2; // phi[1] should be 2 for this algorithm
for (int i = 1; i < N; i++) {
  for (int j = i; j < N; j += i) lcm_sum[j] += (long long) j * (1LL * i * phi[i] / 2);
}
for (int i = 1; i < N; i++) lcm_sum[i] += lcm_sum[i - 1] - i;