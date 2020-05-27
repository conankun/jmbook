#include <algorithm>
#include <iostream>
#include <vector>
#define MAXN 1000
using namespace std;
int N, K;
double R[MAXN + 1], C[MAXN + 1];
bool decide(double opt) {
    vector<double> val(N);
    for (int i = 0; i < N; i++) val[i] = opt * C[i] - R[i];
    sort(val.begin(), val.end(), [](double a, double b) {
       return a > b;
    });
    double sum = 0;
    for (int i = 0; i < K; i++) sum += val[i];
    return sum >= 0;
}
double solve() {
    double low = 0, high = 1;
    double ans = 1;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (low + high) / 2;
        if (decide(mid)) {
            ans = min(ans, mid);
            high = mid;
        } else {
            low = mid;
        }
    }
    return ans;
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&N,&K);
        for (int i = 0; i < N; i++) scanf("%lf%lf",&R[i],&C[i]);
        printf("%.12lf\n", solve());
    }

}
