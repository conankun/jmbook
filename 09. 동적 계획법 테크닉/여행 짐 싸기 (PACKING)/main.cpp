#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define NIL -1
using namespace std;
struct Item {
    string name;
    int volume, value;
};
struct Packing {
    // 물건의 목록.
    vector<Item> items;
    // dp[N] = 부피가 N일 때 최대 절박도.
    vector<int> dp;
    // ref[k][N] = 부피가 N이고 물건을 0, ..., k중 일부를 넣었을 때 최대 절박도를 만드는 마지막 물건.
    // 첫번째 예제의 경우 k = 3 (즉 grinder까지), N = 10 일 때 {laptop, camera, grinder}를 넣으면 최대 절박도를 얻을 수 있는데
    // 이 중 마지막 물건은 grinder (index: 3) 이다. 즉, ref[k=3][N=10] = 3.
    vector<vector<int>> ref;
    int N, W;
    void input() {
        for (int i = 0; i < N; i++) {
            cin>>items[i].name>>items[i].volume>>items[i].value;
        }
    }
    // 최대 절박도를 구성하는 물건의 집합을 찾는다.
    vector<int> tracing(int argvol) {
        int volume = argvol;
        vector<int> ans;
        int ind = N - 1;
        while (volume > 0) {
            int here = ref[ind][volume];
            ans.emplace_back(here); volume -= items[here].volume; ind = here - 1;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    // 정답을 출력한다.
    void print(int argvol) {
        vector<int> trace = tracing(argvol);
        cout << dp[argvol] << ' ' << trace.size() << '\n';
        for (auto ind : trace) {
            cout << items[ind].name << '\n';
        }
    }
    int run_dp() {
        dp[0] = 0;
        int mx = 0, argvol = 0;
        for (int i = 0; i < N; i++) {
            int value = items[i].value, volume = items[i].volume;
            for (int here = W; here >= 0; here--) {
                // 만들 수 없는 상태이므로 넘긴다.
                if (dp[here] == NIL) continue;
                if (here + volume <= W && dp[here+volume] < dp[here] + value) {
                    dp[here + volume] = dp[here] + value, ref[i][here + volume] = i;
                    // 절박도가 최대가 되는 경우 갱신한다. argvol 은 최대 절박도를 만드는 부피의 합이다.
                    if (mx < dp[here + volume]) {
                        mx = dp[here + volume], argvol = here + volume;
                    }
                }
            }
            // i + 1 번째 물건을 사용 안하는 경우 ref[i+1][0...N]은 ref[i][0...N] 그대로다.
            if (i != N - 1) for (int here = 0; here <= W; here++) ref[i + 1][here] = ref[i][here];
        }
        return argvol;
    }
    void solve() {
        input();
        print(run_dp());
    }
    Packing(int N, int W) : N(N), W(W), items(N), dp(W + 1, NIL), ref(N + 1, vector<int>(W + 1, NIL)) {}
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while (C--) {
        int N, W;
        cin>>N>>W;
        Packing pc(N, W);
        pc.solve();
    }
}
