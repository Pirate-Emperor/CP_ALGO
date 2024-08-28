// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long

const int MAXN = 3e6 + 5; 
const int MAX_N = 2e5 + 5;
ll MOD = 1000000007;
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

ll mex(vector<ll> const& A, int N) {
    set<int> b(A.begin(), A.begin() + N);

    ll result = 0;
    while (b.count(result))
        ++result;
    return result;
}


map<ll, ll> vis;
map<ll,vector<ll>> adj;

void dfs(int u) {
    vis[u] = u;
    if (adj.find(u)==adj.end()) return;
    ll res=u;
    for (ll v : adj[u]) {
        if (vis[v]) 
        {
            res=max(res,vis[v]);
            continue;
        }
        dfs(v);
        res=max(res,vis[v]);
    }
    vis[u] = res;
}

void sol()
{
    
    ll a,b,c,n,m,k=-1,x,resu=0;
    cin >> n >> m;
    vector<ll> temp(MAX_N+1);
    map<ll,ll> val;
    for (int i=0;i<n;i++)
    {
        cin >> a;
        for (int j=0;j<a;j++)
        {
            cin >> temp[j];
        }
        b = mex(temp,a);
        temp[a]=b;
        c = mex(temp,a+1);
        adj[b].push_back(c);
        val[b]++;
        // cout << b << " " << c << " | ";
    }    
    resu = m*(m+1)/2;
    for (auto it: val)
    {
        if (vis[it.first]) continue;
        dfs(it.first); 
    }
    vector<pair<ll,ll>> mpi;
    for (auto it: vis)
    {
        mpi.push_back(make_pair(it.second,it.first));
    }
    sort(mpi.begin(),mpi.end());
    int st=0;
    ll mas=0;
    for (int i=0;i<=min((ll)2e5+5,m);i++)
    {
        if (vis.find(i)!=vis.end())
        {
            mas = max(mas,vis[i]);
        }
        // while (mpi[st].first<=i)
        // {
        //     st++;
        // }
        // if (mpi[st].second>=i) continue;
        cout << mas << " ";
        resu+=max(mas,(ll)i)-i;

    }
    // for (auto it: val)
    // {
    //     // cout << it.first << " " << it.second << " | ";
    //     resu+=it.second*(vis[it.first]-it.first);
    //     // resu+=max(it.second,it.first)-it.first;
    // }
    cout << resu << endl;
    adj.clear();
    vis.clear();
    return;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    // precompute(100);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}