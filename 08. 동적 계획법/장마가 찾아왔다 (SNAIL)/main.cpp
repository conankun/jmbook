#include <iostream>
#include <vector>
using namespace std;
struct Snail {
    vector<vector<double>> cache;
    int N, M;
    double solve(int height, int day) {
        if (day <= M && height >= N) {
            return cache[day][height] = 1.0;
        } else if (day == M && height < N) {
            return cache[day][height] = 0.0;
        }
        if (cache[day][height] >= 0) return cache[day][height];
        cache[day][height] =
                0.75 * solve(height + 2, day + 1)
                + 0.25 * solve(height + 1, day + 1);
        return cache[day][height];
    }
    Snail(int N, int M) : N(N), M(M), cache(M + 1, vector<double>(2*N+1, -1)) {}
};
int main() {
    int C;
    scanf("%d",&C);
    while(C--) {
        int N,M;
        scanf("%d%d",&N,&M);
        Snail s(N,M);
        printf("%.12lf\n", s.solve(0, 0));
    }
}
