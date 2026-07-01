#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar array
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// === POLICY BASED DATA STRUCTURES (PBDS) ===
// ordered_set: order_of_key(k) = count of elements < k, find_by_order(k) = k-th element iterator in O(log N)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// === DISJOINT SET UNION (DSU) ===
// Maintains disjoint sets with Union by Rank and Path Compression in O(alpha(N))
struct DSU {
    vector<int> p, sz; int comps;
    DSU(int n) : comps(n), p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int u) { return u == p[u] ? u : p[u] = find(p[u]); }
    bool merge(int u, int v) {
        u = find(u), v = find(v); if (u == v) return false;
        if (sz[u] > sz[v]) swap(u, v);
        p[u] = v; sz[v] += sz[u]; comps--; return true;
    }
};

// === MIN STACK / MIN QUEUE ===
// Maintains minimum element in a sliding window / queue in amortized O(1)
struct MinQueue {
    deque<pair<int, int>> q; int added = 0, removed = 0;
    void push(int x) { while (q.size() && q.back().first > x) q.pop_back(); q.push_back({x, added++}); }
    void pop() { if (q.size() && q.front().second == removed++) q.pop_front(); }
    int get_min() { return q.front().first; }
};

// === SPARSE TABLE ===
// Static Range Minimum Query (RMQ) in O(N log N) build, O(1) query
struct SparseTable {
    int n, k; vector<vector<int>> st;
    SparseTable(vector<int>& a) {
        n = a.size(); k = 32 - __builtin_clz(n); st.assign(k, vector<int>(n));
        for (int i = 0; i < n; i++) st[0][i] = a[i];
        for (int j = 1; j < k; j++) for (int i = 0; i + (1 << j) <= n; i++) st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    int query(int l, int r) { int j = 31 - __builtin_clz(r - l + 1); return min(st[j][l], st[j][r - (1 << j) + 1]); }
};

// === MO'S ALGORITHM (SQRT DECOMPOSITION) ===
// Offline query processing in O(N * sqrt(Q))
const int SQRT = 500;
struct MoQuery {
    int l, r, id;
    bool operator<(const MoQuery& o) const { return l / SQRT == o.l / SQRT ? ((l / SQRT) & 1 ? r < o.r : r > o.r) : l < o.l; }
};

// === TRIE ===
// Stores strings based on common prefixes in O(Length) time
struct Trie {
    vector<vector<int>> trie; vector<int> cnt; int num = 0;
    Trie(int max_nodes) : trie(max_nodes, vector<int>(26, 0)), cnt(max_nodes, 0) {}
    void insert(string s) { int u = 0; for (char c : s) { if (!trie[u][c - 'A']) trie[u][c - 'A'] = ++num; u = trie[u][c - 'A']; } cnt[u]++; }
    bool search(string s) { int u = 0; for (char c : s) { if (!trie[u][c - 'A']) return false; u = trie[u][c - 'A']; } return cnt[u] > 0; }
};

// === SUFFIX ARRAY ===
// Sorted array of all suffixes of a string in O(N log N)
vector<int> suffix_array(string s) {
    s += "$"; int n = s.size(); vector<int> p(n), c(n); vector<pair<char,int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i}; sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    for (int i = 1; i < n; i++) c[p[i]] = a[i].first == a[i - 1].first ? c[p[i - 1]] : c[p[i - 1]] + 1;
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        vector<int> np(n), nc(n), cnt(n, 0), pos(n);
        for (int x : p) cnt[c[x]]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int x : p) np[pos[c[x]]++] = x;
        p = np; nc[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]}, pre = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            nc[p[i]] = cur == pre ? nc[p[i - 1]] : nc[p[i - 1]] + 1;
        } c = nc;
    } return vector<int>(p.begin() + 1, p.end());
}

// === FENWICK TREES (BINARY INDEXED TREES) ===
// 1D Point Update, Range Query, and Order Statistic (find k-th smallest) in O(log N)
struct BIT {
    int n; vector<ll> ft;
    BIT(int n) : n(n), ft(n + 1, 0) {}
    void upd(int x, ll v) { for (; x <= n; x += x & -x) ft[x] += v; }
    ll sum(int x) { ll res = 0; for (; x; x -= x & -x) res += ft[x]; return res; }
    ll qry(int l, int r) { return sum(r) - sum(l - 1); }
    int find_kth(ll k) { int x = 0; for(int i = 1 << 31 - __builtin_clz(n); i > 0; i >>= 1) if(x + i <= n && ft[x + i] < k) k -= ft[x += i]; return x + 1; }
};
// Range Update, Point Query (RUPQ)
struct BIT_RUPQ {
    int n; vector<ll> ft;
    BIT_RUPQ(int n) : n(n), ft(n + 1, 0) {}
    void upd(int x, ll v) { for (; x <= n; x += x & -x) ft[x] += v; }
    void upd_range(int l, int r, ll v) { upd(l, v); upd(r + 1, -v); }
    ll qry_pt(int x) { ll res = 0; for (; x; x -= x & -x) res += ft[x]; return res; }
};
// Range Update, Range Query (RURQ)
struct BIT_RURQ {
    int n; vector<ll> ft1, ft2;
    BIT_RURQ(int n) : n(n), ft1(n + 1, 0), ft2(n + 1, 0) {}
    void upd(vector<ll>& ft, int x, ll v) { for (; x <= n; x += x & -x) ft[x] += v; }
    void upd_range(int l, int r, ll v) { upd(ft1, l, v); upd(ft1, r + 1, -v); upd(ft2, l, v * (l - 1)); upd(ft2, r + 1, -v * r); }
    ll sum(vector<ll>& ft, int x) { ll res = 0; for (; x; x -= x & -x) res += ft[x]; return res; }
    ll pref(int x) { return sum(ft1, x) * x - sum(ft2, x); }
    ll qry(int l, int r) { return pref(r) - pref(l - 1); }
};
// 2D Fenwick Tree for Point Update, Range Query in O(log^2 N)
struct BIT2D {
    int n; vector<vector<ll>> ft;
    BIT2D(int n) : n(n), ft(n + 1, vector<ll>(n + 1, 0)) {}
    void upd(int x, int y, ll v) { for (int i = x; i <= n; i += i & -i) for (int j = y; j <= n; j += j & -j) ft[i][j] += v; }
    ll sum(int x, int y) { ll res = 0; for (int i = x; i; i -= i & -i) for (int j = y; j; j -= j & -j) res += ft[i][j]; return res; }
    ll qry(int x1, int y1, int x2, int y2) { return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1); }
};
// Euler Tour for Subtree Updates: void dfs(int u, int p) { tin[u] = ++timer; for(int v : adj[u]) if(v != p) dfs(v, u); tout[u] = timer; }

// === TREAP (CARTESIAN TREE) ===
// Randomized BST supporting split/merge, dynamic range reversals and insertions in O(log N)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct TreapNode {
    int val, pri, sz; bool rev; TreapNode *ln, *rn;
    TreapNode(int v) : val(v), pri(rng()), sz(1), rev(0), ln(0), rn(0) {}
};
int tr_sz(TreapNode *t) { return t ? t->sz : 0; }
void tr_prop(TreapNode *t) { if (t && t->rev) { swap(t->ln, t->rn); if (t->ln) t->ln->rev ^= 1; if (t->rn) t->rn->rev ^= 1; t->rev = 0; } }
void tr_comb(TreapNode *t) { if (t) { tr_prop(t->ln); tr_prop(t->rn); t->sz = 1 + tr_sz(t->ln) + tr_sz(t->rn); } }
void tr_split(TreapNode *t, TreapNode *&l, TreapNode *&r, int k) {
    if (!t) { l = r = 0; return; } tr_prop(t);
    if (tr_sz(t->ln) < k) { tr_split(t->rn, t->rn, r, k - tr_sz(t->ln) - 1); l = t; }
    else { tr_split(t->ln, l, t->ln, k); r = t; } tr_comb(t);
}
void tr_merge(TreapNode *&t, TreapNode *l, TreapNode *r) {
    tr_prop(l); tr_prop(r); if (!l || !r) { t = l ? l : r; return; }
    if (l->pri > r->pri) { tr_merge(l->rn, l->rn, r); t = l; }
    else { tr_merge(r->ln, l, r->ln); t = r; } tr_comb(t);
}

// === HEAVY-LIGHT DECOMPOSITION (HLD) ===
// Decomposes trees into paths to answer queries (e.g. max edge) between any two nodes in O(log^2 N)
struct HLD {
    int n, timer; vector<int> sz, top, dep, par, in, out; vector<vector<int>> adj;
    HLD(int n) : n(n), timer(0), sz(n, 1), top(n), dep(n), par(n), in(n), out(n), adj(n) {}
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
    void dfs_sz(int u = 0, int p = -1, int d = 0) {
        par[u] = p; dep[u] = d; sz[u] = 1; if (adj[u].size() && adj[u][0] == p) swap(adj[u][0], adj[u].back());
        for (int& v : adj[u]) if (v != p) { dfs_sz(v, u, d + 1); sz[u] += sz[v]; if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]); }
    }
    void dfs_hld(int u = 0, int p = -1, int t = 0) {
        in[u] = timer++; top[u] = t;
        for (int v : adj[u]) if (v != p) dfs_hld(v, u, v == adj[u][0] ? t : v);
        out[u] = timer;
    }
    void build() { dfs_sz(); dfs_hld(); }
    int lca(int u, int v) {
        while (top[u] != top[v]) { if (dep[top[u]] < dep[top[v]]) swap(u, v); u = par[top[u]]; }
        return dep[u] < dep[v] ? u : v;
    }
};

// === BASIC SEGMENT TREE ===
// Point upd, Range Max/Sum, Find first >= val, Find K-th element (e.g. K-th zero) in O(log N)
struct SegTree {
    int n; vector<ll> mx, sum;
    SegTree(int n) : n(n), mx(4 * n, -LINF), sum(4 * n, 0) {}
    void upd(int i, ll x, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(l == r) { mx[v] = sum[v] = x; return; }
        int m = (l + r) / 2; if(i <= m) upd(i, x, 2*v, l, m); else upd(i, x, 2*v+1, m+1, r);
        mx[v] = max(mx[2*v], mx[2*v+1]); sum[v] = sum[2*v] + sum[2*v+1];
    }
    ll qry_max(int ql, int qr, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return -LINF;
        if(ql <= l && r <= qr) return mx[v]; int m = (l + r) / 2;
        return max(qry_max(ql, qr, 2*v, l, m), qry_max(ql, qr, 2*v+1, m+1, r));
    }
    int find_first(ll val, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(mx[v] < val) return -1; if(l == r) return l;
        int m = (l + r) / 2; int res = find_first(val, 2*v, l, m);
        return res != -1 ? res : find_first(val, 2*v+1, m+1, r);
    }
    int find_kth(ll k, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(k > sum[v]) return -1; if(l == r) return l;
        int m = (l + r) / 2; if (sum[2*v] >= k) return find_kth(k, 2*v, l, m);
        return find_kth(k - sum[2*v], 2*v+1, m+1, r);
    }
};

// === MAX & FREQUENCY SEGMENT TREE ===
// Maintains range maximum and the count of its occurrences in O(log N)
struct MaxFreqSeg {
    int n; vector<pair<int, int>> st;
    MaxFreqSeg(int n) : n(n), st(4 * n, {-INF, 0}) {}
    pair<int, int> comb(pair<int, int> a, pair<int, int> b) {
        if (a.first > b.first) return a; if (b.first > a.first) return b;
        return {a.first, a.second + b.second};
    }
    void upd(int i, int x, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(l == r) { st[v] = {x, 1}; return; }
        int m = (l + r) / 2; if(i <= m) upd(i, x, 2*v, l, m); else upd(i, x, 2*v+1, m+1, r);
        st[v] = comb(st[2*v], st[2*v+1]);
    }
    pair<int, int> qry(int ql, int qr, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return {-INF, 0};
        if(ql <= l && r <= qr) return st[v]; int m = (l + r) / 2;
        return comb(qry(ql, qr, 2*v, l, m), qry(ql, qr, 2*v+1, m+1, r));
    }
};

// === LAZY SEGMENT TREE ===
// Range Add, Range Set, Range Sum Query in O(log N)
struct LazySeg {
    int n; vector<ll> st, add, setv; vector<bool> lz;
    LazySeg(int n) : n(n), st(4*n, 0), add(4*n, 0), setv(4*n, 0), lz(4*n, 0) {}
    void push(int v, int l, int r) {
        int m = (l + r) / 2;
        if (lz[v]) {
            st[2*v] = setv[v] * (m - l + 1); st[2*v+1] = setv[v] * (r - m);
            setv[2*v] = setv[2*v+1] = setv[v]; add[2*v] = add[2*v+1] = 0;
            lz[2*v] = lz[2*v+1] = 1; lz[v] = 0;
        }
        if (add[v]) {
            st[2*v] += add[v] * (m - l + 1); st[2*v+1] += add[v] * (r - m);
            add[2*v] += add[v]; add[2*v+1] += add[v]; add[v] = 0;
        }
    }
    void upd_add(int ql, int qr, ll x, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return;
        if(ql <= l && r <= qr) { st[v] += x * (r - l + 1); add[v] += x; return; }
        push(v, l, r); int m = (l + r) / 2;
        upd_add(ql, qr, x, 2*v, l, m); upd_add(ql, qr, x, 2*v+1, m+1, r); st[v] = st[2*v] + st[2*v+1];
    }
    void upd_set(int ql, int qr, ll x, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return;
        if(ql <= l && r <= qr) { st[v] = x * (r - l + 1); setv[v] = x; add[v] = 0; lz[v] = 1; return; }
        push(v, l, r); int m = (l + r) / 2;
        upd_set(ql, qr, x, 2*v, l, m); upd_set(ql, qr, x, 2*v+1, m+1, r); st[v] = st[2*v] + st[2*v+1];
    }
    ll qry(int ql, int qr, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return 0;
        if(ql <= l && r <= qr) return st[v];
        push(v, l, r); int m = (l + r) / 2;
        return qry(ql, qr, 2*v, l, m) + qry(ql, qr, 2*v+1, m+1, r);
    }
};

// === RANGE TOGGLE SEGMENT TREE ===
// Range bitwise toggle and sum in O(log N)
struct ToggleSeg {
    int n; vector<int> st; vector<bool> lz;
    ToggleSeg(int n) : n(n), st(4*n, 0), lz(4*n, 0) {}
    void push(int v, int l, int r) {
        if(lz[v]) {
            int m = (l + r) / 2;
            st[2*v] = (m - l + 1) - st[2*v]; st[2*v+1] = (r - m) - st[2*v+1];
            lz[2*v] = !lz[2*v]; lz[2*v+1] = !lz[2*v+1]; lz[v] = 0;
        }
    }
    void upd(int ql, int qr, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return;
        if(ql <= l && r <= qr) { st[v] = (r - l + 1) - st[v]; lz[v] = !lz[v]; return; }
        push(v, l, r); int m = (l + r) / 2;
        upd(ql, qr, 2*v, l, m); upd(ql, qr, 2*v+1, m+1, r); st[v] = st[2*v] + st[2*v+1];
    }
    int qry(int ql, int qr, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return 0;
        if(ql <= l && r <= qr) return st[v];
        push(v, l, r); int m = (l + r) / 2; return qry(ql, qr, 2*v, l, m) + qry(ql, qr, 2*v+1, m+1, r);
    }
};

// === MAX SUBARRAY SUM SEGMENT TREE ===
// Query max subarray sum in a range. Node stores: sum, pref max, suff max, ans
struct MaxSubSeg {
    struct Node { ll sum, pref, suff, ans; };
    int n; vector<Node> st;
    MaxSubSeg(int n) : n(n), st(4*n, {0, 0, 0, 0}) {}
    Node comb(Node l, Node r) { return {l.sum + r.sum, max(l.pref, l.sum + r.pref), max(r.suff, r.sum + l.suff), max({l.ans, r.ans, l.suff + r.pref})}; }
    void upd(int i, ll x, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1;
        if(l == r) { st[v] = {x, max(0LL, x), max(0LL, x), max(0LL, x)}; return; }
        int m = (l + r) / 2; if(i <= m) upd(i, x, 2*v, l, m); else upd(i, x, 2*v+1, m+1, r);
        st[v] = comb(st[2*v], st[2*v+1]);
    }
    Node qry(int ql, int qr, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l) return {0, (ll)-LINF, (ll)-LINF, (ll)-LINF};
        if(ql <= l && r <= qr) return st[v]; int m = (l + r) / 2;
        return comb(qry(ql, qr, 2*v, l, m), qry(ql, qr, 2*v+1, m+1, r));
    }
};

// === PERSISTENT / DYNAMIC SEGMENT TREE ===
// Pointer-based. Dynamic allocates O(Q log N). Persistent creates new roots per update.
struct PSTNode {
    ll sum; PSTNode *l, *r;
    PSTNode(ll sum = 0) : sum(sum), l(0), r(0) {}
    PSTNode(PSTNode* l, PSTNode* r) : l(l), r(r), sum((l?l->sum:0) + (r?r->sum:0)) {}
};
PSTNode* pst_upd(PSTNode* node, int l, int r, int idx, ll val) {
    if (l == r) return new PSTNode((node?node->sum:0) + val);
    int m = (l + r) / 2;
    if (idx <= m) return new PSTNode(pst_upd(node?node->l:0, l, m, idx, val), node?node->r:0);
    return new PSTNode(node?node->l:0, pst_upd(node?node->r:0, m + 1, r, idx, val));
}
ll pst_qry(PSTNode* node, int l, int r, int ql, int qr) {
    if (!node || r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return node->sum;
    int m = (l + r) / 2; return pst_qry(node->l, l, m, ql, qr) + pst_qry(node->r, m + 1, r, ql, qr);
}
int pst_kth(PSTNode* l_node, PSTNode* r_node, int l, int r, int k) { // K-th smallest in range [L, R]
    if (l == r) return l;
    int count = (r_node && r_node->l ? r_node->l->sum : 0) - (l_node && l_node->l ? l_node->l->sum : 0);
    int m = (l + r) / 2;
    if (count >= k) return pst_kth(l_node ? l_node->l : 0, r_node ? r_node->l : 0, l, m, k);
    return pst_kth(l_node ? l_node->r : 0, r_node ? r_node->r : 0, m + 1, r, k - count);
}

// === 2D SEGMENT TREE ===
// Range sum query over 2D grid in O(log N * log M)
struct SegTree2D {
    int n, m; vector<vector<int>> st;
    SegTree2D(int n, int m) : n(n), m(m), st(4*n, vector<int>(4*m, 0)) {}
    void upd_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int val) {
        if (ly == ry) { if (lx == rx) st[vx][vy] = val; else st[vx][vy] = st[vx*2][vy] + st[vx*2+1][vy]; return; }
        int my = (ly + ry) / 2; if (y <= my) upd_y(vx, lx, rx, vy*2, ly, my, x, y, val); else upd_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, val);
        st[vx][vy] = st[vx][vy*2] + st[vx][vy*2+1];
    }
    void upd_x(int vx, int lx, int rx, int x, int y, int val) {
        if (lx != rx) { int mx = (lx + rx) / 2; if (x <= mx) upd_x(vx*2, lx, mx, x, y, val); else upd_x(vx*2+1, mx+1, rx, x, y, val); }
        upd_y(vx, lx, rx, 1, 0, m - 1, x, y, val);
    }
    int qry_y(int vx, int vy, int ly, int ry, int qly, int qry_) {
        if (ly > qry_ || ry < qly) return 0; if (qly <= ly && ry <= qry_) return st[vx][vy];
        int my = (ly + ry) / 2; return qry_y(vx, vy*2, ly, my, qly, qry_) + qry_y(vx, vy*2+1, my+1, ry, qly, qry_);
    }
    int qry_x(int vx, int lx, int rx, int qlx, int qrx, int qly, int qry_) {
        if (lx > qrx || rx < qlx) return 0; if (qlx <= lx && rx <= qrx) return qry_y(vx, 1, 0, m - 1, qly, qry_);
        int mx = (lx + rx) / 2; return qry_x(vx*2, lx, mx, qlx, qrx, qly, qry_) + qry_x(vx*2+1, mx+1, rx, qlx, qrx, qly, qry_);
    }
};

// === SEGMENT TREE BEATS ===
// Supports range chmin, chmax, and add in O(log^2 N) amortized
struct SegTreeBeats {
    struct Node { ll sum, mx, mx2, mxc, mn, mn2, mnc, add; };
    int n; vector<Node> st;
    SegTreeBeats(int n) : n(n), st(4*n) {}
    void merge(int v) {
        st[v].sum = st[2*v].sum + st[2*v+1].sum;
        if (st[2*v].mx > st[2*v+1].mx) { st[v].mx = st[2*v].mx; st[v].mxc = st[2*v].mxc; st[v].mx2 = max(st[2*v].mx2, st[2*v+1].mx); }
        else if (st[2*v].mx < st[2*v+1].mx) { st[v].mx = st[2*v+1].mx; st[v].mxc = st[2*v+1].mxc; st[v].mx2 = max(st[2*v].mx, st[2*v+1].mx2); }
        else { st[v].mx = st[2*v].mx; st[v].mxc = st[2*v].mxc + st[2*v+1].mxc; st[v].mx2 = max(st[2*v].mx2, st[2*v+1].mx2); }
        if (st[2*v].mn < st[2*v+1].mn) { st[v].mn = st[2*v].mn; st[v].mnc = st[2*v].mnc; st[v].mn2 = min(st[2*v].mn2, st[2*v+1].mn); }
        else if (st[2*v].mn > st[2*v+1].mn) { st[v].mn = st[2*v+1].mn; st[v].mnc = st[2*v+1].mnc; st[v].mn2 = min(st[2*v].mn, st[2*v+1].mn2); }
        else { st[v].mn = st[2*v].mn; st[v].mnc = st[2*v].mnc + st[2*v+1].mnc; st[v].mn2 = min(st[2*v].mn2, st[2*v+1].mn2); }
    }
    void apply_add(int v, int l, int r, ll x) { st[v].sum += x * (r - l + 1); st[v].mx += x; st[v].mn += x; if(st[v].mx2 != -LINF) st[v].mx2 += x; if(st[v].mn2 != LINF) st[v].mn2 += x; st[v].add += x; }
    void apply_mx(int v, ll x) { st[v].sum += (x - st[v].mx) * st[v].mxc; if(st[v].mn == st[v].mx) st[v].mn = x; if(st[v].mn2 == st[v].mx) st[v].mn2 = x; st[v].mx = x; }
    void apply_mn(int v, ll x) { st[v].sum += (x - st[v].mn) * st[v].mnc; if(st[v].mx == st[v].mn) st[v].mx = x; if(st[v].mx2 == st[v].mn) st[v].mx2 = x; st[v].mn = x; }
    void push(int v, int l, int r) {
        int m = (l + r) / 2; if (st[v].add) { apply_add(2*v, l, m, st[v].add); apply_add(2*v+1, m+1, r, st[v].add); st[v].add = 0; }
        if (st[2*v].mx > st[v].mx) apply_mx(2*v, st[v].mx); if (st[2*v+1].mx > st[v].mx) apply_mx(2*v+1, st[v].mx);
        if (st[2*v].mn < st[v].mn) apply_mn(2*v, st[v].mn); if (st[2*v+1].mn < st[v].mn) apply_mn(2*v+1, st[v].mn);
    }
    void upd_chmin(int ql, int qr, ll x, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; if(ql > r || qr < l || st[v].mx <= x) return;
        if(ql <= l && r <= qr && st[v].mx2 < x) { apply_mx(v, x); return; }
        push(v, l, r); int m = (l + r) / 2; upd_chmin(ql, qr, x, 2*v, l, m); upd_chmin(ql, qr, x, 2*v+1, m+1, r); merge(v);
    }
    // upd_chmax and upd_add follow similar logic structure utilizing apply_mn and apply_add
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