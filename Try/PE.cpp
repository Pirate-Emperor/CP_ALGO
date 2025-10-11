// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e5 + 5;
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

vector<int> briarr;
void briCnt(int v)
{
    briarr.push_back(v);
}
int n;
vector<int> adj[MAX_N];

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                briCnt(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        briCnt(v);
}

void find_art() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i);
    }
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    ll v=0,m=0,x=0;
    cin >> n >> m;
    vector<string> grid(n),bgrid(3*n);
    for (int i=0;i<n;i++)
    {
        cin >> grid[i];
    }
    string st="";
    for (int i=0;i<m;i++) st+=".";
    for (int i=0;i<n;i++) bgrid[i]=st+st+st;
    for (int i=n;i<2*n;i++) bgrid[i]=st+grid[i-n]+st;
    for (int i=2*n;i<3*n;i++) bgrid[i]=st+st+st;
    vector<array<int,2>> adj[100];
    for (int i=n;i<3*n;i++)
    {
        for (int j=m;j<3*m;j++)
        {
            if (bgrid[i][j]=='T') {
                a=i;
                b=j;
                break;
            }
        }
    }
    priority_queue<array<int,5>,vector<array<int,5>>,greater<array<int,5>>> pq;
    pq.push({0,a,b,n,m});
    int res=INF;
    while(!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        int x=it[1];
        int y=it[2];
        bgrid[x][y]='x';
        bool check=true;
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<m;j++)
            {
                if (bgrid[it[3]+i][it[4]+j]=='#') check=false;
            }
        }
        if (check) 
        {
            // cout << it[1] << " " << it[2] << " " << it[3] << " " << it[4] << " ";
            res=min(res,it[0]);
            break;
        }
        if (it[3]-1>=0 && bgrid[x-1][y]=='.') 
        {
            pq.push({it[0]+1,x-1,y,it[3]-1,it[4]});
        }
        if (it[3]+n<3*n && bgrid[x+1][y]=='.') 
        {
            pq.push({it[0]+1,x+1,y,it[3]+1,it[4]});
        }
        if (it[4]-1>=0 && bgrid[x][y-1]=='.') 
        {
            pq.push({it[0]+1,x,y-1,it[3],it[4]-1});
        }
        if (it[4]+m<3*m && bgrid[x][y+1]=='.') 
        {
            pq.push({it[0]+1,x,y+1,it[3],it[4]+1});
        }
    }
    if (res==INF) cout << -1 << endl;
    else cout << res << endl;
    return;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
        
    }
}