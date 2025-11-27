#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;

vector<vector<int>> adj(MAX);
vector<bool> vis(MAX);

void dfs(int v) {
    vis[v] = true;
    for (auto u : adj[v]) if (!vis[u]) {
        dfs(u);
    }
}