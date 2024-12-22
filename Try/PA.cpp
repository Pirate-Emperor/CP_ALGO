// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};

void solve() {
    ll n=0,m=0,l=0,r=0,x=0,k=0;
    cin >> n;
    vector<ll> arr(n);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    arr.resize(unique(all(arr))-arr.begin());
    n = arr.size();
    set<st> s;
    vector<vector<ll>> ed(2e6+10);
    for (int i=1;i<n;i++)
    {
        s.insert({i,arr[i]-arr[i-1],0});
        ed[arr[i]-arr[i-1]].push_back(i);
    }

    for (int i=1;;i++)
    {
        for (auto x: ed[i])
        {
            auto it = s.find({x,i,0});
            assert(it!=s.end());
            auto L = (it==s.begin())?s.end():prev(it);
            auto R = next(it);
            if (L!=s.end() && L->t && R!=s.end() && R->t)
            {
                L->len+=i+R->id;
                s.erase(it);
                s.erase(R);
            }
            else if (L!=s.end() && L->t)
            {
                L->len+=i;
                s.erase(it);
            }
            else if (R!=s.end() && R->t)
            {
                L->len+=R->id;
                s.erase(it);
                s.erase(R);
            }
            else
            {
                it->t=1;
            }
        }
        if (arr[0]<i*(i+1))
        {
            ll L = max(arr[0],i*i);
            ll R = i*(i+1);
            ll si = i;
            for (auto it: s)
            {
                L+=it.len;
                if (it.t==0)
                {
                    si = ceil((sqrt(1+4*L)-1)/2.0);
                    L=max(L,si*si);
                }
                R=min(R+it.len,si*(si+1));
                if (L>R) break;
            }
            if (L<=R)
            {
                cout << L-arr[n-1] << endl;
                return;
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}