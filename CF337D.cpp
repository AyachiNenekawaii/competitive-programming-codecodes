#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

constexpr int inf = 1E9 + 10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, d;
    cin >> n >> m >> d;

    vector<int> e(n);
    for (int i = 0; i < m; i++) {
        int p;
        cin >> p;
        e[p - 1] = 1;
    }

    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<array<int, 2>> f(n, {-inf, -inf});
    auto dfs1 = [&](auto &self, int u, int p) ->void {
        if (e[u]) {
            f[u][0] = f[u][1] = 0;
        }
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            if (f[v][0] + 1 > f[u][0]) {
                f[u][1] = f[u][0];
                f[u][0] = f[v][0] + 1;
            } else {
                f[u][1] = max(f[u][1], f[v][0] + 1);
            }
        }
    };
    dfs1(dfs1, 0, -1);

    vector<int> g(n, -inf);
    auto dfs2 = [&](auto &self, int u, int p) ->void {
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            if (f[v][0] + 1 == f[u][0]) {
                g[v] = max(g[u] + 1, f[u][1] + 1);
            } else {
                g[v] = max(g[u] + 1, f[u][0] + 1);
            }
            self(self, v, u);
        }
    };
    dfs2(dfs2, 0, -1);

    int ans = max(f[0][0], f[0][1]) <= d;
    for (int i = 1; i < n; i++) {
        ans += (g[i] <= d && f[i][0] <= d);
    }

    cout << ans << "\n";

    return 0;
}
