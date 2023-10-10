

struct item {
    int a, b;
};
bool cmp(item& a, item& b) {
    if(a.a != b.a) return a.a < b.a;
	return a.b > b.b;
}


bool custom(pair<int, int>& a, pair<int, int>& b) {
    if(a.first != b.first) return a.first > b.first;
	return a.second < b.second;
}

priority_queue<int, vector<int>, greater<int>>
set<int, greater<int>>
map<int, int, greater<int>>

// string to number
stoi(num);
// number to string
to_string(num);

// Binary to decimal
int n = stoi(binary, 0, 2);

// decimal to binary
string binary = bitset<64>(n).to_string();
binary.erase(0, binary.find_first_not_of('0'));

// upper to lower
transform(a.begin(), a.end(), a.begin(), ::tolower);

// set ith bit
n | (1 << i)
// unset ith bit
n & ~(1 << i) 
// toggle or inverse ith bit
n ^ (1 << i)

// sieve
for (int i = 2; i <= N; i++) {
    if (vis[i]) continue;
    primes.push_back(i);
    for (int j = i * 2; j <= N; j += i) vis[j] = 1;
}

---------------------------------------------------------
// ordered set
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

order_of_key();
find_by_order();