# The 7-Day Template Forge Arsenal

**Execution Rules:**

1. Open a blank text editor. No autocomplete, no LSP.
2. Type the **Daily Core Warmup** (Math/Bits) every single day (takes 2 minutes).
3. Pick your designated **Batch for the Day** and blind-type the algorithms.
4. Compile and test against extreme edge cases (e.g., $N=1$, all zeros).
5. Review the **Reading/Memory Vault** passively during meals or downtime.

## The Daily Core Warmup (Every Day)

*Fast, universal math and bits. Type this before starting your daily batch.*

### 1. Math Fundamentals (`qexp`, `gcd`, `ext_gcd`, `inv_mod`)

```cpp
long long qexp(long long a, long long b, long long m = MOD) {
    long long res = 1; a %= m;
    while (b) { if (b & 1) res = (long long)((__int128_t)res * a % m); a = (long long)((__int128_t)a * a % m); b >>= 1; }
    return res;
}
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (!b) { x = 1; y = 0; return a; }
    long long x1, y1, d = ext_gcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b); return d;
}
long long inv_mod(long long a, long long m) { 
    long long x, y; long long g = ext_gcd(a, m, x, y); 
    if (g != 1) return -1;
    return (m + x % m) % m; 
}

```

### 2. Linear Sieve ($O(N)$ Prime Factorization) & Mobius & Totient & more

```cpp
namespace Primes {
    const int MAX_N = 200005;
    int spf[MAX_N], phi[MAX_N], mu[MAX_N];
    vector<int> primes;
    void prec() {
        phi[1] = 1; mu[1] = 1;
        for (int i = 2; i < MAX_N; i++) {
            if (!spf[i]) { spf[i] = i; primes.push_back(i); phi[i] = i - 1; mu[i] = -1; }
            for (int p : primes) {
                if (p > spf[i] || i * p >= MAX_N) break;
                spf[i * p] = p;
                if (i % p == 0) { phi[i * p] = phi[i] * p; mu[i * p] = 0; break; }
                else { phi[i * p] = phi[i] * (p - 1); mu[i * p] = -mu[i]; }
            }
        }
    }
    vector<array<ll, 2>> factorize(ll n) {
        vector<array<ll, 2>> res;
        for (int p : primes) {
            if (1LL * p * p > n) break;
            if (n % p == 0) { int c = 0; while (n % p == 0) { n /= p; c++; } res.push_back({(ll)p, c}); }
        }
        if (n > 1) res.push_back({n, 1}); return res;
    }
    vector<array<ll, 2>> factors_spf(ll n) { // Fast factorization using SPF in O(log N)
        vector<array<ll, 2>> res;
        while (n > 1) {
            int c = 0; ll p = spf[n];
            while (n % p == 0) { n /= p; c++; }
            res.push_back({p, c});
        }
        return res;
    }
    ll NOD(ll n) { ll res = 1; for (auto [p, c] : factorize(n)) res *= (c + 1); return res; }
    ll SOD(ll n) { ll res = 1; for (auto [p, c] : factorize(n)) { ll sum = 1, pw = 1; while (c--) sum += (pw *= p); res *= sum; } return res; }
    array<ll, 2> count_prime_factors(ll n) { array<ll, 2> res = {0, 0}; for (auto [p, c] : factorize(n)) { res[0]++; res[1] += c; } return res; }
    ll get_phi(ll n) { ll res = n; for (auto [p, c] : factorize(n)) res -= res / p; return res; } // Euler's Totient for isolated large N
}
vector<ll> get_divisors(ll n) { // Divisors in O(sqrt(N))
    vector<ll> d;
    for (ll i = 1; i * i <= n; i++) if (n % i == 0) { d.push_back(i); if (i * i != n) d.push_back(n / i); }
    sort(d.begin(), d.end()); return d;
}

```

### 3. Bit Manipulation Macros & Fundamentals

```cpp
#define getbit(x,i) (((x)>>(i))&1LL)            // Extract bit at index i exactly as 0 or 1
#define setbit(x,i) ((x)|(1LL<<(i)))            // Set at index i to 1
#define clearbit(x,i) ((x)&(~(1LL<<(i))))       // Set at index i to 0
#define togglebit(x,i) ((x)^(1LL<<(i)))         // Toggle between 0 and 1
#define lowbit(x) ((x)&(-(x)))                  // Isolate lowest set bit
#define strip_lowbit(x) ((x)-((x)&(-(x))))      // Clear lowest set bit
#define is_pow2(x) ((x)&&(((x)&((x)-1LL))==0))  // Check if exact power of 2
#define is_allones(x) ((x)&&(((x)&((x)+1LL))==0)) // Check if binary representation is all 1s
#define all_ones(n) ((1LL<<(n))-1LL)            // Generate n-bit mask of all 1s

// Built-ins: __builtin_popcountll(x), __builtin_ctzll(x) [trailing 0s], __builtin_clzll(x) [leading 0s]

// Count 1s in binary representations of all numbers from 1 to N in O(log N)
long long count1s_ton(long long n) { 
    long long c = 0; 
    for(int i=61; i>=0; i--) {
        if(n & (1LL<<i)) { 
            c += (i ? (1LL<<(i-1))*i : 0) + (n-(1LL<<i)+1); 
            n -= (1LL<<i); 
        } 
    } 
    return c; 
}

```

## Batch 1: Range Queries (Monday)

### 1. Lazy Segment Tree (1D Range Add / Range Sum)

```cpp
struct LazySeg {
    int n; vector<long long> st, add; vector<bool> lz;
    LazySeg(int n) : n(n), st(4*n, 0), add(4*n, 0), lz(4*n, 0) {}
    
    void push(int v, int l, int r) {
        if (add[v]) {
            int m = (l + r) / 2;
            st[2*v] += add[v] * (m - l + 1); st[2*v+1] += add[v] * (r - m);
            add[2*v] += add[v]; add[2*v+1] += add[v]; 
            add[v] = 0;
        }
    }
    
    void upd_add(int ql, int qr, long long x, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; 
        if(ql > r || qr < l) return;
        if(ql <= l && r <= qr) { st[v] += x * (r - l + 1); add[v] += x; return; }
        push(v, l, r); int m = (l + r) / 2;
        upd_add(ql, qr, x, 2*v, l, m); upd_add(ql, qr, x, 2*v+1, m+1, r); 
        st[v] = st[2*v] + st[2*v+1];
    }
    
    long long qry(int ql, int qr, int v=1, int l=0, int r=-1) {
        if(r==-1) r = n - 1; 
        if(ql > r || qr < l) return 0;
        if(ql <= l && r <= qr) return st[v];
        push(v, l, r); int m = (l + r) / 2;
        return qry(ql, qr, 2*v, l, m) + qry(ql, qr, 2*v+1, m+1, r);
    }
};
```

### 2. Fenwick Tree (Binary Indexed Tree)

```cpp
struct BIT {
    int n; vector<long long> ft;
    BIT(int n) : n(n), ft(n + 1, 0) {}
    void upd(int x, long long v) { for (; x <= n; x += lowbit(x)) ft[x] += v; }
    long long sum(int x) { long long res = 0; for (; x; x -= lowbit(x)) res += ft[x]; return res; }
    long long qry(int l, int r) { return sum(r) - sum(l - 1); }
};
```

### 3. Mo's Algorithm (Sqrt Decomposition)

```cpp
const int SQRT = 500;
struct MoQuery {
    int l, r, id;
    bool operator<(const MoQuery& o) const { 
        return l / SQRT == o.l / SQRT ? ((l / SQRT) & 1 ? r < o.r : r > o.r) : l < o.l; 
    }
};
```

## Batch 2: Graph Core (Tuesday)

### 1. Dijkstra's Algorithm

```cpp
vector<long long> dijkstra(int s, int n, const vector<vector<array<long long, 2>>>& adj) {
    vector<long long> dist(n, 1e18); 
    priority_queue<array<long long, 2>, vector<array<long long, 2>>, greater<array<long long, 2>>> pq;
    dist[s] = 0; pq.push({0, s});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop(); 
        if (d > dist[u]) continue; // CRITICAL: Stale pair check
        
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    } 
    return dist;
}
```

### 2. 0-1 BFS

```cpp
vector<int> bfs_01(int s, int n, const vector<vector<array<int, 2>>>& adjW) {
    vector<int> dist(n, 1e9); 
    deque<int> q({s}); dist[s] = 0;
    
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        for (auto [v, w] : adjW[u]) {
            if (dist[u] + w < dist[v]) { 
                dist[v] = dist[u] + w; 
                w ? q.push_back(v) : q.push_front(v); 
            }
        }
    } 
    return dist;
}
```

### 3. Kahn’s Topological Sort

```cpp
vector<int> topo_sort(int n, const vector<vector<int>>& adj) {
    vector<int> in(n, 0), topo; queue<int> q;
    for (int u = 0; u < n; u++) for (int v : adj[u]) in[v]++;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    
    while (!q.empty()) { 
        int u = q.front(); q.pop(); topo.push_back(u); 
        for (int v : adj[u]) if (!--in[v]) q.push(v); 
    }
    return topo.size() == n ? topo : vector<int>(); // Empty if cycle exists
}
```

### 4. Kuhn's Bipartite Matching (Optimized $O(VE)$)

```cpp
struct Kuhn {
    int n, m, timer; vector<vector<int>> adj; vector<int> mt, vis;
    Kuhn(int n, int m) : n(n), m(m), timer(0), adj(n), mt(m, -1), vis(n, 0) {}
    void add_edge(int u, int v) { adj[u].push_back(v); }
    bool dfs(int u) {
        if (vis[u] == timer) return false; // Eliminates O(N) assign overhead
        vis[u] = timer;
        for (int v : adj[u]) if (mt[v] == -1 || dfs(mt[v])) { mt[v] = u; return true; } 
        return false;
    }
    int max_matching() { 
        int res = 0; 
        for (int i = 0; i < n; i++) { timer++; if (dfs(i)) res++; } 
        return res; 
    }
};
```

## Batch 3: Strings & Combinatorics (Wednesday)

### 1. KMP Prefix Function

```cpp
vector<int> prefix_func(const string& s) {
    int n = s.size(); vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        pi[i] = j + (s[i] == s[j]);
    }
    return pi;
}
```

### 2. Z-Algorithm

```cpp
vector<int> z_func(const string& s) {
    int n = s.size(); vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
```

### 3. Manacher's Algorithm

```cpp
vector<int> manacher(string s) {
    int n = s.size(), l = 1, r = 1; s = "$" + s + "^"; vector<int> p(n + 2);
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) p[i]++;
        if (i + p[i] > r) l = i - p[i], r = i + p[i];
    }
    return vector<int>(p.begin() + 1, p.end() - 1);
}
```

### 4. Lyndon Factorization (Min Cyclic Shift)

```cpp
string min_cyclic_string(string s) {
    s += s; int n = s.size(), i = 0, ans = 0;
    while (i < n / 2) {
        ans = i; int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) { s[k] < s[j] ? k = i : k++; j++; }
        while (i <= k) i += j - k;
    }
    return s.substr(ans, n / 2);
}
```

### 5. Combinatorics ($nCr$, Catalan, Stars & Bars) & Mint Struct

```cpp
const int MOD = 1e9 + 7;
struct Mint {
    int v;
    Mint(long long x = 0) : v((x % MOD + MOD) % MOD) {}
    Mint& operator+=(Mint o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    Mint& operator-=(Mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    Mint& operator*=(Mint o) { v = (long long)v * o.v % MOD; return *this; }
    friend Mint operator+(Mint a, Mint b) { return a += b; }
    friend Mint operator-(Mint a, Mint b) { return a -= b; }
    friend Mint operator*(Mint a, Mint b) { return a *= b; }
    Mint pow(long long k) const {
        Mint res = 1, a = *this;
        while (k) { if (k & 1) res *= a; a *= a; k >>= 1; }
        return res;
    }
    Mint inv() const { return pow(MOD - 2); }
    Mint& operator/=(Mint o) { return *this *= o.inv(); }
    friend Mint operator/(Mint a, Mint b) { return a /= b; }
};

vector<Mint> fact, invf;
void precompute(int n) {
    fact.assign(n + 1, 1); invf.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * Mint(i);
    invf[n] = fact[n].inv();
    for (int i = n - 1; i > 0; i--) invf[i] = invf[i + 1] * Mint(i + 1);
}

Mint nCk(int n, int k) { 
    if (k < 0 || k > n) return 0; 
    return fact[n] * invf[k] * invf[n - k]; 
}
Mint catalan(int n) { return nCk(2 * n, n) * Mint(n + 1).inv(); } // Valid parens, unrooted BSTs
Mint stars_bars(int n, int k) { return nCk(n + k - 1, k - 1); }   // x_1 + .. + x_k = n (x_i >= 0)
```

### 6. Matrix Exponentiation

```cpp
template<size_t N>
struct Matrix {
    long long m[N][N] = {0};
    void identity() { for (size_t i = 0; i < N; ++i) m[i][i] = 1; }
    Matrix operator*(const Matrix& b) const {
        Matrix res; // Cache-friendly loop order (i, k, j)
        for (size_t i = 0; i < N; ++i) for (size_t k = 0; k < N; ++k) for (size_t j = 0; j < N; ++j)
            res.m[i][j] = (res.m[i][j] + m[i][k] * b.m[k][j]) % MOD;
        return res;
    }
    Matrix pow(long long p) const {
        Matrix res, base = *this; res.identity();
        while (p > 0) { if (p & 1) res = res * base; base = base * base; p >>= 1; }
        return res;
    }
};
```

## Batch 4: Trees & Connectivity (Thursday)

### 1. Disjoint Set Union (DSU)

```cpp
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
```

### 2. LCA via Binary Lifting

```cpp
struct LCA {
    int n, l; vector<vector<int>> up, adj; vector<int> dep;
    LCA(int n) : n(n), l(ceil(log2(n))), up(n + 1, vector<int>(l + 1)), dep(n + 1), adj(n + 1) {}
    void dfs(int u, int p = 0, int d = 0) {
        up[u][0] = p; dep[u] = d; 
        for (int i = 1; i <= l; i++) up[u][i] = up[up[u][i - 1]][i - 1];
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
```

### 3. Tarjan's Bridges & Articulation Points

```cpp
int timer = 0;
vector<int> tin, low; vector<bool> is_art; vector<array<int,2>> bridges;

void dfs_bridges(int u, int p, const vector<vector<int>>& adj) {
    tin[u] = low[u] = timer++; int child = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (tin[v] != -1) {
            low[u] = min(low[u], tin[v]);
        } else { 
            dfs_bridges(v, u, adj); 
            low[u] = min(low[u], low[v]); 
            child++; 
            if (low[v] > tin[u]) bridges.push_back({u, v}); 
            if (low[v] >= tin[u] && p != -1) is_art[u] = 1; 
        }
    } 
    if (p == -1 && child > 1) is_art[u] = 1;
}
```

### 4. Euler Tour Technique (Tree Flattening)

```cpp
int timer = 0;
vector<int> tin, tout;
void euler_tour(int u, int p, const vector<vector<int>>& adj) {
    tin[u] = ++timer;
    for (int v : adj[u]) {
        if (v != p) euler_tour(v, u, adj);
    }
    tout[u] = timer; // Subtree of u is mapped to 1D range: [tin[u], tout[u]]
}
```

## Batch 5: Search, Bits & DP (Friday)

### 1. Generalized Backtracking Scaffold

```cpp
bool backtrack(int r, int c, vector<vector<int>>& grid, vector<vector<bool>>& vis) {
    if (/* is_goal */ false) return true; 
    
    vis[r][c] = true; // Choose
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i], nc = c + dc[i];
        if (/* is_valid */ false) {
            if (backtrack(nr, nc, grid, vis)) return true;
        }
    }
    
    vis[r][c] = false; // Un-choose (CRITICAL)
    return false;
}
```

### 2. Bitmask DP Scaffold (Assignments / TSP)

```cpp
void bitmask_dp(int n, vector<vector<int>>& cost) {
    vector<int> dp(1 << n, 1e9); 
    dp[0] = 0; 
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (dp[mask] == 1e9) continue; 
        int bits_active = __builtin_popcount(mask);
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) { 
                int next_mask = mask | (1 << i);
                dp[next_mask] = min(dp[next_mask], dp[mask] + cost[bits_active][i]);
            }
        }
    }
}
```

### 3. Digit DP

```cpp
string num; long long dp_dig[20][180][2];
long long digit_dp(int pos, int sum, bool flag) { // reset dp_dig to -1 before calling
    if (pos == num.size()) return sum;
    if (dp_dig[pos][sum][flag] != -1) return dp_dig[pos][sum][flag];
    long long res = 0; int lmt = flag ? 9 : num[pos] - '0';
    for (int i = 0; i <= lmt; i++) res += digit_dp(pos + 1, sum + i, flag || (i < lmt));
    return dp_dig[pos][sum][flag] = res;
}
```

### 4. Monotonic Deque (Sliding Window Max)

```cpp
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    deque<int> dq; vector<int> res;
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}
```

### 5. Tries (Standard & Bitwise 0-1)

```cpp
// Standard String Trie
struct Trie {
    vector<vector<int>> trie; vector<int> cnt; int num = 0;
    Trie(int max_nodes) : trie(max_nodes, vector<int>(26, 0)), cnt(max_nodes, 0) {}
    void insert(string s) { 
        int u = 0; 
        for (char c : s) { if (!trie[u][c - 'a']) trie[u][c - 'a'] = ++num; u = trie[u][c - 'a']; } 
        cnt[u]++; 
    }
};

// Bitwise 0-1 Trie (Maximum XOR queries)
struct BitTrie {
    vector<vector<int>> trie; int num;
    BitTrie(int max_el) : trie(max_el * 32, vector<int>(2, 0)), num(1) {}
    void insert(int x) {
        int u = 1;
        for (int i = 30; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (!trie[u][bit]) trie[u][bit] = ++num;
            u = trie[u][bit];
        }
    }
    int get_max_xor(int x) {
        int u = 1, ans = 0;
        for (int i = 30; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (trie[u][bit ^ 1]) { ans |= (1 << i); u = trie[u][bit ^ 1]; } 
            else if (trie[u][bit]) { u = trie[u][bit]; } 
            else break;
        } return ans;
    }
};
```

## Batch 6: The Heavyweights (Saturday)

### 1. Suffix Array

```cpp
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
            pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int,int> pre = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            nc[p[i]] = cur == pre ? nc[p[i - 1]] : nc[p[i - 1]] + 1;
        } 
        c = nc;
    } 
    return vector<int>(p.begin() + 1, p.end());
}
```

### 2. Heavy-Light Decomposition (HLD)

```cpp
struct HLD {
    int n, timer; vector<int> sz, top, dep, par, in, out; vector<vector<int>> adj;
    HLD(int n) : n(n), timer(0), sz(n, 1), top(n), dep(n), par(n), in(n), out(n), adj(n) {}
    void dfs_sz(int u = 0, int p = -1, int d = 0) {
        par[u] = p; dep[u] = d; sz[u] = 1; 
        if (adj[u].size() && adj[u][0] == p) swap(adj[u][0], adj[u].back());
        for (int& v : adj[u]) if (v != p) { 
            dfs_sz(v, u, d + 1); sz[u] += sz[v]; 
            if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]); 
        }
    }
    void dfs_hld(int u = 0, int p = -1, int t = 0) {
        in[u] = timer++; top[u] = t;
        for (int v : adj[u]) if (v != p) dfs_hld(v, u, v == adj[u][0] ? t : v);
        out[u] = timer;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) { 
            if (dep[top[u]] < dep[top[v]]) swap(u, v); 
            u = par[top[u]]; 
        }
        return dep[u] < dep[v] ? u : v;
    }
};
```

### 3. Meet in the Middle

```cpp
long long meet_in_the_middle(const vector<long long>& arr, long long target) {
    int n = arr.size(), m1 = n / 2, m2 = n - m1;
    auto get_sums = [&](int st, int len) {
        vector<long long> sums;
        for (int i = 0; i < (1 << len); i++) {
            long long cur = 0;
            for (int j = 0; j < len; j++) if (i & (1 << j)) cur += arr[st + j];
            sums.push_back(cur);
        }
        sort(sums.begin(), sums.end()); return sums;
    };
    auto sum1 = get_sums(0, m1), sum2 = get_sums(m1, m2);
    long long ans = 0;
    for (long long s1 : sum1) 
        ans += upper_bound(sum2.begin(), sum2.end(), target - s1) - 
               lower_bound(sum2.begin(), sum2.end(), target - s1);
    return ans;
}
```

## Batch 7: Systems & OOP (Sunday)

### 1. BigInt (Rule of Five & Memory Leaks Test)

```cpp
class BigInt {
    int* data; size_t sz, cap;
public:
    BigInt(size_t c = 16) : sz(0), cap(c), data(new int[c]()) {}
    ~BigInt() { delete[] data; } // Destructor
    
    // Copy Constructor & Assignment
    BigInt(const BigInt& o) : sz(o.sz), cap(o.cap) {
        data = new int[cap]();
        for (size_t i = 0; i < sz; ++i) data[i] = o.data[i];
    }
    BigInt& operator=(const BigInt& o) { 
        if (this != &o) {
            delete[] data;
            sz = o.sz; cap = o.cap;
            data = new int[cap]();
            for (size_t i = 0; i < sz; ++i) data[i] = o.data[i];
        }
        return *this; 
    }
    
    // Move Constructor & Assignment
    BigInt(BigInt&& o) noexcept : data(o.data), sz(o.sz), cap(o.cap) {
        o.data = nullptr; o.sz = o.cap = 0;
    }
    BigInt& operator=(BigInt&& o) noexcept {
        if (this != &o) {
            delete[] data; data = o.data; sz = o.sz; cap = o.cap;
            o.data = nullptr; o.sz = o.cap = 0;
        } 
        return *this;
    }
};
```

### 2. CRTP & Cache Line Alignment (Low Latency)

```cpp
// Static Polymorphism (Zero VTable overhead)
template <typename Derived>
struct MatchingEngine {
    void process() { 
        static_cast<Derived*>(this)->execute(); 
    }
};

struct CryptoEngine : public MatchingEngine<CryptoEngine> {
    void execute() { /* Fast path */ }
};

// False-sharing prevention for multi-threading
struct alignas(64) OrderBookCounter {
    uint64_t fills;
};
```

## 🏛️ The Reading/Memory Vault (Visual Inspection Only)

*Do NOT blind-type these daily. Read them during meals or buffer time to understand the state transitions and mathematical logic. These are your "break-glass" algorithms for extreme Edge Cases.*

### 1. Eulerian Path (Hierholzer's Algorithm)

```cpp
// Hierholzer's Algorithm (Directed Graph)
vector<int> find_eulerian_path(int n, vector<vector<int>>& adj) {
    vector<int> path, out(n), in(n);
    for (int u = 0; u < n; u++) { out[u] = adj[u].size(); for (int v : adj[u]) in[v]++; }
    int start = 0, end = 0, start_node = 0;
    for (int i = 0; i < n; i++) {
        if (out[i] - in[i] == 1) { start++; start_node = i; }
        else if (in[i] - out[i] == 1) end++;
        else if (in[i] != out[i]) return {}; // Impossible
    }
    if (!(start == 0 && end == 0) && !(start == 1 && end == 1)) return {};
    
    stack<int> st; st.push(start_node);
    while (!st.empty()) {
        int u = st.top();
        if (out[u] == 0) { path.push_back(u); st.pop(); }
        else { int v = adj[u][--out[u]]; st.push(v); }
    }
    reverse(path.begin(), path.end()); return path;
}
```

### 2. K-th Order Statistic (QuickSelect)

*Expected* $O(N)$ *to find median or K-th smallest without full sort.*

```cpp
int partition(vector<int>& arr, int l, int r) {
    int pivot = arr[r], i = l;
    for (int j = l; j < r; j++) if (arr[j] <= pivot) swap(arr[i++], arr[j]);
    swap(arr[i], arr[r]); return i;
}
int quickSelect(vector<int>& arr, int l, int r, int k) {
    if (l <= r) {
        int p = partition(arr, l, r);
        if (p == k) return arr[p];
        if (p < k) return quickSelect(arr, p + 1, r, k);
        return quickSelect(arr, l, p - 1, k);
    }
    return -1;
} // Call: quickSelect(arr, 0, n - 1, k - 1);
```

### 3. Closest Pair of Points (Divide & Conquer)

$O(N \log N)$ *algorithm heavily tested in computational geometry rounds.*

```cpp
struct pt { double x, y; };
double closest_pair(vector<pt>& p) {
    sort(p.begin(), p.end(), [](pt a, pt b) { return a.x < b.x; });
    set<pair<double, double>> s; double d = 1e9; int l = 0;
    for (int i = 0; i < p.size(); i++) {
        while (l < i && p[i].x - p[l].x >= d) { s.erase({p[l].y, p[l].x}); l++; }
        auto it_low = s.lower_bound({p[i].y - d, p[i].x - d});
        for (auto it = it_low; it != s.end() && it->first - p[i].y <= d; it++) {
            d = min(d, hypot(p[i].x - it->second, p[i].y - it->first));
        }
        s.insert({p[i].y, p[i].x});
    } return d;
}
```

### 4. Bellman-Ford & Floyd-Warshall

*Bellman-Ford: Negative Cycles. Floyd-Warshall: All-Pairs Shortest Path.*

```cpp
// Bellman-Ford O(VE)
bool bellman_ford(int s, int n, vector<ll>& dist, vector<array<ll, 3>>& edges) {
    dist.assign(n, 1e18); dist[s] = 0; bool cycle = false;
    for (int i = 0; i < n; i++) {
        cycle = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] != 1e18 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; cycle = true;
            }
        }
    } return cycle; // True if negative cycle exists
}

// Floyd-Warshall O(V^3)
void floyd_warshall(int n, vector<vector<ll>>& dist) {
    for (int k = 0; k < n; k++) 
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++)
                if (dist[i][k] != 1e18 && dist[k][j] != 1e18) 
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
```

### 5. Sum Over Subsets (SOS) DP & Variants

*Evaluates subset sums over a boolean hypercube in* $O(N 2^N)$*. Signature DE Shaw / Google problem type.*

```cpp
void sos_dp(int max_bits, vector<int>& a) {
    vector<int> dp(1 << max_bits, 0); 
    for (int x : a) dp[x]++;
    
    for (int i = 0; i < max_bits; i++) {
        for (int mask = 0; mask < (1 << max_bits); mask++) {
            // BASE: SUBSET SUM
            // Accumulates sum of all subsets of the current mask
            if (mask & (1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
            
            // -----------------------------------------------------
            // VARIANT 1: SUPERSET SUM
            // Finds sum of all masks that strictly contain the current mask.
            // Replace the 'if' condition with:
            // if (!(mask & (1 << i))) dp[mask] += dp[mask ^ (1 << i)];
            
            // -----------------------------------------------------
            // VARIANT 2: INCLUSION-EXCLUSION (MOBIUS INVERSION)
            // Reverts SOS DP back to original array frequencies.
            // Replace '+=' with '-=':
            // if (mask & (1 << i)) dp[mask] -= dp[mask ^ (1 << i)];
            
            // -----------------------------------------------------
            // VARIANT 3: XOR CONVOLUTION (Fast Walsh-Hadamard Transform - FWHT)
            // Used to find XOR pairs or count pairs x^y = K.
            // Replace the inside loop logic completely:
            // int u = dp[mask ^ (1 << i)], v = dp[mask];
            // dp[mask ^ (1 << i)] = u + v; 
            // dp[mask] = u - v;
        }
    }
}
```

### 6. Gaussian Elimination (Linear Systems & Expected Value)

*Solves Absorbing Markov Chains ($N = (I - Q)^{-1}$) and EV problems where states transition backwards.*

```cpp
// Gaussian Elimination O(N^3)
// Returns: 1 (Unique solution), 0 (No solution), INF (Infinite solutions)
int gauss(vector<vector<double>>& a, vector<double>& ans) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i) if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
        if (abs(a[sel][col]) < 1e-9) continue;
        swap(a[sel], a[row]); where[col] = row;
        for (int i = 0; i < n; ++i) if (i != row) {
            double c = a[i][col] / a[row][col];
            for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
        }
        ++row;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i = 0; i < n; ++i) {
        double sum = 0; for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > 1e-9) return 0;
    }
    for (int i = 0; i < m; ++i) if (where[i] == -1) return 1e9;
    return 1; 
}
```

### 7. Advanced DP Optimizations (Li-Chao & D&C)

*Li-Chao minimizes* $kx+b$*. D&C optimizes quadrangle inequality DP transitions.*

```cpp
// Li-Chao Tree (Convex Hull Trick Alternative) O(log X)
struct LiChao {
    struct Line { ll m, c; ll operator()(ll x) { return m * x + c; } };
    struct Node { Line seg; Node *l, *r; Node(Line s): seg(s), l(0), r(0) {} };
    Node* root; int N;
    LiChao(int n): N(n) { root = new Node({0, (ll)1e18}); }
    void upd(Node*& n, int l, int r, Line y) {
        if (!n) { n = new Node(y); return; }
        int m = (l + r) / 2; bool b1 = y(l) < n->seg(l), b2 = y(m) < n->seg(m);
        if (b2) swap(n->seg, y);
        if (l + 1 == r) return;
        if (b1 != b2) upd(n->l, l, m, y); else upd(n->r, m, r, y);
    }
};

// Divide & Conquer DP
// Optimizes DP from O(K N^2) to O(K N log N)
void dac_opt(int i, int l, int r, int ql, int qr, vector<vector<int>>& dp) {
    if (l > r) return;
    int mid = (l + r) / 2; array<int,2> bst = {1e9, -1};
    for (int k = ql; k <= min(mid, qr); k++) 
        bst = min(bst, {dp[i - 1][k - 1] + cost(k, mid), k});
    dp[i][mid] = bst[0];
    dac_opt(i, l, mid - 1, ql, bst[1], dp); 
    dac_opt(i, mid + 1, r, bst[1], qr, dp);
}
```

### 8. Suffix Automaton (SAM) & Aho-Corasick

*Aho-Corasick for multi-pattern matching. SAM for* $O(N)$ *DAWG construction.*

```cpp
// Aho-Corasick Add and Link
void add(string s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) { t[v].next[c] = t.size(); t.emplace_back(v, ch); }
        v = t[v].next[c];
    }
    t[v].out = true;
}
int get_link(int v) {
    if (t[v].link == -1) t[v].link = (v == 0 || t[v].p == 0) ? 0 : go(get_link(t[v].p), t[v].pch);
    return t[v].link;
}

// Suffix Automaton properties logic
// States represent equivalence classes grouped by endpos. 
// len[v] is max length in state. link[v] points to longest suffix in different class.
// len(link(v)) = minlen(v) - 1.