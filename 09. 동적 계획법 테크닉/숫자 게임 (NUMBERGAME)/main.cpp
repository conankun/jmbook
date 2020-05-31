#include <iostream>
#define MAXN 50
#define NIL 9999999
using namespace std;
int cache[2][MAXN][MAXN], arr[MAXN], N;
void init() {
    for (int k = 0; k < 2; k++) for (int i = 0; i < MAXN; i++) for(int j = 0; j < MAXN; j++) cache[k][i][j] = NIL;
}
int game(int left, int right, bool hyunwoo) {
    if (left > right || left < 0 || right >= N) {
        return 0;
    }
    int &ret = cache[hyunwoo][left][right];
    if (ret != NIL) return ret;
    auto cmp = hyunwoo ? [](int a, int b) { return max(a,b); } : [](int a, int b) { return min(a,b); };
    int elem = hyunwoo ? arr[left] : -arr[left];

    // 왼쪽
    ret = game(left + 1, right, !hyunwoo) + elem;
    if (right - left > 0) {
        ret = cmp(ret, game(left + 2, right, !hyunwoo));
        ret = cmp(ret, game(left, right - 2, !hyunwoo));
    }

    // 오른쪽
    elem = hyunwoo ? arr[right] : -arr[right];
    ret = cmp(ret, game(left, right - 1, !hyunwoo) + elem);
    if (right - left > 0) {
        ret = cmp(ret, game(left + 2, right, !hyunwoo));
        ret = cmp(ret, game(left, right - 2, !hyunwoo));
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        init();
        cin>>N;
        for (int i = 0; i < N; i++) cin>>arr[i];
        cout << game(0, N - 1, 1) << '\n';
    }
}
