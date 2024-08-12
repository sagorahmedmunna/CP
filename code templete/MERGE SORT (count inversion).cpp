#include <bits/stdc++.h>
using namespace std;

long long merge(vector<int>& a, int l, int mid, int r) {
  long long inv = 0;
  int n1 = mid - l + 1;
  int n2 = r - mid;
  vector<int> a1(n1), a2(n2);
  for (int i = 0; i < n1; i++) a1[i] = a[l + i];
  for (int i = 0; i < n2; i++) a2[i] = a[mid + 1 + i];
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (a1[i] <= a2[j]) {
      a[k] = a1[i++];
    } else {
      a[k] = a2[j++];
      inv += n1 - i;
    }
    k++;
  }
  while (i < n1) a[k++] = a1[i++];
  while (j < n2) a[k++] = a2[j++];
  return inv;
}

long long Merge_sort(vector<int>& a, int l, int r) {
  long long inv = 0;
  if (l >= r) return 0;
  int mid = (l + r) / 2;
  inv += Merge_sort(a, l, mid);
  inv += Merge_sort(a, mid + 1, r);
  inv += merge(a, l, mid, r);
  return inv;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  
  int n; cin >> n;
  vector<int> a(n);
  for (auto& ai : a) cin >> ai;
  long long inv = Merge_sort(a, 0, n - 1);
  // print inversions count
  cout << inv << '\n';
  // print sorted array
  for (auto& ai : a) cout << ai << ' ';
  cout << '\n';
  return 0;
}