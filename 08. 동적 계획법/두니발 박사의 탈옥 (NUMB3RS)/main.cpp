#include <cstring>
#include <iostream>
#define MAXN 50
#define MAXD 100
using namespace std;
int adj[MAXN][MAXN], sz[MAXN], n, d, p, t;
double cache[MAXD + 1][MAXN];
void get_sz() {
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (auto x : adj[i]) cnt += x;
        sz[i] = cnt;
    }
}
void reset() {
    memset(adj, 0, sizeof(int) * MAXN * MAXN);
    memset(sz, 0, sizeof(int) * MAXN);
    memset(cache, 0, sizeof(double) * (MAXD + 1) * MAXN);
}
void get_map() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d",&adj[i][j]);
        }
    }
}
double find(int k, int here) {
    if (k == 0) {
        return (here == p);
    }
    double &ret = cache[k][here];
    if (ret) return ret;
    for (int next = 0; next < n; next++) {
        if (adj[here][next]) {
            ret += find(k - 1, next) / (double)sz[next];
        }
    }
    return ret;
}
void query() {
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int here;
        scanf("%d", &here);
        printf("%.12lf ", find(d, here));
    }
    printf("\n");
}
int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        reset();
        scanf("%d%d%d",&n,&d,&p);
        get_map();
        get_sz();
        query();
    }
}