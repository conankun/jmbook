#include <algorithm>
#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>
#define LIMIT 0.0001
#define IDENTITY 2147483647
using namespace std;
inline double sq(double x) {
    return x*x;
}
inline double distance(pair<double,double> a, pair<double,double> b) {
    return sqrt(sq(a.first - b.first) + sq(a.second - b.second));
}
bool decide(double radius, const vector<vector<double>> &dist) {
    int n = dist.size() - 1;
    vector<bool> discovered(n + 1, 0);
    queue<int> qu;
    qu.push(1);
    int covered = 0;
    while(!qu.empty()) {
        int i = qu.front(); qu.pop();
        covered++, discovered[i]=true;
        for (int j = 1; j <= n; j++) {
            if(dist[i][j] <= radius && !discovered[j]) {
                discovered[j] = true;
                qu.push(j);
            }
        }
    }
    return (covered == n);
}
double optimize(const vector<vector<double>> &dist) {
    double low = 0, high = 2000;
    int iter = 100;
    double ans = IDENTITY;
    while(iter--) {
        double mid = (low + high) / 2;
        if (decide(mid, dist)) {
            ans = min(ans, mid);
            high = mid;
        } else {
            low = mid;
        }
    }
    return ans;
}
double solve(const vector<pair<double,double>> &location) {
    int n = location.size() - 1;
    vector<vector<double>> dist(n + 1, vector<double>(n+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n;j++) {
            if (i == j) continue;
            dist[i][j] = distance(location[i], location[j]);
        }
    }
    return optimize(dist);
}
int main() {
    int C;
    scanf("%d",&C);
    while(C--) {
        int n;
        scanf("%d",&n);
        vector<pair<double,double>> loc(n+1);
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf", &loc[i].first, &loc[i].second);
        }
        printf("%.2lf\n", solve(loc));
    }
}
