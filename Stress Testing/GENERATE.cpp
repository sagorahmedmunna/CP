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

  // generate tree
  // int n = rnd(2, 20);
  // printf("%d\n", n);
  // vector<pair<int,int>> edges;
  // for(int i = 2; i <= n; ++i) {
  //   edges.emplace_back(rnd(1, i - 1), i);
  // }
  // vector<int> perm(n + 1); // re-naming vertices
  // for(int i = 1; i <= n; ++i) {
  //   perm[i] = i;
  // }
  // random_shuffle(perm.begin() + 1, perm.end());
  // random_shuffle(edges.begin(), edges.end()); // random order of edges
  // for(pair<int, int> edge : edges) {
  //   int a = edge.first, b = edge.second;
  //   if(rng() % 2) {
  //     swap(a, b); // random order of two vertices
  //   }
  //   printf("%d %d\n", perm[a], perm[b]);
  // }
  // make sure to check bambo tree and star tree
}