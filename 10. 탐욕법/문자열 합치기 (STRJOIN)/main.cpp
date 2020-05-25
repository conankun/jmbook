#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int solve(const vector<int> &arr) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto n : arr) pq.push(n);
    int sum = 0;
    while(!pq.empty()) {
        int a = pq.top(); pq.pop();
        if (pq.empty()) break;
        int b = pq.top(); pq.pop();
        sum += a + b;
        pq.push(a+b);
    }
    return sum;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin>>arr[i];
        cout << solve(arr) << '\n';
    }
}