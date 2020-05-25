#include <iostream>
#include <cmath>
#include <functional>
#include <queue>
#include <vector>
using namespace std;
struct Routing {
    int N, M;
    vector<vector<pair<int,double>>> adj;
    void input() {
      for (int i = 0; i < M; i++) {
          int a,b; double c;
          scanf("%d%d%lf", &a, &b, &c);
          c = log(c);
          adj[a].push_back({b,c});
          adj[b].push_back({a,c});
      }
    }
    double solve() {
        vector<double> dist(N, -1);
        queue<pair<int,double>> qu;
        dist[0] = 0;
        qu.push({0, 0});
        while (!qu.empty()) {
            auto top = qu.front(); qu.pop();
            int here = top.first; double d = top.second;
            if (d > dist[here]) continue;
            for (auto nn : adj[here]) {
                int next = nn.first; double delta = nn.second;
                if (dist[next] == -1 || dist[here] + delta < dist[next]) {
                    dist[next] = dist[here] + delta;
                    qu.push({next, dist[next]});
                }
            }
        }
        return exp(dist[N-1]);
    }
    Routing(int N, int M) : N(N), M(M), adj(N) {}
};
int main() {
    int C;
    scanf("%d", &C);
    while(C--) {
        int N, M;
        scanf("%d%d",&N,&M);
        Routing r(N, M);
        r.input();
        printf("%.12lf\n", r.solve());
    }
}