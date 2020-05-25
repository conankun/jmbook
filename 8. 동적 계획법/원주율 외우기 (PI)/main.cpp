#include <iostream>
#include <limits>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(0)
using namespace std;
const int SUP = numeric_limits<int>::max();
bool all_same(const string &str, int begin, int end) {
    bool ret = true;
    for (int i = begin + 1; i <= end; i++) {
        if (str[i] != str[begin]) {
            ret = false;
            break;
        }
    }
    return ret;
}
bool monotonic(const string &str, int begin, int end, int next(int a)) {
    bool ret = true;
    for (int i = begin + 1; i <= end; i++) {
        if (next(str[i-1]) != str[i]) {
            ret = false;
            break;
        }
    }
    return ret;
}
bool alternate(const string &str, int begin, int end) {
    bool ret = true;
    for (int i = begin + 2; i <= end; i++) {
        if (str[i] != str[i-2]) {
            ret = false;
            break;
        }
    }
    return ret;
}
bool arithmetic(const string &str, int begin, int end) {
    bool ret = true;
    for (int i = begin + 2; i <= end; i++) {
        if(str[i] != str[i-1]*2 - str[i-2]) {
            ret = false;
            break;
        }
    }
    return ret;
}
int difficulty(const string &str, int begin, int end) {
    if (all_same(str, begin, end)) {
        return 1;
    }
    auto inc = [](int a) {return a + 1;};
    auto dec = [](int a) {return a - 1;};
    if (monotonic(str, begin, end, inc ) || monotonic(str, begin, end, dec)) {
        return 2;
    }
    if (alternate(str, begin, end)) {
        return 4;
    }
    if (arithmetic(str, begin, end)) {
        return 5;
    }
    return 10;
}
int solve(const string &str) {
    int n = str.size();
    vector<int> dp(n, SUP);
    for (int i = 2; i < 5; i++) {
        dp[i] = difficulty(str, 0, i);
    }
    for (int i = 5; i < n; i++) {
        for (int j = i-2; j >= i-4; j--) {
            if (dp[j-1] != SUP) {
                dp[i] = min(dp[i], dp[j-1] + difficulty(str, j, i));
            }
        }
    }
    return dp[n-1];
}
int main() {
    FAST_IO;
    int C;
    cin>>C;
    while(C--) {
        string str;
        cin>>str;
        cout << solve(str) << '\n';
    }
}
