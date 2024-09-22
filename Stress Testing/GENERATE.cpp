#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 2e5 + 9;

int rnd(int l, int r){
  return l + rng() % (r - l + 1);
}
int main() {
  int t = 1000;
  cout << t << '\n';
  for (int i = 1; i <= t; i++) {
    int n = rnd(1, 99999);
    cout << n << ' ';
  }
}