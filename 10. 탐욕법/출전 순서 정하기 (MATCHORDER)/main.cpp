#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
int solve(vector<int> &R, vector<int> &K) {
    sort(R.begin(), R.end(), greater<int>());
    sort(K.begin(), K.end(), greater<int>());
    int cnt = 0;
    int front = 0, back = K.size() - 1;
    for (int i = 0; i < K.size(); i++) {
        if (front <= back && R[i] <= K[front]) {
            cnt++;
            front++;
        } else {
            back--;
        }
    }
    return cnt;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<int> R(n), K(n);
        for (int i = 0; i < n; i++) cin>>R[i];
        for (int i = 0; i < n; i++) cin>>K[i];
        cout << solve(R, K) << '\n';
    }
}