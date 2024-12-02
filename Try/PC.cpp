// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 5e5 + 5;
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


void solve() {
    ll n=0,m=0;
    cin >> n;
    vector<ar<ll,2>> arr(n);
    vector<ll> vis(n,0),res(n,0);
    vector<pair<ll,pair<ll,ll>>> path;
    map<pair<ll,ll>,vector<ll>> mpi;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i][0] >> arr[i][1];
        path.push_back({arr[i][0],make_pair(n-arr[i][0],i)});
        path.push_back({arr[i][1],make_pair(n-arr[i][0],i)});
        mpi[{arr[i][0],arr[i][1]}].push_back(i);
    }
    for (auto it: mpi)
    {
        if (it.second.size()>1)
        {
            for (auto i: it.second)
            {
                vis[i]=2;
            }
        }
    }
    sort(path.begin(),path.end());
    map<pair<ll,pair<ll,ll>>,ll> smar;
    map<pair<ll,pair<ll,ll>>,ll,greater<pair<ll,pair<ll,ll>>>> bigl;
    for (int i=0;i<path.size();i++)
    {
        // cout << path[i].second.second << " ";
        vis[path[i].second.second]++;
        if (vis[path[i].second.second]>2) continue;
        if (vis[path[i].second.second]==2)
        {
            bigl.erase({arr[path[i].second.second][0], make_pair(n-path[i].second.first,path[i].second.second)});
            smar.erase({arr[path[i].second.second][1], make_pair(path[i].second.first, path[i].second.second)});
            auto it = bigl.lower_bound({arr[path[i].second.second][0], make_pair(n-path[i].second.first,path[i].second.second)});
            ll li=-1,ri=-1;
            if (it!=bigl.end())
            {
                li=it->first.first;
            }
            else continue;
            auto it2 = smar.lower_bound({arr[path[i].second.second][1], make_pair(path[i].second.first, path[i].second.second)});
            if (it2!=smar.end())
            {
                ri=it2->first.first;
            }
            else continue;
            res[path[i].second.second]=ri-li-(arr[path[i].second.second][1]-arr[path[i].second.second][0]);
        }
        else
        {
            bigl[{arr[path[i].second.second][0], make_pair(n-path[i].second.first,path[i].second.second)}]=i;
            smar[{arr[path[i].second.second][1], make_pair(path[i].second.first,path[i].second.second)}]=i;
        }
    }
    for (int i=0;i<n;i++)
    {
        cout << res[i] << endl;
    }
    // cout << endl;
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