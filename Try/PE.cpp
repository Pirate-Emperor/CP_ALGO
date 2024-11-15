// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e6;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, vis[MAX_N];
vector<int> adj[MAX_N];



ll dfs(int u) {
    vis[u] = 1;
    ll b=0,resu=0;
    vector<ll> dep;
    for (int v : adj[u]) {
        if (vis[v]) continue;
        b = dfs(v);
        resu=max(resu,b);
        dep.push_back(b);
    }
    if (dep.size()==0) return 0;
    else if (dep.size()<3) return resu+1;
    sort(dep.begin(),dep.end());
    ll l=resu+1,r=resu+100,mid=0;
    ll res=resu+100;
    // cout << u << " " << dep[3] << " " << endl;
    while(l<r)
    {
        mid = (r+l)/2;
        ll curd=mid-dep[0],cnt=1;
        for (int i=1;i<dep.size();i++)
        {
            while(curd>mid-dep[i])
            {
                cnt=(cnt+1)/2;
                curd--;
            }
            cnt++;
        }
        ll tem = log2(cnt-1);
        
        if (curd<=tem) l=mid+1;
        else 
        {
            // cout << mid << " " << tem << " " << curd << " " << endl;
            res=min(res,mid);
            r=mid-1;
        }
    }
    for (ll mid: {l,r})
    {
        ll curd=mid-dep[0],cnt=1;
        for (int i=1;i<dep.size();i++)
        {
            while(curd>mid-dep[i])
            {
                cnt=(cnt+1)/2;
                curd--;
            }
            cnt++;
        }
        ll tem = log2(cnt-1);
        
        if (curd<=tem) l=mid+1;
        else 
        {
            // cout << mid << " " << tem << " " << curd << " " << endl;
            res=min(res,mid);
            r=mid-1;
        }
    }
    return res;
}

void solve() {
    cin >> n;
    m=n-1;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u;
        v = i+2;
        adj[u].push_back(v);
    }
    ll resu=0;
    resu = dfs(1);
    cout << resu << endl;
    for (int i=1;i<=n;i++)
    {
        vis[i]=0;
        adj[i].clear();
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