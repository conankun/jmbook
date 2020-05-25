#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> get_pi(const string &p) {
    int n = p.size();
    vector<int> pi(n, 0);
    int j = 0;
    for (int i = 1; i < n; i ++) {
        while(j > 0 && p[i] != p[j]) j = pi[j-1];
        if(p[i] == p[j]) {
            pi[i] = ++j;
        }
    }
    return pi;
}
int kmp(const string &s, const string &p) {
    int n = s.size(), m = p.size();
    vector<int> pi = get_pi(p);
    int j = 0;
    int ret = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) j = pi[j-1];
        if (s[i] == p[j]) {
            j++;
            if (i == n - 1) ret = j;
            if (j == m) {
                j = pi[j-1];
            }
        }
    }
    return ret;
}
int solve(const string &s) {
    string srev = string(s);
    reverse(srev.begin(), srev.end());
    int match = kmp(s, srev);
    return 2*s.size() - match;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        string s;
        cin>>s;
        cout << solve(s) << '\n';
    }
}
//     zzzzabcdefdcba
//                  abcdefedcbazzzz