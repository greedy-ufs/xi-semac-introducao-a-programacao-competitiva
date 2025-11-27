#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;

vector<vector<int>> adj(MAX);
vector<bool> vis(MAX);

void bfs(int s) {
    queue<int> q; q.push(s);
    vis[s] = true;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto u : adj[v]) if (!vis[u]) {
            q.push(u);
            vis[u] = true;
        }
    }
}