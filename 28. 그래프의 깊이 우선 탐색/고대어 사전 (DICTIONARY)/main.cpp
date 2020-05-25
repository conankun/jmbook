#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define TO_INT(x) (x-97)
#define TO_CHAR(x) (x+97)
using namespace std;
struct Solution {
    vector<vector<bool>> adj;
    vector<int> post;
    vector<bool> vis;
    int post_num;
    string prev_str;
    bool invalid;
    // return false if there's a contradiction.
    bool make_graph(const string &str1, const string &str2) {
        int n = str1.size(), m = str2.size();
        int size = min(n,m);
        for (int i = 0; i < size; i++) {
            if (str1[i] != str2[i]) {
                adj[TO_INT(str1[i])][TO_INT(str2[i])] = 1;
                return true;
            }
        }
        if (n > m) {
            return false;
        }
        return true;
    }
    void add_string(const string &str) {
        if (!prev_str.empty()) {
            bool res = make_graph(prev_str, str);

            if (!res) invalid = true;
        }
        prev_str = str;
    }
    void dfs(int here) {
        vis[here] = true;
        for (int i = 0; i < 26; i++) {
            if (adj[here][i] && !vis[i]) {
                dfs(i);
            }
        }
        post[here]=++post_num;
    }
    void toposort() {
        for (int i = 0; i < 26; i++) {
            if (!post[i]) dfs(i);
        }
        // Validate
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (i != j && adj[i][j] && post[i] < post[j]) {
                    // backward edge (=cycle) exists. invalid.
                    invalid = true;
                    return;
                }
            }
        }
    }
    string answer() {
        vector<pair<int,int>> po;
        for (int i = 0; i < 26; i++) {
            po.push_back(make_pair(post[i], i));
        }
        sort(po.begin(), po.end(), greater<pair<int,int>>());
        string ans = "";
        for (auto x : po) {
            ans += TO_CHAR(x.second);
        }
        return ans;
    }
    string solve() {
        toposort();
        return invalid ? "INVALID HYPOTHESIS" : answer();
    }
    Solution()
        : adj(26, vector<bool>(26)),
        prev_str(""),
        invalid(false),
        post(26, 0),
        post_num(0),
        vis(26, 0) {}
};
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N;
        cin>>N;
        string str;
        Solution sol;
        for (int i = 0; i < N; i++) {
            cin>>str;
            sol.add_string(str);
        }
        cout << sol.solve() << '\n';
    }
}