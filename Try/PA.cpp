// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
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

void solve() {
    ll n=0,m,q=0,resu=0,on=0,ze=0,a=0,b=0,c=0,d;
    cin >> n >> m;
    vector<map<ll,ll>> adj(n);
    for (int i=0;i<m;i++)
    {
        cin >> a >> b;
        a--;
        b--;
        adj[a].insert({b,1});
        adj[b].insert({a,1});
    }
    resu=2*max(n,m);
    ll lef=resu;
    vector<ar<ll,3>> res;
    for (int i=0;i<n;i++)
    {
        c=adj[i].size();
        if (c<=1) continue;
        auto tem = adj[i];
        for (auto it = tem.rbegin(); it != tem.rend(); advance(it, 1)) {
            auto fi = it;
            advance(it,1);
            if (it==tem.rend()) break;
            auto si = it;
            if (adj[fi->first].find(si->first)!=adj[fi->first].end())
            {
                adj[fi->first].erase(si->first);
                adj[si->first].erase(fi->first);
            }
            else
            {
                adj[fi->first][si->first]=1;
                adj[si->first][fi->first]=1;
            }
            adj[fi->first].erase(i);
            adj[si->first].erase(i);
            adj[i].erase(fi->first);
            adj[i].erase(si->first);
            lef--;
            res.push_back({i,fi->first,si->first});
            // cout << i << fi->first << si->first << " ";
        }
    }
    vector<bool> vis(n);
    vector<ll> temp;
    a=-1;
    b=-1;
    for (int i=0;i<n;i++)
    {
        if (!vis[i])
        {
            vis[i]=true;
            temp.push_back(i);
            if (adj[i].size()>0)
            {
                int j=adj[i].begin()->first;
                vis[j]=true;
                a=i;
                b=j;
            }
        }
        
    }
    if (a!=-1)
    {
        for (int i=0;i<temp.size();i++)
        {
            if (a==temp[i]) continue;
            res.push_back({a,b,temp[i]});
            b=temp[i];
        }
    }
    cout << res.size() << endl;
    for (int i=0;i<res.size();i++)
    {
        a = res[i][0]+1;
        b = res[i][1]+1;
        c = res[i][2]+1;
        cout << a << " " << b << " " << c << endl;
    }
    return;
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