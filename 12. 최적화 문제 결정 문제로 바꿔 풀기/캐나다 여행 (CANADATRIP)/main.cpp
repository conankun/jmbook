#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
ll count(ll N, ll pos, ll L, ll M, ll G) {
    if (pos >= L) return M/G + 1;
    ll rpos = L - pos;
    if (rpos > M) return 0;
    return (M-rpos) / G + 1;
}
bool decide(ll N, ll K, ll pos, const vector<ll> &L, const vector<ll> &M, const vector<ll> &G) {
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        cnt += count(N, pos, L[i], M[i], G[i]);
    }
    return cnt >= K;
}
ll optimize(ll N, ll K, ll low, ll high, const vector<ll> &L, const vector<ll> &M, const vector<ll> &G) {
    if(low > high) return -1;
    ll mid = (low+high) >> 1;
    if(decide(N, K, mid, L, M, G)) {
        ll res = optimize(N, K, low, mid-1, L, M, G);
        return (res == -1) ? mid : res;
    }
    return optimize(N, K, mid + 1, high, L, M, G);
}
ll solve(ll N, ll K, const vector<ll> &L, const vector<ll> &M, const vector<ll> &G) {
    int mx = 0;
    for (int i = 1; i <= N; i++) mx = max<ll>(mx, L[i]);
    return optimize(N, K, 0, mx, L, M, G);
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int t;
    cin>>t;
    while(t--) {
        ll N, K;
        cin>>N>>K;
        vector<ll> L(N+1), M(N+1), G(N+1);
        for (int i = 1; i <= N; i++) cin>>L[i]>>M[i]>>G[i];
        cout << solve(N, K, L, M, G) << '\n';
    }
}


// 500 320

// 500, 450, 400, 350
// => 180/5 + 1

// 500, 300

// 500, 450, 400, 350, 300
// => 200/5 + 1 = 5