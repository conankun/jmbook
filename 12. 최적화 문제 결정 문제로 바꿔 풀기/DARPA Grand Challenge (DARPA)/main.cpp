#include <iostream>
#include <vector>
#define LIMIT 0.001
using namespace std;
bool greedy(double size, const vector<double> &arr, int n) {
    int m = arr.size();
    double prev = -1;
    int cnt = 0;
    for (double loc : arr) {
        if (prev == -1 || loc-prev >= size) {
            cnt++;
            prev = loc;
        }
    }
    return cnt >= n;
}
double ps(double low, double high, const vector<double> &arr, int n) {
    if (low>high || high-low < LIMIT) {
        return -1;
    }
    double mid = (low+high)/2;
    bool feasible = greedy(mid, arr, n);
    if (feasible) {
        return max(mid, ps(mid + LIMIT, high, arr, n));
    } else {
        return ps(low, mid-LIMIT, arr, n);
    }
}
double solve(const vector<double> &arr, int n) {
    return ps(0, arr.back(), arr, n);
}
int main() {
    int c;
    scanf("%d", &c);
    while(c--) {
        int n, m;
        scanf("%d%d",&n,&m);
        vector<double> arr(m);
        for (int i = 0; i < m; i++) scanf("%lf",&arr[i]);
        printf("%.2lf\n", solve(arr,n));
    }
}
