// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 3e5+10;
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

int vis[2*MAX_N];
ll idt[2*MAX_N];
ll res;
vector<int> adj[2*MAX_N];
map<ll,ll> mpi;

void dfs(int u) {
    vis[u] = 1;
    res = max(res,idt[u]);
    for (int v : adj[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

void solve() {
    ll n,k,x,y;
    cin >> n;
    vector<ll> arr(n+1);
    mpi.clear();
    ll idx=0;
    if (mpi.find(n)==mpi.end())
    {
        mpi[n]=idx;
        idt[idx]=n;
        idx++;
    }
    for (int i=1;i<=n;i++)
    {
        cin >> arr[i];
        arr[i]+=i-1;
        if (mpi.find(arr[i])==mpi.end())
        {
            mpi[arr[i]]=idx;
            idt[idx]=arr[i];
            idx++;
        }
        if (mpi.find(arr[i]+i-1)==mpi.end())
        {
            mpi[arr[i]+i-1]=idx;
            idt[idx]=arr[i]+i-1;
            idx++;
        }
    }
    for (int i=1;i<=n;i++)
    {
        adj[mpi[arr[i]]].push_back(mpi[arr[i]+i-1]);
    }
    res=0;
    dfs(0);
    cout << res << endl;
    for (int i=0;i<=idx;i++)
    {
        adj[i].clear();
        vis[i]=0;
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