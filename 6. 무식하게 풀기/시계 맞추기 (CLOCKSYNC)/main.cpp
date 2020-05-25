#include <algorithm>
#include <iostream>
#include <vector>
#define N 16
#define NSWITCH 10
#define BETTER (ret == -1 || r < ret)
#define MOD 4
typedef unsigned int ui;
using namespace std;
vector<vector<int>> switches =
        {
            {0, 1, 2},
            {3, 7, 9, 11},
            {4, 10, 14, 15},
            {0, 4, 5, 6, 7},
            {6, 7, 8, 10, 12},
            {0, 2, 14, 15},
            {3, 14, 15},
            {4, 5, 7, 14, 15},
            {1, 2, 3, 4, 5},
            {3, 4, 5, 9, 13}
        };
inline ui compress(ui val) {
    return (val / 3) % 4;
}
vector<int> input() {
    vector<int> ret(N);
    for (int i = 0; i < N; i++) {
        cin>>ret[i];
        ret[i] = compress(ret[i]);
    }
    return ret;
}
void set(vector<int> &clock_state, int sw_idx, int val) {
    for (auto x : switches[sw_idx]) {
        clock_state[x] += val + MOD;
        clock_state[x] %= MOD;
    }
}
int find(int level, int current_switch, vector<int> &clock_state, vector<int> &switch_state) {
    bool is_goal = true;
    for (int i = 0; i < N; i++) is_goal &= !clock_state[i];
    if (is_goal) return level;
    int ret = -1;
    for (int i = current_switch; i < NSWITCH; i++) {
        if (switch_state[i] == 3) continue;
        set(clock_state, i, 1);
        switch_state[i]++;
        int r = find(level + 1, i, clock_state, switch_state);
        if (r > 0 && BETTER) {
            ret = r;
        }
        switch_state[i]--;
        set(clock_state, i, -1);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        vector<int> clock_state = input();
        vector<int> switch_state(NSWITCH, 0);
        cout << find(0, 0, clock_state, switch_state) << '\n';
    }
}
