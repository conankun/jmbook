#include <iostream>
#include <vector>
#define UPDATE_MIN_AVG if (min_avg == -1 || min_avg > sum/(double)i) min_avg = sum/(double)i
using namespace std;
double solve(const int N, const int L, const vector<int> &arr) {
    double min_avg = -1;
    for (int i = L; i <= N; i++) {
        int sum = 0;
        for (int j = 0; j < i; j++) sum += arr[j];
        UPDATE_MIN_AVG;
        for (int j = i; j < N; j++) {
            sum += arr[j]; sum-=arr[j-i];
            UPDATE_MIN_AVG;
        }
    }
    return min_avg;
}
int main() {
    int C;
    scanf("%d",&C);
    while(C--) {
        int N,L;
        scanf("%d%d",&N,&L);
        vector<int> arr(N);
        for (int i = 0; i < N; i++) scanf("%d",&arr[i]);
        printf("%.12lf\n", solve(N,L,arr));
    }
}