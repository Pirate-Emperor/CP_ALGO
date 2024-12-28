// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define int long long

const int MAX_N = 2e5+100;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, vis[MAX_N];
vector<int> adj[MAX_N];

void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

void solve() {
    cin >> n;
    m=n-1;
    vector<pair<ll,ll>> edges;
    for (int i = 1; i <= n; i++) 
    {
        adj[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u,v});
        edges.push_back({v,u});
    }
    vector<ll> leafs;
    map<ll,ll> lef,deg1;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size()==1) 
        {
            leafs.push_back(i);
            lef[i]=1;
            if (adj[adj[i][0]].size()!=1) deg1[adj[i][0]]=1;
        }
        // adj[i].clear();
    }
    // for (auto it: edges) {
    //     int u = it.first;
    //     int v = it.second;
    //     if (lef.find(u)!=lef.end()) continue;
    //     if (lef.find(v)!=lef.end()) continue;

    //     adj[u].push_back(v);
    //     adj[v].push_back(u);
    // }
    
    ll temp = leafs.size();
    ll res = temp*(n-temp);
    n-=temp;
    ll temp2 = deg1.size();
    cout << temp << " " << temp2 << " ";
    res += temp2*(n-temp2);
    cout << res << endl;    

}


signed main() {
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