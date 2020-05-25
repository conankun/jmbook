#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> get_pi(const string &p) {
    int n = p.size();
    vector<int> pi(n, 0);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while(j > 0 && p[i] != p[j]) j = pi[j-1];
        if (p[i] == p[j]) {
            pi[i] = j++;
        } else if (j > 0) {
            j = pi[j-1];
        }
    }
    return pi;
}
vector<int> solve(const string &p) {
    vector<int> pi = get_pi(p);
    vector<int> ans;
    ans.push_back(p.size());
    int j = pi[pi.size()-1];
    while (j > 0) {
        ans.push_back(j+1);
        j = pi[j];
    }
    if (p[0] == p[p.size()-1]) ans.push_back(1);
    sort(ans.begin(), ans.end());
    return ans;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    string s1,s2;
    cin>>s1>>s2;
    vector<int> ans = solve(s1+s2);

    for (auto x : ans) {
        cout << x << ' ';
    }
}

// ababcababababcabab