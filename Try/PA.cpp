// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e3 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
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

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int i_query(string s)
{
    int k;
    cout << s << endl; 
    cout.flush();
    cin >> k;
    return k;
}
char rev(char c)
{
    char resu = (c=='T')?'F':'T';
    return resu;
}

int n, m, vis[MAX_N], cnt[MAX_N];
map<pair<ll,ll>,ll> mpi;
vector<int> adj[MAX_N];
vector<pair<ll,ll>> path;
vector<pair<int,int>> que[MAX_N];

void dfs(int u) {
    vis[u] = 1;
    
    for (int v : adj[u]) {
        if (vis[v]) continue;
        int i=0;
        vector<ll> tem;
        ll x=0;
        mpi.clear();
        for (int i=path.size()-1;i>=0;i-=2)
        {
            mpi[path[i]]=2;
        }
        for (auto it: mpi)
        {
            x+=it.first.first;
            tem.push_back(x);
        }
        ll ni = tem.size();
        for (auto it: que[v])
        {
            ll x = max(ni - it.first,0LL);
            ll ex = path.size() - ni;
            // ex-=ex%2;
            if (x==0) cnt[it.second] = min(ni,(ll)it.first)+1;
            else cnt[it.second] = 2*tem[x-1]+it.first;
            cnt[it.second]+=ex;
        }
        if (v!=0)
        {
            mpi[{adj[v].size(),v}]=1;
            path.push_back({adj[v].size(),v});
        }
        
        dfs(v);
        if (v!=0)
        {
            mpi.erase(make_pair(adj[v].size(),v));
            path.pop_back();
        }
    }
    
}
void solve() {
    ll n=0,l=0,x=0,y=0,k=0,r=0,q=0;
    cin >> n >> q;
    for (int i=0;i<=q;i++) cnt[i]=0;
    mpi.clear();
    path.clear();
    for (int i=0;i<=n;i++)
    {
        vis[i]=0;
        adj[i].clear();
    }
    vector<ll> res(n,0);
    for (int i=0;i<n-1;i++)
    {
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i=0;i<q;i++)
    {
        cin >> l >> r;
        l--;
        que[l].push_back({r,i});
    }
    ll s = 0;
    dfs(s);
    for (int i=0;i<q;i++)
    {
        cout << cnt[i] << endl;
    }
}







int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}