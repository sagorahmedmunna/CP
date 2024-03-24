pair<vector<int>, vector<int>> closest_min_element(vector<int> &a) {
  int n = a.size();
  vector<int> l(n), r(n);
  stack<int> st;
  st.push(-1);
  for (int i = 0; i < n; i++) {
    while (st.top() != -1 && a[st.top()] > a[i]) st.pop();
    l[i] = st.top() + 1;
    st.push(i);
  }
  while (!st.empty()) st.pop();
  st.push(n);
  for (int i = n - 1; i >= 0; i--) {
    while (st.top() != n && a[st.top()] >= a[i]) st.pop();
    r[i] = st.top() - 1;
    st.push(i);
  }
  return {l, r};
}

pair<vector<int>, vector<int>> closest_max_element(vector<int> &a) {
  int n = a.size();
  vector<int> l(n), r(n);
  stack<int> st;
  st.push(-1);
  for (int i = 0; i < n; i++) {
    while (st.top() != -1 && a[st.top()] < a[i]) st.pop();
    l[i] = st.top() + 1;
    st.push(i);
  }
  while (!st.empty()) st.pop();
  st.push(n);
  for (int i = n - 1; i >= 0; i--) {
    while (st.top() != n && a[st.top()] <= a[i]) st.pop();
    r[i] = st.top() - 1;
    st.push(i);
  }
  return {l, r};
}