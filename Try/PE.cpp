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
    ll x,y,z,k, resu=0;
    cin >> x >> y >> z >> k;
    ll d = 0;
    resu = LINF;
    while(z>0)
    {
        if (k<1e4)
        {
            for (int j=0;j<k;j++)
            {
                ll di=d+j;
                if (di==0) continue;
                ll ti=(di*x);
                ti+=((z+di-1)/(di))*y;
                ti+=(d/k)*y;
                resu = min(resu,ti);
            }
        }
        else
        {
            ll cl = (z+d+k-2)/(d+k-1);
            ll cr = (d==0)?sqrt(z): (z+d-1)/(d);
            for (int i=cl;i<=cr;i++)
            {
                ll di = (z)/i;
                ll ti = di*x;
                ti+=i*y;
                ti+=(d/k)*y;
                resu = min(resu,ti);
            }
        }
        
        // cout << resu << " ";
        d+=k;
        z-=d;
    }
    if (z==0)
    {
        ll di = d;
        ll ti=(di*x);
        ti+=((z+di-1)/(di))*y;
        ti+=(d/k)*y;
        resu = min(resu,ti);
    }
    cout << resu << endl;
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