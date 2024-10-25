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
deque<ll> ans; 
void recur(int n)
{
    if (n==0) return;
    ll x,y,ti;
    ti = max(n-2,0);
    cout << "? " << ti << endl;
    cin >> x >> y;
    if (n==1)
    {
        ans.push_front(x);
        return;
    }
    else if (n==2)
    {
        if (y==0)
        {
            ll a,b;
            cout << "? " << 0 << endl;
            cin >> a >> b;
            ans.push_front(x);
            ans.push_front(a);
        }
        else
        {
            ans.push_back(x);
            ans.push_front(y);
        }
        return;
    }
    if (y==0)
    {
        ll a,b;
        cout << "? " << 0 << endl;
        cin >> a >> b;
        recur(n-2);
        ans.push_front(x);
        ans.push_front(a);
    }
    else
    {
        recur(n-1);
        if (ans.front()==y)
        {
            ans.push_back(x);
        }
        else ans.push_front(x);
    }
    return;
}
void solve() {
    cin >> n;
    recur(n);
    cout << "! ";
    while(!ans.empty())
    {
        cout << ans.front() << " ";
        ans.pop_front();
    }
    cout << endl;
    cout.flush();
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
    cout.flush();
}