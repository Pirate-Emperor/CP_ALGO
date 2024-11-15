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
    ll n=0,m,q=0,resu=0,on=0,ze=0,a=0,b=0,c=0,x;
    cin >> n;
    vector<ll> arr(n),pref(n+1,0),nex(n+1,-1),res(n+1,0);
    map<pair<ll,ll>,ll> greq,les;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        pref[i+1]=max(pref[i],arr[i]);
        greq[{arr[i],i}]=1;
    }
    a=0;
    for (int i=0;i<n;i++)
    {
        map<pair<ll,ll>,ll> tem;
        auto it = greq.begin();
        while(it != greq.end() && it->first.first<arr[i])
        {
            tem[{it->first.first,it->first.second}]=1;
            les[{it->first.second,it->first.first}]=1;
            it++;
        }
        for (auto it2=tem.begin();it2!=tem.end();it2++)
        {
            greq.erase(it2->first);
        }
        nex[i]=i;
        if (les.rbegin()!=les.rend()) nex[i]=max(nex[i],les.rbegin()->first.first);
    }
    for (int i=n-1;i>=0;i--)
    {
        
        res[i+1]=max(pref[i+1],res[nex[i]+1]);
    }
    for (int i=0;i<n;i++)
    {
        cout << res[i+1] << " ";
    }
    cout << endl;
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