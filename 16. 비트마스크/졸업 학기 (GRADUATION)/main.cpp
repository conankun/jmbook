#include <bitset>
#include <iostream>
#include <vector>
#define MAXN 12
#define BS bitset<MAXN>
#define MAXH 0xfff
#define SUP 999999
#define IND(x) ((x) & 1)
typedef unsigned int ui;
using namespace std;
void input(const int N, const int M, vector<BS> &prereq, vector<BS> &semester) {
    for (int i = 0; i < N; i++) {
        int R;
        cin>>R;
        for (int j = 0; j < R; j++) {
            int r;
            cin>>r;
            prereq[i][r] = 1;
        }
    }
    for (int i = 0; i < M; i++) {
       int C;
       cin>>C;
       for (int j = 0; j < C; j++) {
           int c;
           cin>>c;
           semester[i][c] = 1;
       }
    }
}
bool is_valid(const BS &set, const BS &state, const vector<BS> &prereq, int L) {
    // check prereq.
    for (int i = 0; i < set.size(); i++) {
        if (set[i]) {
            for (int j = 0; j < prereq[i].size(); j++) {
                if (prereq[i][j] && !state[j]) return false;
            }
        }
    }
    return set.count() <= L;
}
int solve(const int N, const int K, const int M, const int L) {
    vector<BS> prereq(N, BS(0));
    vector<BS> semester(M, BS(0));
    input(N, M, prereq, semester);
    // minimum number of semesters to reach state.
    vector<vector<int>> dp(2, vector<int>(MAXH + 1, SUP));
    for (int i = 0; i < 2; i++) dp[i][0] = 0;
    for (int i = 0; i < M; i++) {
        for (ui s = 0; s <= MAXH && i > 0; s++) dp[IND(i)][s] = dp[IND(i-1)][s];
        for (ui s = 0; s <= MAXH; s++) {
            if (i > 0 && dp[IND(i-1)][s] == SUP) continue;
            BS state(s);
            if (state.count() >= K) continue;
            ui init = semester[i].to_ulong();
            for (ui ns = init; ns; ns = ((ns-1) & init)) {
                if (is_valid(BS(ns), state, prereq, L)) {
                    if (i) dp[IND(i)][s | ns] = min(dp[IND(i)][s | ns], dp[IND(i-1)][s] + 1);
                    else dp[IND(i)][s|ns] = 1;
                }
            }
            if (!i) break;
        }
    }
    // find the answer
    int ans = SUP;
    for (ui s = 0; s <= MAXH; s++) {
        BS set(s);
        if (set.count() >= K) {
            ans = min(ans, dp[IND(M-1)][s]);
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N, K, M, L;
        cin>>N>>K>>M>>L;
        int ans = solve(N, K, M, L);
        if (ans != SUP) cout << ans << '\n';
        else cout << "IMPOSSIBLE" << '\n';
    }
}
