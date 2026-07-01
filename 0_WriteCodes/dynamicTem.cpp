#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar array
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

// === BASIC DP (KADANE, LIS, LCS) ===
// 1D Maximum Subarray Sum (Kadane's Algorithm) in O(N)
ll kadane_1d(vector<ll>& a) { ll ans = -LINF, cur = -LINF; for (ll x : a) { cur = max(x, cur + x); ans = max(ans, cur); } return ans; }
// 2D Maximum Subarray Sum in O(N^3)
ll kadane_2d(vector<vector<ll>>& a) {
    int n = a.size() - 1; ll ans = -LINF;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) a[i][j] += a[i][j - 1];
    for (int l = 1; l <= n; l++) for (int r = l; r <= n; r++) {
        ll cur = 0; for (int i = 1; i <= n; i++) { ll x = a[i][r] - a[i][l - 1]; cur = max(x, cur + x); ans = max(ans, cur); }
    } return ans;
}
// Longest Increasing Subsequence (LIS) in O(N log N)
int lis(vector<int>& a) { vector<int> dp; for (int x : a) { auto it = lower_bound(dp.begin(), dp.end(), x); if (it == dp.end()) dp.push_back(x); else *it = x; } return dp.size(); }
// Longest Common Subsequence (LCS) in O(NM)
int lcs(string& x, string& y) {
    int n = x.size(), m = y.size(); vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) dp[i][j] = (x[i - 1] == y[j - 1]) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][m];
}

// === KNAPSACK & COIN CHANGE ===
// 0-1 Knapsack: Max value for given weight capacity in O(NW)
int knapsack(int w, vector<int>& wt, vector<int>& val) {
    vector<int> dp(w + 1, 0);
    for (size_t i = 0; i < wt.size(); i++) for (int j = w; j >= wt[i]; j--) dp[j] = max(dp[j], dp[j - wt[i]] + val[i]);
    return dp[w];
}
// Coin Change: Combinations, Ordered Permutations, and Minimum Coins in O(NX)
void coin_change(int x, vector<int>& c) {
    vector<int> ways(x + 1, 0), perm(x + 1, 0), min_c(x + 1, INF); ways[0] = perm[0] = 1; min_c[0] = 0;
    for (int i = 1; i <= x; i++) for (int j : c) if (i - j >= 0) ways[i] = (ways[i] + ways[i - j]) % MOD; // Combinations
    for (int j : c) for (int i = 1; i <= x; i++) if (i - j >= 0) perm[i] = (perm[i] + perm[i - j]) % MOD; // Ordered ways
    for (int i = 1; i <= x; i++) for (int j : c) if (i - j >= 0) min_c[i] = min(min_c[i], min_c[i - j] + 1); // Min coins
}

// === INTERVAL & SCHEDULING DP ===
// Maximum profit from non-overlapping intervals (Weighted Job Scheduling) in O(N log N)
ll job_scheduling(vector<ar<ll,3>>& jobs) { // {end, start, profit}
    sort(jobs.begin(), jobs.end()); int n = jobs.size(); vector<ll> dp(n, 0); dp[0] = jobs[0][2];
    for (int i = 1; i < n; i++) {
        int k = lower_bound(jobs.begin(), jobs.begin() + i, ar<ll,3>{jobs[i][1], 0, 0}) - jobs.begin() - 1;
        dp[i] = max(dp[i - 1], (k >= 0 ? dp[k] : 0) + jobs[i][2]);
    } return dp[n - 1];
}

// === RANGE DP (MCM VARIANTS) ===
// Cutting Sticks with Knuth Optimization from O(N^3) to O(N^2)
int cutting_sticks_knuth(int n, vector<int>& a) { // a includes 0 and length X
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, INF)), opt(n + 2, vector<int>(n + 2, 0));
    for (int i = 0; i <= n; i++) dp[i][i + 1] = 0, opt[i][i + 1] = i;
    for (int l = 2; l <= n + 1; l++) for (int i = 0, j = l; j <= n + 1; i++, j++) {
        for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) 
            if (dp[i][j] > dp[i][k] + dp[k][j] + a[j] - a[i]) dp[i][j] = dp[i][k] + dp[k][j] + a[j] - a[i], opt[i][j] = k;
    } return dp[0][n + 1];
}
// Mixtures (Range DP Variant for combining adjacents) in O(N^3)
int mixtures(vector<int>& a) {
    int n = a.size(); vector<vector<int>> dp(n, vector<int>(n, INF)), sum(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) sum[i][i] = a[i], dp[i][i] = 0;
    for (int l = 1; l < n; l++) for (int i = 0, j = l; j < n; i++, j++) {
        for (int k = i; k < j; k++) if (dp[i][j] > dp[i][k] + dp[k + 1][j] + sum[i][k] * sum[k + 1][j])
            dp[i][j] = dp[i][k] + dp[k + 1][j] + sum[i][k] * sum[k + 1][j], sum[i][j] = (sum[i][k] + sum[k + 1][j]) % 100;
    } return dp[0][n - 1];
}

// === BITMASK DP ===
// Elevator Rides: Minimum rides to carry everyone without exceeding weight limit in O(N 2^N)
int elevator_rides(int limit, vector<int>& w) {
    int n = w.size(); vector<ar<int,2>> dp(1 << n, {n + 1, 0}); dp[0] = {0, 0};
    for (int i = 1; i < (1 << n); i++) for (int j = 0; j < n; j++) if (i & (1 << j)) {
        auto cur = dp[i ^ (1 << j)];
        if (cur[1] + w[j] <= limit) cur[1] += w[j]; else cur[0]++, cur[1] = w[j];
        dp[i] = min(dp[i], cur);
    } return dp[(1 << n) - 1][0] + (dp[(1 << n) - 1][1] > 0);
}
// TSP / Hamiltonian Tour: Minimum weight Hamiltonian cycle in O(N^2 2^N)
int tsp(int n, vector<vector<int>>& adj) {
    vector<vector<int>> dp(1 << n, vector<int>(n, INF)); dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) for (int u = 0; u < n; u++) if (mask & (1 << u))
        for (int v = 0; v < n; v++) if (!(mask & (1 << v))) dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + adj[u][v]);
    int ans = INF; for (int i = 1; i < n; i++) ans = min(ans, dp[(1 << n) - 1][i] + adj[i][0]); return ans;
}

// === DIGIT DP ===
// Sum of digits between A and B in O(L * 10 * 2) where L is digits length
string num; ll dp_dig[20][180][2];
ll digit_dp(int pos, int sum, bool flag) { // reset dp_dig to -1 before calling
    if (pos == num.size()) return sum;
    if (dp_dig[pos][sum][flag] != -1) return dp_dig[pos][sum][flag];
    ll res = 0; int lmt = flag ? 9 : num[pos] - '0';
    for (int i = 0; i <= lmt; i++) res += digit_dp(pos + 1, sum + i, flag || (i < lmt));
    return dp_dig[pos][sum][flag] = res;
}

// === SUM OVER SUBSETS (SOS) DP ===
// Evaluates subset sum over boolean hypercube in O(N 2^N)
void sos_dp(int max_bits, vector<int>& a) {
    vector<int> dp(1 << max_bits, 0); for (int x : a) dp[x]++;
    for (int i = 0; i < max_bits; i++) for (int mask = 0; mask < (1 << max_bits); mask++) 
        if (mask & (1 << i)) dp[mask] += dp[mask ^ (1 << i)];
}

// === DP OPTIMIZATIONS ===
// Li-Chao Segment Tree: Convex Hull Trick Alternative (Min queries, generic X) in O(log(MAX_X))
struct LiChao {
    struct Line { ll m, c; ll operator()(ll x) { return m * x + c; } };
    struct Node { Line seg; Node *l, *r; Node(Line s): seg(s), l(0), r(0) {} };
    Node* root; int N;
    LiChao(int n): N(n) { root = new Node({0, LINF}); } // 0 slope, inf intercept initially
    void upd(Node*& n, int l, int r, Line y) {
        if (!n) { n = new Node(y); return; }
        int m = (l + r) / 2; bool b1 = y(l) < n->seg(l), b2 = y(m) < n->seg(m);
        if (b2) swap(n->seg, y);
        if (l + 1 == r) return;
        if (b1 != b2) upd(n->l, l, m, y); else upd(n->r, m, r, y);
    }
    ll qry(Node* n, int l, int r, ll x) {
        if (!n) return LINF; if (l + 1 == r) return n->seg(x);
        int m = (l + r) / 2; return min(n->seg(x), x < m ? qry(n->l, l, m, x) : qry(n->r, m, r, x));
    }
};

// Divide & Conquer DP Optimization: Optimizes DP from O(K N^2) to O(K N log N) when cost(i, j) satisfies quadrangle inequality
int cost(int i, int j) { return 0; } // Define cost function separately
void dac_opt(int i, int l, int r, int ql, int qr, vector<vector<int>>& dp) {
    if (l > r) return;
    int mid = (l + r) / 2; ar<int,2> bst = {INF, -1};
    for (int k = ql; k <= min(mid, qr); k++) bst = min(bst, {dp[i - 1][k - 1] + cost(k, mid), k});
    dp[i][mid] = bst[0];
    dac_opt(i, l, mid - 1, ql, bst[1], dp); dac_opt(i, mid + 1, r, bst[1], qr, dp);
}

// Deque Optimization (Sliding Window Min/Max): Optimizes DP transition from O(NK^2) to O(NK)
ll deque_trick(int n, int k, int limit, vector<int>& a) { // Ex: Select X items, dist between items <= K
    vector<vector<ll>> dp(n + 1, vector<ll>(limit + 1, -LINF)); dp[0][0] = 0;
    for (int j = 1; j <= limit; j++) {
        deque<ar<ll,2>> dq; dq.push_back({j - 1, dp[j - 1][j - 1]});
        for (int i = j; i <= n; i++) {
            while (dq.size() && dq.front()[0] < i - k) dq.pop_front();
            if (dq.size()) dp[i][j] = dq.front()[1] + a[i];
            while (dq.size() && dp[i][j - 1] >= dq.back()[1]) dq.pop_back();
            dq.push_back({i, dp[i][j - 1]});
        }
    } return dp[n][limit];
}

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