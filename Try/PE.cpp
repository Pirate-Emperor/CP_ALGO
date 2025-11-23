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
    vector<ll> arr(n), brr(m);
    ll ni=-1;
    ll mi=-1;
    map<ll,vector<ll>> tempi,tempj;
    bool ch=false;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        if (arr[i]>a){
            a=arr[i];
            ni=i;
        }
        tempi[arr[i]].push_back(i);
        if (tempi[arr[i]].size()>1) ch=true;
    }
    bool ch1=false;
    for (int i=0;i<m;i++)
    {
        cin >> brr[i];
        if (brr[i]>b){
            b=brr[i];
            mi=i;
        }
        tempj[brr[i]].push_back(i);
        if (tempj[brr[i]].size()>1) ch1=true;
    }
    if (a!=b || ch || ch1) {
        cout << "No\n";
        return;
    }
    vector<vector<ll>> grid(n,vector<ll>(m,0));
    map<ll,ll> vis;
    for (int i=0;i<n;i++){
        if (tempj[arr[i]].size()==1) grid[i][tempj[arr[i]][0]]=arr[i];
        else grid[i][mi]=arr[i];
        vis[arr[i]]=1;
    }
    for (int i=0;i<m;i++){
        if (tempi[brr[i]].size()==1) grid[tempi[brr[i]][0]][i]=brr[i];
        else grid[ni][i]=brr[i];
        vis[brr[i]]=1;
    }
    map<array<ll,3>,ll,greater<array<ll,3>>> mpi;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            if (grid[i][j]==0){
                ll t1 = min(arr[i],brr[j]);
                mpi[{t1,i,j}]=1;
            }
        }
    }
    ll prev=a;
    for (auto it: mpi){
        if (a>it.first[0]) a=it.first[0]-1;
        while(vis[a]==1) a--;
        if (a<=0) {
            cout << "No\n";
            return;
        }
        grid[it.first[1]][it.first[2]]=a;
        vis[a]=1;
        a--;
    }
    cout << "Yes\n";
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
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