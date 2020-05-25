#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define FRONT(x) (x.front() - 97)
#define BACK(x) (x.back() - 97)
using namespace std;
struct Solution {
    vector<vector<int>> adj;
    vector<string> inv[26][26];
    vector<vector<int>> inv_ind;
    vector<int> in, out;
    vector<int> ans;
    void make_graph(int N, const vector<string> &arr) {
        for (int i = 0; i < N; i++) {
            adj[FRONT(arr[i])][BACK(arr[i])]++;
            inv[FRONT(arr[i])][BACK(arr[i])].push_back(arr[i]);
            in[BACK(arr[i])]++;
            out[FRONT(arr[i])]++;
        }
    }

    bool check_existence() {
        int cnt1 = 0; // in = out
        int cnt2 = 0; // in = out + 1
        int cnt3 = 0; // in + 1 = out
        for (int i = 0; i < 26; i++) {
            if (in[i] == out[i]) cnt1++;
            else if(in[i] == out[i] + 1) cnt2++;
            else if(in[i] + 1 == out[i]) cnt3++;
            else return false;
        }
        return (cnt2 == 0 && cnt3 == 0) || (cnt2 == 1 && cnt3 == 1);
    }

    int find_start_point() {
        int candidate = 0;
        for (int i = 0; i < 26; i++) {
            if (in[i] + 1 == out[i]) return i;
            if (in[i] == out[i] && out[i] > 0) candidate = i;
        }
        return candidate;
    }

    void euler_path(int here) {
        for (int i = 0; i < 26; i++) {
            while(adj[here][i]) {
                adj[here][i]--;
                euler_path(i);
            }
        }
        ans.push_back(here);
    }

    string solve(int N, const vector<string> &arr) {
        make_graph(N, arr);
        if (!check_existence()) return "IMPOSSIBLE";
        euler_path(find_start_point());
        reverse(ans.begin(), ans.end());
        string ret = "";
        for (int i = 0; i < ans.size() - 1; i++) {
            int here = ans[i];
            int next = ans[i+1];
            ret += inv[here][next][inv_ind[here][next]++] + ' ';
        }
        return ret;
    }
    Solution()
        : adj(26, vector<int>(26,0)), out(26), in(26), inv_ind(26, vector<int>(26,0)) {}
};
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N;
        cin>>N;
        vector<string> arr(N);
        for (int i = 0; i < N; i++) cin>>arr[i];
        Solution sol;
        cout << sol.solve(N, arr) << '\n';
    }
}
