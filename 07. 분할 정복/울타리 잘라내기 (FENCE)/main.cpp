#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int pop_stack(stack<pair<int,int>> &st, const vector<int> &arr, int here) {
    int ans = 0;
    while (!st.empty()
        && (arr.size() == here || st.top().first > arr[here])) {
        auto top = st.top();
        st.pop();
        int left = st.empty() ? 1 : (st.top().second + 1);
        int right = here - 1;
        ans = max(ans, (right-left + 1) * top.first);
    }
    return ans;
}
int solve(const vector<int> &arr) {
    stack<pair<int,int>> st;
    st.push({arr[1], 1});
    int ans = arr[1];
    for (int i = 2; i < arr.size(); i++) {
        ans = max(ans, pop_stack(st, arr, i));
        st.push({arr[i], i});
    }
    ans = max(ans, pop_stack(st, arr, arr.size()));
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N;
        cin>>N;
        vector<int> arr(N+1);
        for (int i = 1; i <= N; i++) cin>>arr[i];
        cout << solve(arr) << '\n';
    }
}
