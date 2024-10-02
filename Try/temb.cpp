// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1<<22;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, par[MAX_N], sz[MAX_N], num_grp;
vector<pair<ll,ll>> bm;

int find(int u) {
    return u == par[u] ? u : par[u] = find(par[u]);
}
 
void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (sz[u] > sz[v]) swap(u, v);
    par[u] = v;
    sz[v] += sz[u];
    num_grp--;
}
void upd(ll it, ll val)
{
    if (bm[it].first==-1) bm[it].first=val;
    else if (bm[it].second==-1)
    {
        if (bm[it].first==val) return;
        else 
        {
            bm[it].second = bm[it].first;
            bm[it].first = val;
            if (bm[it].second < bm[it].first)
            {
                swap(bm[it].first,bm[it].second);
            }
        }
    }
    else 
    {
        if (bm[it].second < val)
        {
            bm[it].second = bm[it].first;
            bm[it].first = val;
        }
        else if (bm[it].second != val)
        {   
            bm[it].first = max(bm[it].first,val);
        }
    }
}
void solve() {
    ll m, resu=0;
    cin >> n;
    m = 22;
    vector<ll> arr(n);
    bm.resize(MAX_N);
    for(int i=0;i<MAX_N;i++)
    {
        bm[i]=make_pair(-1,-1);
    }
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        upd(arr[i],i);
        m = max((int)m,(int)log2(arr[i]));
    }
    for (int j=0;j<m;j++)
    {
        for (int i=0;i<(1<<m);i++)
        {
            if (i&(1<<j))
            {
                ll ind = i^(1<<j);
                if (bm[i].first!=-1) upd(ind,bm[i].first);
                if (bm[i].second!=-1) upd(ind,bm[i].second);
            }
        }
    }
    for (int i=0;i<n;i++)
    {
        ll cur = arr[i];
        ll opt=0;
        bool check=false;
        for (int j=m-1;j>=0;j--)
        {
            if (((cur>>j)&1)==0)
            {
                if (bm[opt^(1<<j)].second!=-1 && bm[opt^(1<<j)].first>i)
                {
                    check=true;
                    opt^=(1<<j);
                }
            }
        }
        if (bm[opt].second!=-1 && bm[opt].first>i) resu = max(resu,arr[i]^opt);
    }
    cout << resu << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}