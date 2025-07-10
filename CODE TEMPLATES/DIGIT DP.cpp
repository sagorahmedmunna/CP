#include <bits/stdc++.h>
using namespace std;

//-> for case of 0 use 'started' state

string s;
int n;

#1 countTotalOccurrencesOfADigit // f(0, 0, 1, 0)
int targetDigit, dp[11][11][2][2];
int f(int i, int cnt, int tight, int started) {
  if (i == n) {
    return started ? cnt : 0;
  }
  auto& ret = dp[i][cnt][tight][started];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newStarted = started || (d > 0);
    int newCnt = cnt;
    if (newStarted) newCnt += d == targetDigit;
    ret += f(i + 1, newCnt, newTight, newStarted);
  }
  return ret;
}

#2 countWithExactDigitCount // f(0, 0, 1, 0)
int dp[11][11][2][2];
int targetDigit, targetCnt;
int f(int i, int digitCnt, int tight, int started) {
  if (i == n) {
    return targetCnt == digitCnt;
  }
  auto& ret = dp[i][digitCnt][tight][started];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newStarted = started || (d > 0);
    int newDigitCnt = digitCnt;
    if (newStarted) newDigitCnt += (d == targetDigit);
    ret += f(i + 1, newDigitCnt, newTight, newStarted);
  }
  return ret;
}

#3 countWithSumDivisibleByK // f(0, 0, 1)
int dp[11][101][2];
int k;
int f(int i, int sum, int tight) {
  if (i == n) {
    return sum == 0;
  }
  auto& ret = dp[i][sum][tight];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newSum = (sum + d) % k;
    ret += f(i + 1, newSum, newTight);
  }
  return ret;
}

#4 countWithSumInRange // f(0, 0, 1)
int dp[11][200][2];
int mn, mx;
int f(int i, int sum, int tight) {
  if (i == n) {
    return (sum >= mn) && (sum <= mx);
  }
  auto& ret = dp[i][sum][tight];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newSum = (sum + d);
    if (newSum <= mx) {
      ret += f(i + 1, newSum, newTight);
    }
  }
  return ret;
}

#5 countEqualEvenOddSum // f(0, 100, 1)
int dp[11][201][2];
int f(int i, int sum, int tight) {
  if (i == n) {
    return sum == 100;
  }
  auto& ret = dp[i][sum][tight];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newSum = sum;
    if(d & 1) newSum -= d;
    else newSum += d;
    ret += f(i + 1, newSum, newTight);
  }
  return ret;
}

#6 countNumbersWithOnly1234 // f(0, 1, 0)
int dp[11][2][2];
int f(int i, int tight, int started) {
  if (i == n) {
    return started;
  }
  auto& ret = dp[i][tight][started];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newStarted = started || (d > 0);
    if (d > 4) continue;
    if (!newStarted && d == 0) ret += f(i + 1, newTight, newStarted);
    else if (d >= 1 && d <= 4) ret += f(i + 1, newTight, newStarted);
  }
  return ret;
}

#7 countNumbersWithExactlyOne1234 // f(0, 0, 1)
int dp[11][1009][2];
const int target = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
int f(int i, int mask, int tight) {
  if (i == n) return mask == target;
  auto& ret = dp[i][mask][tight];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newMask = mask;
    if (d >= 1 && d <= 4) {
      if ((mask & (1 << d)) == 0) {
        newMask |= (1 << d);
      } else {
        continue;
      }
    }
    ret += f(i + 1, newMask, newTight);
  }
  return ret;
}

#8 countDistinctDigitNumbers // f(0, 0, 1, 0)
int dp[11][1025][2][2];
int f(int i, int mask, int tight, int started) {
  if (i == n) return started;
  auto& ret = dp[i][mask][tight][started];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newStarted = started || (d > 0);
    int newMask = mask;
    if (newStarted) {
      if (mask & (1 << d)) continue;
      newMask |= (1 << d);
    }
    ret += f(i + 1, newMask, newTight, newStarted);
  }
  return ret;
}
#9 countWithAnyRepeatedDigits -> n - f(countDistinctDigitNumbers)

#10 countNumbersWithKDistinctDigits // f(0, 0, 1, 0)
int k, dp[11][1025][2][2];
int f(int i, int mask, int tight, int started) {
  if (i == n) return started && (__builtin_popcount(mask) == k);
  auto& ret = dp[i][mask][tight][started];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newStarted = started || (d > 0);
    int newMask = mask;
    if (newStarted) newMask |= (1 << d);
    ret += f(i + 1, newMask, newTight, newStarted);
  }
  return ret;
}

#11 count Numbers Divisible By k and Contains No Digit m // f(0, 0, 1, 0)
int dp[11][100][2][2];
int k, m;
int f(int i, int rem, int tight, int started) {
  if (i == n) return started && (rem == 0);
  auto& ret = dp[i][rem][tight][started];
  if (~ret) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    if (d == m) continue;
    int newTight = tight && (d == limit);
    int newStarted = started || (d > 0);
    int newRem = (rem * 10 + d) % k;
    ret += f(i + 1, newRem, newTight, newStarted);
  }
  return ret;
}

--> find sum and conunt at same time
#12 sum and count of all numbers x that has at most k distinct digits // f(0, 0, 1, 0)
const int mod = 998244353;
int64_t n, k, Pow10[20];
array<int64_t, 2> dp[20][1025][2][2]; // dp[0] -> cnt, dp[1] -> sum;
string s;
array<int64_t, 2> f(int i, int mask, int tight, int started) {
  if (i == n) {
    return {started && (__builtin_popcount(mask) <= k), 0};
  }
  auto& ret = dp[i][mask][tight][started];
  if (~ret[0]) return ret;
  ret = {0, 0};
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    int newStarted = started || (d > 0);
    int newMask = mask;
    if (newStarted) newMask |= (1 << d);
    auto [currCnt, currSum] = f(i + 1, newMask, newTight, newStarted);
    auto& [cnt, sum] = ret;
    cnt = (cnt + currCnt) % mod;
    sum = (sum + (currCnt * d % mod) * Pow10[n - i - 1] % mod) % mod;
    sum = (sum + currSum) % mod;
  }
  return ret;
}
int64_t Cnt(int64_t num) {
  if (num <= 0) return 0;
  memset(dp, -1, sizeof dp);
  s = to_string(num);
  n = s.size();
  Pow10[0] = 1;
  for (int i = 1; i < 20; i++) {
    Pow10[i] = (Pow10[i - 1] * 10) % mod;
  }
  return f(0, 0, 1, 0)[1];
}

// Optimized versions -->

## with only 1 memset, reverse the number then calculate from (n - 1) ->
## so when some state is already calculated and tight == 0, then return 'ret', or else again calculate the state

#13 count of 3 = 6 = 9, and count of 3 > 0
const int mod = 1e9 + 7, N = 17;
string s;
int dp[51][N][N][N][2]; // f(s.size() - 1, 0, 0, 0, 1)
int f(int i, int three, int six, int nine, int tight) {
  if (three > 16 || six > 16 || nine > 16) return 0;
  if (i < 0) {
    return (three > 0) && (three == six) && (six == nine);
  }
  auto& ret = dp[i][three][six][nine][tight];
  if (ret != -1 && !tight) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    ret = (ret + f(i - 1, three + (d == 3), six + (d == 6), nine + (d == 9), newTight)) % mod;
  }
  return ret;
}
// optimized, without tight state
// when the state is not tight then return 'ret' also memoize the dp;
int dp[51][N][N][N];
int f(int i, int three, int six, int nine, int tight) {
  if (three > 16 || six > 16 || nine > 16) return 0;
  if (i < 0) {
    return (three > 0) && (three == six) && (six == nine);
  }
  auto ret = dp[i][three][six][nine];
  if (ret != -1 && !tight) return ret;
  ret = 0;
  int limit = tight ? (s[i] - '0') : 9;
  for (int d = 0; d <= limit; d++) {
    int newTight = tight && (d == limit);
    ret = (ret + f(i - 1, three + (d == 3), six + (d == 6), nine + (d == 9), newTight)) % mod;
  }
  if (!tight) dp[i][three][six][nine] = ret;
  return ret;
}
int Cnt(string a) {
  reverse(a.begin(), a.end());
  s = a;
  return f(s.size() - 1, 0, 0, 0, 1);
}
int check(string& s) {
  // problem condition
}
void solve() {
  string a, b;
  cin >> a >> b;
  cout << Cnt(b) - Cnt(a) + check(a); // check if only string a can satisfy the condition
}


// calculate between l and r in one function
int dp[51][2][2][18][18][18];
string l, r;
int f(int i, int tightLower, int tightUpper, int c3, int c6, int c9) {
  if (c3 >= 17 || c6 >= 17 || c9 >= 17) return 0;
  if (i < 0) {
    return c3 && c3 == c6 && c6 == c9;
  }
  int& ret = dp[i][tightLower][tightUpper][c3][c6][c9];
  if (~ret && !tightLower && !tightUpper) return ret;
  int lo = tightLower ? l[i] - '0' : 0;
  int hi = tightUpper ? r[i] - '0' : 9;
  ret = 0;
  for (int d = lo; d <= hi; d++) {
    int newTightLower = tightLower && (d == lo);
    int newTightUpper = tightUpper && (d == hi);
    ret = (ret + f(i - 1, newTightLower, newTightUpper, c3 + (d == 3), c6 + (d == 6), c9 + (d == 9))) % mod;
  }
  return ret;
}
// optimized, without (tightLower, tightUpper) state
int f(int i, int tightLower, int tightUpper, int c3, int c6, int c9) {
  if (c3 >= 17 || c6 >= 17 || c9 >= 17) return 0;
  if (i < 0) {
    return c3 && c3 == c6 && c6 == c9;
  }
  int ret = dp[i][c3][c6][c9];
  if (~ret && !tightLower && !tightUpper) return ret;
  int lo = tightLower ? l[i] - '0' : 0;
  int hi = tightUpper ? r[i] - '0' : 9;
  ret = 0;
  for (int d = lo; d <= hi; d++) {
    int newTightLower = tightLower && (d == lo);
    int newTightUpper = tightUpper && (d == hi);
    ret = (ret + f(i - 1, newTightLower, newTightUpper, c3 + (d == 3), c6 + (d == 6), c9 + (d == 9))) % mod;
  }
  if (!tightLower && !tightUpper) dp[i][c3][c6][c9] = ret;
  return ret;
}
void solve() {
  cin >> l >> r;
  int n = r.size();
  while (l.size() < n) l = "0" + l;
  reverse(l.begin(), l.end());
  reverse(r.begin(), r.end());
  cout << f(n - 1, 1, 1, 0, 0, 0) << '\n';
}



int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  memset(dp, -1, sizeof dp);
  return 0;
}