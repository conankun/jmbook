#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define SQ(x) ((x) * (x))
#define D(x1, y1, x2, y2) (sqrt(SQ(x1-x2) + SQ(y1-y2)))
using namespace std;

struct UnionFind {
    vector<int> parent;
    int N;
    int find(int u) {
        if (parent[u] == u) return u;
        auto r =  find(parent[u]);
        parent[u] = r;
        return r;
    }

    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        parent[u] = v;
    }

    UnionFind(int N) : N(N), parent(N) {
        for (int i = 0; i < N; i++) parent[i] = i;
    }
};
struct Lan {
    int N, M;
    vector<pair<int,int>> xy;
    UnionFind uf;
    void input() {
        for (int i = 0; i < N; i++) scanf("%d", &xy[i].first);
        for (int i = 0; i < N; i++) scanf("%d", &xy[i].second);
        for (int i = 0; i < M; i++) {
            int a,b;
            scanf("%d%d",&a,&b);
            uf.merge(a,b);
        }
    }
    double solve() {
        vector<pair<double, pair<int,int>>> edges;
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                edges.push_back({D(xy[i].first, xy[i].second, xy[j].first, xy[j].second), {i, j}});
        sort(edges.begin(), edges.end());
        double sum = 0;
        for (auto edge : edges) {
            double w = edge.first;
            int u = edge.second.first, v = edge.second.second;
            if (uf.find(u) == uf.find(v)) continue;
            uf.merge(u, v);
            sum += w;
        }
        return sum;
    }
    Lan(int N, int M) : N(N), M(M), xy(N), uf(N) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    scanf("%d",&C);
    while(C--) {
        int N, M;
        scanf("%d%d",&N,&M);
        Lan l(N, M);
        l.input();
        printf("%.12lf\n", l.solve());
    }
}