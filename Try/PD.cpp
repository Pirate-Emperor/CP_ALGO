// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

int n, m, x;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
int res=0;
void recur(int u, int dep)
{
    vis[u]=1;
    for (int it: adj[u])
    {
        if (vis[it]==0) 
        {
            par[it]=u;
            recur(it, dep+1);
        }
    }
    dis[u]=dep;
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    edges.clear();
    vis.clear();
    dis.clear();
    par.clear();
    for (int i=0;i<n;i++) 
    {
        adj[i].clear();
    }
    vis.push_back(0);
    dis.push_back(-1);
    par.push_back(-1);
    for (int i=0;i<n-1;i++)
    {
        vis.push_back(0);
        dis.push_back(-1);
        par.push_back(-1);
        cin >> l >> r;
        l--;
        r--;
        adj[l].push_back(r);
        adj[r].push_back(l);
    }
    recur(0,0);
    priority_queue<array<ll,2>,vector<array<ll,2>>,greater<array<ll,2>>> odd,eve;
    for (int i=0;i<n;i++)
    {
        if (adj[i].size()==1)
        {
            ll val=0;
            if (i==0) val+=n;
            if (i==n-1) continue;
            if (dis[i]%2==0) eve.push({val+i,i});
            else odd.push({val+i,i});
        }
    }
    vector<array<ll,2>> ans;
    ll res=0;
    int it=0;
    while(!odd.empty() || !eve.empty())
    {
        if (it%2==0)
        {
            if (!odd.empty()) 
            {
                auto tem = odd.top();
                odd.pop();
                adj[par[tem[1]]].pop_back();
                if (adj[par[tem[1]]].size()==1) 
                {
                    int i = par[tem[1]];
                    ll val=0;
                    if (i==0) val+=n;
                    if (i==n-1) continue;
                    if (dis[i]%2==0) eve.push({val+i,i});
                    else odd.push({val+i,i});
                }
                ans.push_back({2,tem[1]});
                ans.push_back({1,-1});
                res++;
            }
            else ans.push_back({1,-1});
        }
        else
        {
            if (!eve.empty()) 
            {
                auto tem = eve.top();
                eve.pop();
                adj[par[tem[1]]].pop_back();
                if (adj[par[tem[1]]].size()==1) 
                {
                    int i = par[tem[1]];
                    ll val=0;
                    if (i==0) val+=n;
                    if (i==n-1) continue;
                    if (dis[i]%2==0) eve.push({val+i,i});
                    else odd.push({val+i,i});
                }
                ans.push_back({2,tem[1]});
                ans.push_back({1,-1});
                res++;
            }
            else ans.push_back({1,-1});
        }
        it++;
        res++;
    }
    cout << ans.size() << endl;
    for (int i=0;i<ans.size();i++)
    {
        if (ans[i][0]==1) cout << 1 << endl;
        else cout << ans[i][0] << " " << ans[i][1]+1 << endl;
    }
    cout << endl;
    return;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}