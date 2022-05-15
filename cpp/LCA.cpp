int timer;
int h[N];
int tin[N];
int tout[N];
int up[20][N];
void dfs(int v, int par, int lvl){
    h[v] = lvl;
    tin[v] = ++timer;
    up[0][v] = par;
    for (int i = 1; i < 20; i++){
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (auto u : g[v]){
        if (u == par) continue;
        dfs(u, v, lvl + 1);
    }
    tout[v] = ++timer;
}
bool anc(int v, int u){
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}
int lca(int v, int u){
    if (anc(v, u)) return v;
    if (anc(u, v)) return u;
    for (int i = 19; i >= 0; i--){
        if (!anc(up[i][v], u))
            v = up[i][v];
    }
    return up[0][v];
}
int dist(int v, int u){
    return h[v] + h[u] - 2 * h[lca(v, u)];
}
