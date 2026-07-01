#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAX_N = 3e5 + 5;
const int INF = 1e9;
const ll LINF = 1e18;

// ==========================================
// 2-SAT PROBLEM
// Solves the 2-Satisfiability problem by converting boolean clauses into an implication graph.
// It uses Kosaraju's algorithm to find Strongly Connected Components (SCCs) to determine if a valid truth assignment exists.
// If a variable and its negation are in the same SCC, it's impossible; otherwise, it assigns truth values topologically.
// ==========================================
struct TwoSAT {
    int n, scc = 0;
    vector<vector<int>> adj[2];
    vector<int> vis, comp, dfn;
    TwoSAT(int n) : n(n), vis(2*n+1, 0), comp(2*n+1, 0) { adj[0].resize(2*n+1); adj[1].resize(2*n+1); }
    void add_clause(int u, bool cu, int v, bool cv) {
        int u1 = u*2 ^ (!cu), u2 = v*2 ^ (!cv);
        adj[0][u1^1].push_back(u2); adj[0][u2^1].push_back(u1);
        adj[1][u2].push_back(u1^1); adj[1][u1].push_back(u2^1);
    }
    void dfs(int u, int t) {
        vis[u] = 1; if (t == 1) comp[u] = scc;
        for (int v : adj[t][u]) if (!vis[v]) dfs(v, t);
        if (t == 0) dfn.push_back(u);
    }
    bool solve(vector<char>& ans) {
        for (int i = 1; i <= 2 * n; i++) if (!vis[i]) dfs(i, 0);
        fill(vis.begin(), vis.end(), 0);
        for (int i = 2 * n - 1; i >= 0; i--) if (!vis[dfn[i]]) { scc++; dfs(dfn[i], 1); }
        ans.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            ans[i] = comp[2 * i] > comp[2 * i + 1] ? '+' : '-';
        }
        return true;
    }
};

// ==========================================
// CLOSEST 3 POINTS (DIVIDE & CONQUER)
// Finds three points that form a triangle with the minimum possible perimeter.
// It uses a divide-and-conquer approach similar to the closest pair of points, running in O(N log N) time.
// The space is divided into halves, and a boundary strip is checked for closer points spanning the dividing line.
// ==========================================
namespace Closest3Points {
    struct pt { double x, y; };
    double dist(pt a, pt b) { return hypot(a.x - b.x, a.y - b.y); }
    double perimeter(pt a, pt b, pt c) { return dist(a, b) + dist(b, c) + dist(c, a); }
    double dac(vector<pt>& pts, int l, int r) {
        if (r - l <= 1) return INF;
        if (r - l == 2) return perimeter(pts[l], pts[l + 1], pts[l + 2]);
        int mid = l + (r - l) / 2;
        double ans = min(dac(pts, l, mid), dac(pts, mid + 1, r));
        vector<pt> strip;
        for (int i = l; i <= r; i++) if (abs(pts[i].x - pts[mid].x) < ans) strip.push_back(pts[i]);
        sort(strip.begin(), strip.end(), [](pt a, pt b){ return a.y < b.y; });
        for (size_t i = 0; i < strip.size(); i++)
            for (size_t j = i + 1; j < strip.size() && strip[j].y - strip[i].y < ans; j++)
                for (size_t k = j + 1; k < strip.size() && strip[k].y - strip[j].y < ans; k++)
                    ans = min(ans, perimeter(strip[i], strip[j], strip[k]));
        return ans;
    }
    double solve(vector<pt>& pts) {
        sort(pts.begin(), pts.end(), [](pt a, pt b){ return a.x < b.x; });
        return dac(pts, 0, pts.size() - 1);
    }
}

// ==========================================
// MAXIMUM HISTOGRAM AREA
// Finds the largest rectangular area that can be formed within a histogram in O(N) time.
// It maintains a monotonic increasing stack to efficiently find the left and right boundaries (smaller elements) for each bar.
// The area for each bar is calculated using these boundaries, and the global maximum is returned.
// ==========================================
ll max_histogram_area(const vector<int>& arr) {
    int n = arr.size(); stack<int> st; vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        l[i] = st.empty() ? 0 : st.top() + 1; st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        r[i] = st.empty() ? n - 1 : st.top() - 1; st.push(i);
    }
    ll mx = 0;
    for (int i = 0; i < n; i++) mx = max(mx, (ll)arr[i] * (r[i] - l[i] + 1));
    return mx;
}

// ==========================================
// MEDIAN HEAP
// Maintains the running median of a stream of incoming numbers in O(log N) time per insertion.
// It uses a max-heap to store the smaller half of the numbers and a min-heap for the larger half.
// The heaps are kept balanced so that the median is always readily accessible at the top of the max-heap.
// ==========================================
struct MedianHeap {
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;
    void insert(int x) {
        if (hi.empty() || x <= hi.top()) lo.push(x); else hi.push(x);
        if (lo.size() > hi.size() + 1) { hi.push(lo.top()); lo.pop(); }
        if (lo.size() < hi.size()) { lo.push(hi.top()); hi.pop(); }
    }
    void remove_median() {
        lo.pop();
        if (lo.size() != hi.size()) { lo.push(hi.top()); hi.pop(); }
    }
    int get_median() { return lo.top(); }
};

// ==========================================
// MEET IN THE MIDDLE
// Optimizes subset sum problems from O(2^N) to O(2^(N/2)), making it viable for N up to ~40.
// The array is split into two halves, and all possible subset sums are generated for each half independently.
// For each sum in the first half, binary search (upper_bound/lower_bound) is used to find matching complements in the sorted second half.
// ==========================================
ll meet_in_the_middle(const vector<ll>& arr, ll target) {
    int n = arr.size(), m1 = n / 2, m2 = n - m1;
    auto get_sums = [&](int st, int len) {
        vector<ll> sums;
        for (int i = 0; i < (1 << len); i++) {
            ll cur = 0;
            for (int j = 0; j < len; j++) if (i & (1 << j)) cur += arr[st + j];
            sums.push_back(cur);
        }
        sort(sums.begin(), sums.end());
        return sums;
    };
    auto sum1 = get_sums(0, m1), sum2 = get_sums(m1, m2);
    ll ans = 0;
    for (ll s1 : sum1) 
        ans += upper_bound(sum2.begin(), sum2.end(), target - s1) - lower_bound(sum2.begin(), sum2.end(), target - s1);
    return ans;
}

// ==========================================
// N QUEENS BACKTRACKING
// Counts the total number of valid ways to place N non-attacking queens on an N x N chessboard.
// It uses backtracking to place one queen per column while maintaining state arrays for rows and both diagonals.
// The algorithm efficiently skips placements on predefined obstacle squares (marked as '*').
// ==========================================
namespace NQueens {
    int n, ans; vector<int> r, c, d1, d2; vector<string> board;
    void place(int j) {
        if (j == n) { ans++; return; }
        if (c[j]) place(j + 1);
        else {
            for (int i = 0; i < n; i++) {
                if (board[i][j] != '*' && !r[i] && !d1[i + j] && !d2[i - j + n]) {
                    r[i] = d1[i + j] = d2[i - j + n] = 1;
                    place(j + 1);
                    r[i] = d1[i + j] = d2[i - j + n] = 0;
                }
            }
        }
    }
    int solve(const vector<string>& b) {
        board = b; n = b.size(); ans = 0;
        r.assign(n, 0); c.assign(n, 0); d1.assign(2*n, 0); d2.assign(2*n, 0);
        place(0); return ans;
    }
}

// ==========================================
// OFFLINE DYNAMIC CONNECTIVITY
// Answers connectivity queries in a graph where edges are dynamically added and removed over time.
// Since all queries are known upfront, it processes the lifespan of edges using a divide-and-conquer tree over time.
// A Disjoint Set Union (DSU) with rollback capabilities is used to add edges when going down the tree and undo them when backtracking.
// ==========================================
struct DSU_Rollback {
    int num; vector<int> p, sz; stack<int> st;
    DSU_Rollback(int n) : num(n), p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int u) { return u == p[u] ? u : find(p[u]); }
    bool same(int u, int v) { return find(u) == find(v); }
    void merge(int u, int v) {
        if (same(u, v)) return; u = find(u), v = find(v);
        if (sz[u] > sz[v]) swap(u, v);
        num--; sz[v] += sz[u]; p[u] = v; st.push(u);
    }
    void rollback(int t) {
        while (st.size() > t) {
            int u = st.top(); st.pop(); num++; sz[p[u]] -= sz[u]; p[u] = u;
        }
    }
};

struct OfflineDynamicConnectivity {
    struct Query { int t, type, id, u, v; };
    vector<Query> qs; vector<int> other, ans;
    void add_edge(int u, int v, int s_time, int e_time) {
        qs.push_back({s_time, 0, -1, u, v}); qs.push_back({e_time + 1, 1, -1, u, v});
    }
    void add_query(int u, int v, int time, int id) { qs.push_back({time, 2, id, u, v}); }
    void solve(int n, int q_count) {
        sort(qs.begin(), qs.end(), [](Query a, Query b){ return a.t < b.t; });
        other.resize(qs.size()); ans.assign(q_count, -1);
        map<pair<int,int>, int> mp;
        for (int i = 0; i < qs.size(); i++) {
            if (qs[i].type == 0) { mp[{qs[i].u, qs[i].v}] = i; other[i] = qs.size(); }
            else if (qs[i].type == 1) { other[mp[{qs[i].u, qs[i].v}]] = i; other[i] = mp[{qs[i].u, qs[i].v}]; }
        }
        DSU_Rollback dsu(n + 1);
        auto dco = [&](auto& self, int l, int r) -> void {
            if (l > r) return;
            if (l == r) { if (qs[l].type == 2) ans[qs[l].id] = dsu.same(qs[l].u, qs[l].v); return; }
            int mid = (l + r) / 2, save = dsu.st.size();
            for (int i = mid + 1; i <= r; i++) if (qs[i].type == 1 && other[i] < l) dsu.merge(qs[i].u, qs[i].v);
            self(self, l, mid); dsu.rollback(save);
            for (int i = l; i <= mid; i++) if (qs[i].type == 0 && other[i] > r) dsu.merge(qs[i].u, qs[i].v);
            self(self, mid + 1, r); dsu.rollback(save);
        };
        if (!qs.empty()) dco(dco, 0, qs.size() - 1);
    }
};

// ==========================================
// TREE PAINTING (EULER TOUR + SEGMENT TREE)
// Solves path query problems on trees (like counting painted edges between two nodes) using an Eulerian tour.
// The tree is flattened into an array where every edge appears twice (once going down, once going up), allowing path queries to be converted into range sum queries.
// A Segment Tree is then used to update edge states and query sums in O(log N) time, combined with LCA (Lowest Common Ancestor) to subtract paths outside the target range.
// ==========================================
struct TreePainting {
    int n; vector<vector<int>> g, e_ids;
    vector<int> dfs_list, edges_list, h, first, first1, first2;
    vector<int> lca_tree, tree1, tree2;
    vector<char> edge_used;
    TreePainting(int n) : n(n), g(n), e_ids(n), h(n, -1), first(n, -1), first1(n-1, -1), first2(n-1, -1), edge_used(n-1) {}
    void add_edge(int u, int v, int id) { g[u].push_back(v); g[v].push_back(u); e_ids[u].push_back(id); e_ids[v].push_back(id); }
    void dfs(int v, int cur_h = 1) {
        h[v] = cur_h; dfs_list.push_back(v);
        for (size_t i = 0; i < g[v].size(); ++i) {
            if (h[g[v][i]] == -1) {
                edges_list.push_back(e_ids[v][i]); dfs(g[v][i], cur_h + 1);
                edges_list.push_back(e_ids[v][i]); dfs_list.push_back(v);
            }
        }
    }
    void build_lca(int i, int l, int r) {
        if (l == r) { lca_tree[i] = dfs_list[l]; return; }
        int m = (l + r) >> 1; build_lca(i*2, l, m); build_lca(i*2+1, m+1, r);
        lca_tree[i] = h[lca_tree[i*2]] < h[lca_tree[i*2+1]] ? lca_tree[i*2] : lca_tree[i*2+1];
    }
    int q_lca(int i, int tl, int tr, int l, int r) {
        if (tl == l && tr == r) return lca_tree[i];
        int m = (tl + tr) >> 1;
        if (r <= m) return q_lca(i*2, tl, m, l, r);
        if (l > m) return q_lca(i*2+1, m+1, tr, l, r);
        int lt = q_lca(i*2, tl, m, l, m), rt = q_lca(i*2+1, m+1, tr, m+1, r);
        return h[lt] < h[rt] ? lt : rt;
    }
    int get_lca(int a, int b) {
        if (first[a] > first[b]) swap(a, b);
        return q_lca(1, 0, dfs_list.size() - 1, first[a], first[b]);
    }
    void upd_sum(vector<int>& t, int i, int l, int r, int j, int d) {
        t[i] += d; if (l >= r) return;
        int m = (l + r) >> 1; j <= m ? upd_sum(t, i*2, l, m, j, d) : upd_sum(t, i*2+1, m+1, r, j, d);
    }
    int q_sum(const vector<int>& t, int i, int tl, int tr, int l, int r) {
        if (l > r || tl > tr) return 0;
        if (tl == l && tr == r) return t[i];
        int m = (tl + tr) >> 1;
        if (r <= m) return q_sum(t, i*2, tl, m, l, r);
        if (l > m) return q_sum(t, i*2+1, m+1, tr, l, r);
        return q_sum(t, i*2, tl, m, l, m) + q_sum(t, i*2+1, m+1, tr, m+1, r);
    }
    void init() {
        dfs(0); lca_tree.assign(dfs_list.size() * 4, -1); build_lca(1, 0, dfs_list.size() - 1);
        for (size_t i = 0; i < dfs_list.size(); ++i) if (first[dfs_list[i]] == -1) first[dfs_list[i]] = i;
        for (size_t i = 0; i < edges_list.size(); ++i) {
            if (first1[edges_list[i]] == -1) first1[edges_list[i]] = i;
            else first2[edges_list[i]] = i;
        }
        tree1.assign(edges_list.size() * 4, 0); tree2.assign(edges_list.size() * 4, 0);
    }
    void paint_edge(int x, bool paint) {
        edge_used[x] = paint;
        upd_sum(tree1, 1, 0, edges_list.size()-1, first1[x], paint ? 1 : -1);
        upd_sum(tree2, 1, 0, edges_list.size()-1, first2[x], paint ? 1 : -1);
    }
    int query_path(int v1, int v2) {
        auto q = [&](int a, int b) {
            return q_sum(tree1, 1, 0, edges_list.size()-1, first[a], first[b]-1) - 
                   q_sum(tree2, 1, 0, edges_list.size()-1, first[a], first[b]-1);
        };
        int l = get_lca(v1, v2);
        return q(l, v1) + q(l, v2);
    }
};

// ==========================================
// SOLVE & MAIN
// ==========================================
void solve() {
    // Template entry point
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc = 1; 
    // cin >> tc;
    while (tc--) solve();
    return 0;
}