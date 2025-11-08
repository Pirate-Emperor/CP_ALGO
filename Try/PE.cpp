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
    vector<string> arr(n);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    vector<array<ll,1>> dp((n+1)*(m+1),{INF});
    priority_queue<array<int,5>,vector<array<int,5>>,greater<array<int,5>>> pq;
    pq.push({0,0,-1,0,0});
    int res=n*m;
    while(!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        int val=it[0];
        int px=it[1];
        int py=it[2];
        int x=it[3];
        int y=it[4];
        int nx=x,ny=y;
        int nval=val;
        // cout << val << " " << x << " " << y << endl;
        if (x==n-1 && y==m) {
            res=val;
            cout << res << endl;
            return;
        }
        else if (x<0 || y<0 || x>=n || y>=m) continue;
        dp[x][y]=min(dp[x][y],val);
        if (x==px){
            int vi = -1;
            if (py<y) vi=1;
            for (char it: {'A','B','C'}){
                nx=x;
                ny=y;
                if (it=='A') ny=y+vi;
                else if (it=='B') nx=x+vi;
                else if (it=='C') nx=x-vi;

                nval = val+(arr[x][y]!=it);
                // if (nx==n-1 && ny==m) {
                //     res=nval;
                //     break;
                // }
                if (nx<0 || ny<0 || nx>=n || ny>m) continue;
                if (dp[nx][ny]>=nval) {
                    // dp[x][y]=nval;
                    // cout << nval << " " << x << " " << y << " " << nx << " " << ny << endl;
                    pq.push({nval,x,y,nx,ny});
                }
            }
        }
        else if (y==py){
            int vi = -1;
            if (px<x) vi=1;
            for (char it: {'A','B','C'}){
                nx=x;
                ny=y;
                if (it=='A') nx=x+vi;
                else if (it=='B') ny=y+vi;
                else if (it=='C') ny=y-vi;

                nval = val+(arr[x][y]!=it);
                // if (nx==n-1 && ny==m) {
                //     res=nval;
                //     break;
                // }
                if (nx<0 || ny<0 || nx>=n || ny>m) continue;
                if (dp[nx][ny]>=nval) {
                    // dp[x][y]=nval;
                    // cout << val << " " << x << " " << y << " " << nx << " " << ny << endl;
                    
                    pq.push({nval,x,y,nx,ny});
                }
            }
        }
        
    }
    cout << "T" << res << endl;
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