#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define DP(i,j) dp[i+1][j+1]
using namespace std;
inline bool match(char s, char p) {
    return s == '?' || s == '*' || s == p;
}
bool lcs(const string &s, const string &p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = 1;
    dp[1][0] = (s[0] == '*');
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (match(s[i], p[j])) {
                DP(i,j) = max(DP(i,j), DP(i-1,j-1));
            }
            if (s[i] == '*') {
                DP(i,j) = max(DP(i,j), max(DP(i-1,j), DP(i,j-1)));
            }
        }
    }
    return dp[n][m];
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        string s;
        cin>>s;
        int n;
        cin>>n;
        vector<string> ans;
        while(n--) {
            string p;
            cin>>p;
            if (lcs(s,p)) {
                ans.push_back(p);
            }
        }
        sort(ans.begin(), ans.end());
        for (auto x : ans) cout << x << '\n';
    }
}
