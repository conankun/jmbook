#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> get_pi(const string &p) {
    int n = p.size();
    vector<int> pi(n, 0);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && p[i] != p[j]) j = pi[j-1];
        if (p[i] == p[j]) {
            pi[i] = ++j;
        }
    }
    return pi;
}
int kmp(const string &s, const string &p) {
    int n = s.size(), m = p.size();
    vector<int> pi = get_pi(p);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while(j > 0 && s[i] != p[j]) j = pi[j-1];
        if (s[i] == p[j]) {
            ++j;
            if (j == m) {
                return i - m + 1;
            }
        }
    }
}
int solve(const string &s1, const string &s2) {
    return min(kmp(s1+s1, s2), kmp(s2+s2, s1));
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        string here;
        cin>>n>>here;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            string next;
            cin>>next;
            sum += (i % 2) ? kmp(here+here, next) : kmp(next+next, here) ;
            here = next;
        }
        cout << sum << '\n';
    }
}