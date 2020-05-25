#include <iostream>
#include <stack>
#include <string>
#define IS_OPEN_BRACKET(c) (c == '(' || c == '[' || c == '{')
#define CORRESPONDING_BRACKET(c) (c == ')' ? '(' : (c == '}' ? '{' : '['))
using namespace std;
bool solve(const string &s) {
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if(IS_OPEN_BRACKET(c)) {
            st.push(c);
        } else {
            if (!st.empty() && st.top() == CORRESPONDING_BRACKET(c)) {
                st.pop();
            } else return false;
        }
    }
    return st.empty();
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        string s;
        cin>>s;
        cout << (solve(s) ? "YES" : "NO") << '\n';
    }
}