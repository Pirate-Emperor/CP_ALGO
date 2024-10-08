// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long

const int MAXN = 3e6 + 5; 
const int MAX_N = 16;
const int MOD = 1e9 + 7;
const int INF = 1e9;
// const ll INF = 1e18;

int N, adj[MAX_N][MAX_N];
ll dp[1 << MAX_N][MAX_N];


void sol()
{
    
    ll a,b,c,n,m,k=-1,x,resu=0;
    cin >> n >> m;
    vector<vector<ll>> grid(n+1,vector<ll>(m+1,0));
    ll col=0;
    ll row=0;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            cin >> grid[i][j];
            grid[n][j]^=grid[i][j];
            grid[i][m]^=grid[i][j];
            grid[n][m]^=grid[i][j];
        }
    }
    resu = INF;
    int fullmask_n = (1 << (n+1)) - 1;
    int fullmask_m = (1 << (m+1)) - 1;
    vector<vector<ll>> fr(n+1,vector<ll>(m+1,INF)),fc(n+1,vector<ll>(m+1,INF));
    for (int i=0;i<=m;i++)
    {
        for (int ti=0;ti<=n;ti++)
        {
            for (int tj=0;tj<=n;tj++)
            {
                adj[ti][tj]=0;
                for (int k=0;k<=m;k++)
                {
                    if (i==k) continue;
                    adj[ti][tj]+=abs(grid[ti][k]-grid[tj][k]);
                }
            }
        } 
        N=n+1;
        memset(dp, INF, sizeof dp);
        for (int it=0;it<=n;it++)
        {
            for (int jt=0;jt<(1<<N);jt++)
            {
                dp[jt][it]=INF;
            }
            dp[1<<it][it]=0;
        }
        for (int mask=0;mask<(1<<N);mask++)
        {
            for (int u=0;u<=n;u++)
            {
                if (~mask >> u & 1) continue;
                if (__builtin_popcount(mask) == n) continue;

                for (ll v = 0; v < N; v++) {
                    if (!(mask & (1 << v))) { // this node is unvisited
                        ll new_mask = mask | (1 << v);
                        dp[new_mask][v] = min(dp[new_mask][v], (ll)adj[u][v] + dp[mask][u]);
                    }
                }
            }
        }
        
        // pair<int,int> tem = tsp(1,0);
        for (int mi=0;mi<=n;mi++)
        {
            ll mask = ((1<<(n+1))-1) ^ (1<<mi);
            for (int u=0;u<=n;u++)
            {
                fr[mi][i]=min(fr[mi][i],(ll)dp[mask][u]);
            }
        }
    }
    for (int i=0;i<=n;i++)
    {
        for (int ti=0;ti<=m;ti++)
        {
            for (int tj=0;tj<=m;tj++)
            {
                adj[ti][tj]=0;
                for (int k=0;k<=n;k++)
                {
                    if (i==k) continue;
                    adj[ti][tj]+=abs(grid[k][ti]-grid[k][tj]);
                }
            }
        } 
        N=m+1;
        memset(dp, INF, sizeof dp);
        for (int it=0;it<=m;it++)
        {
            for (int jt=0;jt<(1<<N);jt++)
            {
                dp[jt][it]=INF;
            }
            // fill(dp[i], dp[i] + fullmask_n, INF);
            dp[1<<it][it]=0;
        }
        
        for (int mask=0;mask<(1<<N);mask++)
        {
            for (int u=0;u<=m;u++)
            {
                if (~mask >> u & 1) continue;
                if (__builtin_popcount(mask) == m) continue;

                for (ll v = 0; v < N; v++) {
                    if (!(mask & (1 << v))) { // this node is unvisited
                        ll new_mask = mask | (1 << v);
                        dp[new_mask][v] = min(dp[new_mask][v], (ll)adj[u][v] + dp[mask][u]);
                    }
                }
            }
        }

        for (int mi=0;mi<=m;mi++)
        {
            ll mask = ((1<<(m+1))-1) ^ (1<<mi);
            for (int u=0;u<=m;u++)
            {
                fc[i][mi]=min(fc[i][mi],(ll)dp[mask][u]);
            }
        }
    }
    resu=INF;
    for (int i=0;i<=n;i++)
    {
        for (int j=0;j<=m;j++)
        {
            // cout << fr[i][j]+fc[i][j] << " ";
            resu=min(resu,fr[i][j]+fc[i][j]);
        }
        // cout << endl;
    }
    cout << resu << endl;
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