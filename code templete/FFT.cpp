// POLYMUL - Polynomial Multiplication
// https://www.spoj.com/problems/POLYMUL/

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);
struct cplx {
  double a, b;
  cplx(double a = 0, double b = 0) : a(a), b(b) {}
  const cplx operator + (const cplx &c) const { return cplx(a + c.a, b + c.b); }
  const cplx operator - (const cplx &c) const { return cplx(a - c.a, b - c.b); }
  const cplx operator * (const cplx &c) const { return cplx(a * c.a - b * c.b, a * c.b + b * c.a); }
  const cplx operator / (const double &d) const { return cplx(a / d, b / d); }
};

void fft(vector<cplx> &p, bool inv = 0) {
  int n = p.size(), i = 0;
  for (int j = 1; j < n - 1; ++j) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if(j < i) swap(p[i], p[j]);
  }
  for (int l = 1, m; (m = l << 1) <= n; l <<= 1) {
    double ang = 2 * PI / m;
    cplx wn = cplx(cos(ang), (inv ? 1. : -1.) * sin(ang)), w;
    for (int i = 0, j, k; i < n; i += m) {
      for (w = cplx(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn) {
        cplx t = w * p[j + l];
        p[j + l] = p[j] - t;
        p[j] = p[j] + t;
      }
    }
  }
  if (inv) {
    for (int i = 0; i < n; ++i) p[i] = p[i] / n;
  }
}

vector<long long> multiply(vector<int> &a, vector<int> &b) {
  int n = a.size(), m = b.size(), sz = 1;
  while(sz < n + m - 1) sz <<= 1;
  vector<cplx> x(sz), y(sz), z(sz);
  for(int i = 0 ; i < sz; i++) {
    x[i] = i < n ? cplx(a[i], 0) : cplx(0, 0);
    y[i] = i < m ? cplx(b[i], 0) : cplx(0, 0);
  }
  fft(x), fft(y);
  for(int i = 0; i < sz; i++) z[i] = x[i] * y[i];
  fft(z, 1);
  vector<long long> c(n + m - 1);
  for(int i = 0; i < n + m - 1; i++) c[i] = (long long)round(z[i].a);
  return c;
}

void test() {
  int n; cin >> n;
  vector<int> a(n + 1), b(n + 1);
  for (auto& ai : a) cin >> ai;
  for (auto& bi : b) cin >> bi;
  auto c = multiply(a, b);
  for (auto& ci : c) cout << ci << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t = 1; 
  cin >> t;
  for (int i = 1; i <= t; i++) {
    test();
  }
  return 0;
}