#include <iostream>
#include <string>
#include <vector>
#define NIL (-1)
using namespace std;
struct UnionFind {
    vector<int> parent, enemy, size;
    int find(int node) {
        if (parent[node] == node) {
            return node;
        }
        int p = find(parent[node]);
        parent[node] = p;
        return p;
    }
    int merge(int node1, int node2) {
        if (node1 == NIL || node2 == NIL) return max(node1, node2);
        int p1 = find(node1), p2 = find(node2);
        if (p1 == p2) {
            return p1;
        }
        parent[p1] = p2;
        size[p2] += size[p1];
        return p2;
    }
    bool ack(int node1, int node2) {
        int p1 = find(node1), p2 = find(node2);
        if (enemy[p1] == p2) {
            return false;
        }
        int a = merge(p1, p2);
        int b = merge(enemy[p1], enemy[p2]);
        enemy[a] = b;
        if (b != NIL) enemy[b] = a;
        return true;
    }

    bool dis(int node1, int node2) {
        int p1 = find(node1), p2 = find(node2);
        if (p1 == p2) {
            return false;
        }
        int a = merge(p1, enemy[p2]);
        int b = merge(p2, enemy[p1]);
        enemy[a] = b;
        enemy[b] = a;
        return true;
    }
    UnionFind(int n) : parent(n),enemy(n,NIL),size(n,1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N, M;
        cin>>N>>M;
        string s;
        bool is_contradiction = false;
        int contradict_index = -1;
        UnionFind uf(N);
        for (int i = 1; i <= M; i++) {
            int a,b;
            cin>>s>>a>>b;
            if (is_contradiction) continue;
            if (s == "ACK") {
                bool res = uf.ack(a,b);
                if (!res) {
                    is_contradiction = true;
                    contradict_index = i;
                }
            } else {
                bool res = uf.dis(a,b);
                if (!res) {
                    is_contradiction = true;
                    contradict_index = i;
                }
            }
        }
        if (is_contradiction) {
            cout << "CONTRADICTION AT " << contradict_index << '\n';
        } else {
            int sum = 0;
            for (int i = 0; i < N; i++) {
                if (uf.parent[i] == i && uf.enemy[i] < i) {
                    sum += max(uf.size[i], (uf.enemy[i] == NIL ? 0 : uf.size[uf.enemy[i]]));
                }
            }
            cout << "MAX PARTY SIZE IS " << sum << '\n';
        }
    }
}
