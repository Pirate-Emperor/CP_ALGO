#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar array
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// === BASIC TRAVERSALS & TOPOLOGICAL SORT ===
// BFS, 0-1 BFS, DFS, Bipartite Check, and Topological Sort (Kahn's Algorithm)
struct Graph {
    int n; vector<vector<int>> adj; vector<vector<ar<int,2>>> adjW; 
    Graph(int n) : n(n), adj(n), adjW(n) {}
    void add_edge(int u, int v, int w = 1) { adj[u].push_back(v); adjW[u].push_back({v, w}); }
    vector<int> bfs(int s) {
        vector<int> dist(n, -1); queue<int> q({s}); dist[s] = 0;
        while (q.size()) { int u = q.front(); q.pop(); for (int v : adj[u]) if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); } } return dist;
    }
    vector<int> bfs_01(int s) { // 0-1 BFS using deque in O(V + E)
        vector<int> dist(n, INF); deque<int> q({s}); dist[s] = 0;
        while (q.size()) {
            int u = q.front(); q.pop_front();
            for (auto [v, w] : adjW[u]) if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; w ? q.push_back(v) : q.push_front(v); }
        } return dist;
    }
    bool is_bipartite(int s) {
        vector<int> color(n, 0); queue<int> q({s}); color[s] = 1;
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) { if (!color[v]) { color[v] = color[u] % 2 + 1; q.push(v); } else if (color[v] == color[u]) return false; }
        } return true;
    }
    vector<int> topo_sort() { // Kahn's Algorithm in O(V + E)
        vector<int> in(n, 0), topo; queue<int> q;
        for (int u = 0; u < n; u++) for (int v : adj[u]) in[v]++;
        for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
        while (q.size()) { int u = q.front(); q.pop(); topo.push_back(u); for (int v : adj[u]) if (!--in[v]) q.push(v); }
        return topo.size() == n ? topo : vector<int>(); // Returns empty if cycle exists
    }
};

// === SHORTEST PATHS ===
// Dijkstra O((V+E)logV), Bellman-Ford O(VE), Floyd-Warshall O(V^3)
struct ShortestPaths {
    int n; vector<vector<ar<ll,2>>> adj;
    ShortestPaths(int n) : n(n), adj(n) {}
    void add_edge(int u, int v, ll w) { adj[u].push_back({v, w}); }
    vector<ll> dijkstra(int s) {
        vector<ll> dist(n, LINF); priority_queue<ar<ll,2>, vector<ar<ll,2>>, greater<ar<ll,2>>> pq;
        dist[s] = 0; pq.push({0, s});
        while (pq.size()) {
            auto [d, u] = pq.top(); pq.pop(); if (d > dist[u]) continue;
            for (auto [v, w] : adj[u]) if (dist[v] > dist[u] + w) pq.push({dist[v] = dist[u] + w, v});
        } return dist;
    }
    bool bellman_ford(int s, vector<ll>& dist) { // Returns true if negative cycle exists
        dist.assign(n, LINF); dist[s] = 0; bool cycle = false;
        for (int i = 0; i < n; i++) {
            cycle = false;
            for (int u = 0; u < n; u++) if (dist[u] != LINF)
                for (auto [v, w] : adj[u]) if (dist[v] > dist[u] + w) { dist[v] = dist[u] + w; cycle = true; }
        } return cycle;
    }
    vector<vector<ll>> floyd_warshall(vector<vector<ll>> dist) { // Initialize missing edges with LINF, self with 0
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            if (dist[i][k] != LINF && dist[k][j] != LINF) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        return dist;
    }
};

// === MINIMUM SPANNING TREE (MST) ===
// Kruskal O(E log V) with DSU, Prim O((V+E)logV)
struct DSU { vector<int> p; DSU(int n) : p(n, -1) {} int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); } bool merge(int x, int y) { x=find(x), y=find(y); if(x==y) return false; if(p[x]>p[y]) swap(x,y); p[x]+=p[y]; p[y]=x; return true; } };
ll kruskal(int n, vector<ar<int,3>>& edges) { // {weight, u, v}
    sort(edges.begin(), edges.end()); DSU dsu(n + 1); ll cost = 0; int cnt = 0;
    for (auto [w, u, v] : edges) if (dsu.merge(u, v)) { cost += w; cnt++; }
    return cnt == n - 1 ? cost : -1;
}
ll prim(int n, int s, vector<vector<ar<ll,2>>>& adj) {
    ll cost = 0; vector<bool> vis(n + 1, 0); priority_queue<ar<ll,2>, vector<ar<ll,2>>, greater<ar<ll,2>>> pq; pq.push({0, s});
    while (pq.size()) {
        auto [w, u] = pq.top(); pq.pop(); if (vis[u]) continue;
        cost += w; vis[u] = 1; for (auto [v, dw] : adj[u]) if (!vis[v]) pq.push({dw, v});
    } return cost; // Add connectedness check if required
}

// === CONNECTIVITY (BRIDGES, ARTICULATIONS, SCC) ===
// Tarjan's SCC and Bridge/Articulation Point finders in O(V + E)
struct Connectivity {
    int n, timer, scc_cnt; vector<vector<int>> adj; vector<int> tin, low, comp, st; vector<bool> in_st, is_art; vector<ar<int,2>> bridges;
    Connectivity(int n) : n(n), adj(n), tin(n, -1), low(n, -1), comp(n, -1), in_st(n, 0), is_art(n, 0), timer(0), scc_cnt(0) {}
    void add_edge(int u, int v) { adj[u].push_back(v); } // Undirected for bridges, Directed for SCC
    void dfs_bridges(int u, int p = -1) {
        tin[u] = low[u] = timer++; int child = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (tin[v] != -1) low[u] = min(low[u], tin[v]);
            else { dfs_bridges(v, u); low[u] = min(low[u], low[v]); child++; if (low[v] > tin[u]) bridges.push_back({u, v}); if (low[v] >= tin[u] && p != -1) is_art[u] = 1; }
        } if (p == -1 && child > 1) is_art[u] = 1;
    }
    void tarjan_scc(int u) {
        tin[u] = low[u] = timer++; st.push_back(u); in_st[u] = 1;
        for (int v : adj[u]) { if (tin[v] == -1) { tarjan_scc(v); low[u] = min(low[u], low[v]); } else if (in_st[v]) low[u] = min(low[u], tin[v]); }
        if (low[u] == tin[u]) { while (true) { int v = st.back(); st.pop_back(); in_st[v] = 0; comp[v] = scc_cnt; if (u == v) break; } scc_cnt++; }
    }
    int check_eulerian(bool directed = false) { // 0: None, 1: Euler Path, 2: Euler Cycle (assumes 1 connected comp)
        int odd = 0; for (int i = 0; i < n; i++) if (adj[i].size() & 1) odd++; return odd == 0 ? 2 : (odd == 2 ? 1 : 0);
    }
};

// === FLOOD FILL (GRID TRAVERSAL) ===
// 2D Grid DFS for connected components in O(R * C)
const int di[] = {1, 0, -1, 0}, dj[] = {0, -1, 0, 1};
void flood_fill(int i, int j, int r, int c, vector<string>& grid, vector<vector<bool>>& vis) {
    vis[i][j] = 1;
    for (int k = 0; k < 4; k++) {
        int ni = i + di[k], nj = j + dj[k];
        if (ni >= 0 && nj >= 0 && ni < r && nj < c && grid[ni][nj] == '.' && !vis[ni][nj]) flood_fill(ni, nj, r, c, grid, vis);
    }
}

// === KUHN'S MAXIMAL BIPARTITE MATCHING ===
// Finds maximum matching in a bipartite graph in O(V * E)
struct Kuhn {
    int n, m; vector<vector<int>> adj; vector<int> mt; vector<bool> vis;
    Kuhn(int n, int m) : n(n), m(m), adj(n), mt(m, -1), vis(n) {}
    void add_edge(int u, int v) { adj[u].push_back(v); } // u in left (size n), v in right (size m)
    bool dfs(int u) {
        if (vis[u]) return false; vis[u] = 1;
        for (int v : adj[u]) if (mt[v] == -1 || dfs(mt[v])) { mt[v] = u; return true; } return false;
    }
    int max_matching() { int res = 0; for (int i = 0; i < n; i++) { vis.assign(n, 0); if (dfs(i)) res++; } return res; }
};

// === MAX FLOW (DINIC & EDMONDS-KARP) ===
// Dinic: O(V^2 E) (fastest generally). Both operate on the same residual graph structure.
struct MaxFlow {
    struct Edge { int u, v, cap, flow; };
    int n; vector<Edge> el; vector<vector<int>> adj; vector<int> d, ptr, par;
    MaxFlow(int n) : n(n), adj(n), d(n), ptr(n), par(n) {}
    void add_edge(int u, int v, int cap) {
        adj[u].push_back(el.size()); el.push_back({u, v, cap, 0});
        adj[v].push_back(el.size()); el.push_back({v, u, 0, 0}); // Add reverse edge with 0 capacity
    }
    bool bfs(int s, int t) {
        d.assign(n, -1); d[s] = 0; queue<int> q({s});
        while (q.size()) {
            int u = q.front(); q.pop(); if (u == t) break;
            for (int id : adj[u]) if (el[id].cap > el[id].flow && d[el[id].v] == -1) { d[el[id].v] = d[u] + 1; par[el[id].v] = id; q.push(el[id].v); }
        } return d[t] != -1;
    }
    int dfs(int u, int t, int f) {
        if (u == t || !f) return f;
        for (int& i = ptr[u]; i < (int)adj[u].size(); i++) {
            int id = adj[u][i], v = el[id].v; if (d[v] != d[u] + 1) continue;
            if (int pushed = dfs(v, t, min(f, el[id].cap - el[id].flow))) { el[id].flow += pushed; el[id ^ 1].flow -= pushed; return pushed; }
        } return 0;
    }
    ll dinic(int s, int t) { ll mf = 0; while (bfs(s, t)) { ptr.assign(n, 0); while (int f = dfs(s, t, INF)) mf += f; } return mf; }
};

// === LOWEST COMMON ANCESTOR (BINARY LIFTING & RMQ) ===
// LCA using jump pointers: O(N log N) build, O(log N) query
struct LCA_BinaryLifting {
    int n, l; vector<vector<int>> up, adj; vector<int> dep;
    LCA_BinaryLifting(int n) : n(n), l(ceil(log2(n))), up(n + 1, vector<int>(l + 1)), dep(n + 1), adj(n + 1) {}
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
    void dfs(int u, int p = 0, int d = 0) {
        up[u][0] = p; dep[u] = d; for (int i = 1; i <= l; i++) up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u]) if (v != p) dfs(v, u, d + 1);
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = l; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v]) u = up[u][i];
        if (u == v) return u;
        for (int i = l; i >= 0; i--) if (up[u][i] != up[v][i]) u = up[u][i], v = up[v][i];
        return up[u][0];
    }
};

// === SOLVE & MAIN ===
void solve() {
    // Template entry point
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int tc = 1; 
    // cin >> tc;
    while (tc--) solve();
    return 0;
}