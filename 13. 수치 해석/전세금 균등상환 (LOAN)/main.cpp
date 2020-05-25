#include <iostream>
using namespace std;
bool decide(const double C, const double N, const double M, const double P) {
    double balance = N;
    double rate = 1.0 + P/(12.0*100.0);
    for (int i = 0; i < M; i++) {
        balance *= rate;
        balance -= C;
    }
    return balance <= 0;
}
double solve(const double N, const double M, const double P) {
    double low = 0, high = 2*N;
    double ret = high;
    for (int iter = 0; iter < 300; iter++) {
        double mid = (low + high) / 2.;
        if (decide(mid, N, M, P)) {
            ret = min(ret, mid);
            high = mid;
        } else {
            low = mid;
        }
    }
    return ret;
}
int main() {
    cin.tie(0);
    int T;
    cin>>T;
    while(T--) {
        double N, M, P;
        cin>>N>>M>>P;
        printf("%.10lf\n", solve(N,M,P));
    }
}
