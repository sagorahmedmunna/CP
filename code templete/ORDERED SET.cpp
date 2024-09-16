#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T, class R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Sorting Descending (or Equal)
template <class T> using ordered_set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T, class R> using ordered_map = tree<T, R, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Fucntions
order_of_key(k): // Gives the count of elements smaller than k. — O(log n)
find_by_order(k): // Returns the iterator for the kth element (0 based index). — O(log n)
// To remove an element in a multiset, you must delete it using iterators:
ss.erase(ss.find_by_order(ss.order_of_key(x)));
// ordered_multiset erase
int rank = st.order_of_key(val); // Number of elements that are less than val in st
auto it = st.find_by_order(rank); // Iterator that points to the (rank+1)th element in st
st.erase(it);