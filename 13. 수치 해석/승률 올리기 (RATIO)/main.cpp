#include <cmath>
#include <iostream>
#define SUP 2000000001
#define WORKS (100*(M+mid) >= (Z+1)*(N+mid))
typedef long long ll;
using namespace std;
int bs(ll low, ll high, const ll M, const ll N) {
    if(low>high) {
        return SUP;
    }
    ll Z = M*100. / N;
    ll mid = (low + high) >> 1;
    if (WORKS) {
        return min<ll>(bs(low, mid-1, M, N), mid);
    } else {
        return bs(mid + 1, high, M, N);
    }
}
ll solve(const ll M, const ll N) {
    if (M >= N) return -1;
    ll sol = bs(1, SUP-1, M, N);
    if (sol == SUP) return -1;
    return sol;
}
int main() {
    int C;
    cin>>C;
    while(C--) {
        ll N,M;
        cin>>N>>M;
        cout << solve(M,N) << '\n';
    }
}
