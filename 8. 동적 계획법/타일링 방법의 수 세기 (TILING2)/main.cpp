#include <iostream>
#include <vector>
#define MOD 1000000007
using namespace std;
int main() {
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i-1] + (i > 1 ? dp[i-2] : 0);
            dp[i] %= MOD;
        }
        cout << dp[n] << '\n';
    }
}
