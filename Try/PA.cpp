// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ari array
#define ll long long
#define int long long

const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

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
vector<int> adj[MAX_N];
int vis[MAX_N];

void solve() {
    ll n=0,m=0,l=0,r=0,k=0;
    ll w=0,x=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0;
    cin >> n;
    vector<map<int,int>> adj(n);
    for (int i=1;i<n;i++)
    {
        cin >> x >> y;
        x--;
        y--;
        adj[x][y]=1;
        adj[y][x]=1;
    }    
    vector<int> temp;
    vector<int> up(n);
    for (int i=0;i<n;i++)
    {
        if (adj[i].size()==1) 
        {
            temp.push_back(i);
            up[i]=adj[i].begin()->first;
        }
    }
    int id=0;
    vector<ar<int,2>> cnt(n,{0,0});
    while(!temp.empty())
    {
        vector<int> temp2;
        for (int u:temp)
        {
            vis[u]=1;
            cnt[up[u]][id]++;
            adj[up[u]].erase(u);
        }
        for (int u:temp)
        {
            if (vis[up[u]]==0) temp2.push_back(up[u]);
            vis[up[u]]=1;
            if (adj[up[u]].size()==1) up[up[u]]=adj[up[u]].begin()->first;
        }
        temp = temp2;
        id=1-id;
    }

    
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