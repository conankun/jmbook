#include <iostream>
#include <vector>
#define IS_ROOT(parent) (parent == -1)
using namespace std;
enum State {
    UNWATCHED = 0,
    WATCHED = 1,
    INSTALLED = 2,
};
struct Gallery {
    int G;
    vector<vector<int>> adj;
    int count;
    vector<bool> discovered;
    State dfs(int here, int parent) {
        discovered[here] = true;
        int child[3] = {0,0,0};
        for (auto next : adj[here]) {
            if (parent != next) {
                child[dfs(next, here)]++;
            }
        }
        if (child[UNWATCHED]) {
            count++;
            return INSTALLED;
        }
        if (child[INSTALLED]) {
            return WATCHED;
        }
        return UNWATCHED;
    }
    int solve() {
        for (int i = 0; i < G; i++) {
            if (!discovered[i]) {
                if(!dfs(i, -1)) count++;
            }
        }
        return count;
    }
    Gallery(int G) : G(G), adj(G), discovered(G, false), count(0) {}
};
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int G,H;
        cin>>G>>H;
        Gallery ga(G);
        for (int i = 0; i < H; i++) {
            int a,b;
            cin>>a>>b;
            ga.adj[a].push_back(b);
            ga.adj[b].push_back(a);
        }
        cout << ga.solve() << '\n';
    }
}
