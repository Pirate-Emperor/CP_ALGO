// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;


mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

const int MAXN = 3e6 + 5; 
const int MAX_N = 405;
ll MOD = 998244353;
const ll MOD2 = 1073676287;
const ll MOD3 = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

vector<ll> fact, invf;

void precompute(int n) {
    fact.assign(n + 1, 1); 
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    invf.assign(n + 1, 1);
    invf[n] = qexp(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i > 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
}

ll nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invf[k] % MOD * invf[n - k] % MOD;
    // return fact[n] * qexp(fact[k], MOD - 2, MOD) % MOD * qexp(fact[n - k], MOD - 2, MOD) % MOD;
}

int read() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int ret = 0;
	while (c >= '0' && c <= '9') ret = ret*10 + (c - '0'), c = getchar();
	return ret;
}

int n, m, p;
ll dist[MAX_N][MAX_N];

void floyd_warshall() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], max(dist[i][k] , dist[k][j]));
}
 
void sol() {
    cin >> n >> m >> p;
    vector<ll> parr(p);
    for (int i=0;i<p;i++)
    {
        cin >> parr[i];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = (i == j) ? 0 : LINF;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = dist[v][u] = min(dist[u][v], (ll)w); 
    }
    floyd_warshall();
    ll resu=LINF;
    vector<ll> dp(p+1,LINF);
    vector<ll> ans;
    // for (int i=1;i<=n;i++)
    // {
    //     for (int j=1;j<=n;j++)
    //     {
    //         cout << dist[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for (int i=0;i<n;i++)
    {
        vector<ll> t1dp(p+1,LINF);
        ll rest = LINF;
        for (int j=1;j<=n;j++)
        {
            ll res=0;
            vector<ll> tdp(p+1,LINF);
            for (int k=0;k<p;k++)
            {
                tdp[k] = min(dp[k],max(dist[j][parr[k]],dist[parr[k]][j]));
                res+=tdp[k];
            }
            // cout << res << " "; 
            if (res<=rest) 
            {
                rest=res;
                t1dp = tdp;
            }
        }
        if (rest<=resu)
        {
            resu=rest;
            dp=t1dp;
        }
        ans.push_back(resu);
    }
    for (int i=0;i<n;i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
}


int main() {

    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    
    // precompute(2e5+10);
    // TxtIO;
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}