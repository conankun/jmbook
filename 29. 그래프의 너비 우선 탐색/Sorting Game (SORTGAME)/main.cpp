#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
vector<int> swap(const vector<int> &arr, int i, int j) {
    vector<int> new_arr(arr);
    int left = i, right = j;
    while (left < right) {
        swap(new_arr[left], new_arr[right]);
        left++, right--;
    }
    return new_arr;
}
map<vector<int>, int> solve() {
    const int n = 8;
    map<vector<int>, int> ans;
    vector<int> init = {1,2,3,4,5,6,7,8};
    ans[init] = 0;
    queue<vector<int>> qu;
    qu.push(init);
    int count = 0;
    while (!qu.empty()) {
        vector<int> top = qu.front(); qu.pop();
        int dist = ans[top];
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (i == 4 && j == n - 1) {
                    i=i;
                }
                vector<int> next = swap(top, i, j);
                if (!ans.count(next)) {
                    ans[next] = dist + 1;
                    qu.push(next);
                }
            }
        }
    }
    return ans;
}
vector<int> compression(const vector<int> &arr) {
    vector<pair<int,int>> ref(arr.size());
    for (int i = 0; i < arr.size(); i++) ref[i].first = arr[i], ref[i].second = i;
    sort(ref.begin(), ref.end());
    int key = 1;
    vector<int> keys(arr.size());
    for (int i = 0; i < ref.size(); i++) keys[ref[i].second] = (i > 0 && ref[i].first != ref[i-1].first ? ++key : key);
    return keys;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    auto ans = solve();
    while(C--) {
        int n;
        cin>>n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin>>arr[i];
        arr = compression(arr), arr.resize(8);
        for (int i = n; i < 8; i++) arr[i] = i + 1;
        cout << ans[arr] << '\n';
    }
}