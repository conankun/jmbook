#include <iostream>
#include <string>
#include <vector>
using namespace std;
string solve(const string &str, int idx) {
    if (str[idx] == 'b' || str[idx] == 'w') {
        return str.substr(idx, 1);
    }
    vector<string> arr(4, "");
    int p = idx + 1;
    for (int i = 0; i < 4; i++) {
        arr[i] = solve(str, p);
        p += arr[i].size();
    }
    return 'x' + arr[2] + arr[3] + arr[0] + arr[1];
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        string s;
        cin>>s;
        cout << solve(s, 0) << '\n';
    }
}
