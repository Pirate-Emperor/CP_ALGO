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
    int n;
    if(!(cin>>n)) return;
    int k=0;
    while((1LL<<k)<=n) k++;
    vector<string>S(k);
    for(int i=0;i<k;i++) cin>>S[i];
    vector<int>E(k,0);
    for(int i=1;i<=n;i++)for(int j=0;j<k;j++)if((i>>j)&1)E[j]++;
    
    vector<int>W(k,0);
    for(int j=0;j<k;j++){
        int c=0;
        for(int i=0;i<n;i++) if(S[j][i]=='1') {
            c++;
            W[j]=c;
        }
    }
    vector<int> sE=E,sW=W;
    sort(sE.begin(),sE.end());
    sort(sW.begin(),sW.end());
    if(sE!=sW){
        cout<<0<<endl;
        return;
    }
    vector<int>p(k,-1);
    vector<bool>u(k,0);
    for(int i=0;i<k;i++) for(int j=0;j<k;j++) if(!u[j]&&E[i]==W[j]) {
        u[j]=1;p[i]=j;
        break;
    }
    vector<int>a(n,0);
    for(int i=0;i<n;i++){
        int v=0;
        for(int j=0;j<k;j++) if(S[p[j]][i]=='1') {
            v|=(1<<j);
            a[i]=v;
        }
    }
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++) if(a[i]!=i+1) {
        cout<<0<<endl;
        return;
    }
    ll ans=1;
    map<int,int>f;
    for(int x:E) f[x]++;
    for(auto&[w,ct]:f) for(int i=1;i<=ct;i++) ans*=i;
    cout<<ans<<endl;
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