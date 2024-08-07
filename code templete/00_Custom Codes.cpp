freopen("input.in", "r", stdin);
freopen("output.in", "w", stdout);
ios_base::sync_with_stdio(0), cin.tie(0);

// pragma
#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC optimize ("-ffloat-store")
#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,abm,mmx")

// ignore white space
cin.ignore(); or cin >> ws;

// STL merge function: merge two vectors or sets
vector<int> a = {1, 2, 7}, b = {4, 2, 3};
sort(a.begin(), a.end());
sort(b.begin(), b.end());
vector<int> c(a.size() + b.size());
merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());

set<int> a = {3, 2, 1}, b = {4, 5, 1};
set<int> c;
merge(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
for (auto& i : c) cout << i << ' ';

// tuple
tuple<int, int, int> tup = {1, 2, 3};
int first = get<0>(tup);

// custom compare function
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

// custom compare in set
struct cmp{
	bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
		if (a.first != b.first) return a.first > b.first;
		return a.second < b.second;
	}
};
set<pair<int, int>, cmp> a;

// greater functions
priority_queue<int, vector<int>, greater<int>>
set<int, greater<int>>
map<int, int, greater<int>>

// fill with elements
fill(v.begin(), v.end(), -1);

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

// count digit
int d = log10(num) + 1;

// set ith bit
n | (1 << i)
// unset ith bit
n & ~(1 << i) 
// toggle or inverse ith bit
n ^ (1 << i)

// a point inside cricle
// x1, y1 = point of circle
// r = radius of circle
// x2, y2 = target point
bool isInside(int x1, int y1, int x2, int y2, int r) {
	return ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) <= r * r;
}

---------------------------------------------------------
// gp hash table
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> mp;

---------------------------------------------------------
// unordered map custom hash

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};
unordered_map<int, int, custom_hash> ump;
---------------------------------------------------------
// ordered set

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Sorting Descending (or Equal)
template<class T> using ordered_set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Fucntions
order_of_key(k): // Gives the count of elements smaller than k. — O(log n)
find_by_order(k): // Returns the iterator for the kth element (0 based index). — O(log n)

// To remove an element in a multiset, you must delete it using iterators:
ss.erase(ss.find_by_order(ss.order_of_key(x)));

// ordered_multiset erase
int rank = st.order_of_key(val); //Number of elements that are less than val in st
auto it = st.find_by_order(rank); // //Iterator that points to the (rank+1)th element in st
st.erase(it);