// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ari array
#define ll long long
#define int long long

const int MAX_N = 1e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

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
    ll n=0,m=0,l=0,r=0,k=0;
    ll w=0,x=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0;
    cin >> n >> q;
    vector<ll> arr(n),brr(n);
    map<ll,ll> ma,mb;
    vector<ari<ll,2>> ar(n),br(n);
    for (int i=0;i<n;i++)
    {
        cin >> x;
        arr[i]=x;
        ma[x]++;
        ar[i]={x,i};
        // ar[{arr[i],i}]=1;
    }
    for (int i=0;i<n;i++)
    {
        cin >> x;
        brr[i]=x;
        mb[x]++;
        br[i]={x,i};
        // br[{brr[i],i}]=1;
    }
    map<ll,ari<ll,2>> am,bm;
    ll ti=0;
    for (auto it: ma)
    {
        am[it.first]={it.second,ti};
        ti+=it.second;
    }
    ti=0;
    for (auto it: mb)
    {
        bm[it.first]={it.second,ti};
        ti+=it.second;
    }
    sort(ar.begin(),ar.end());
    sort(br.begin(),br.end());
    ll ans = 1;
    for (int i=0;i<n;i++)
    {
        ans = (ans*min(ar[i][0],br[i][0]))%MOD;
    }
    cout << ans << " ";
    for (int i=0;i<q;i++)
    {
        ll res = ans;
        cin >> x >> y;
        y--;
        
        

        if (x==1)
        {
            ll valy = arr[y];
            auto it1 = am[valy];
            auto it2 = it1;
            am.erase(valy);

            
            ll oi = it1[1]+it1[0]-1;
            ll oival = min(br[oi][0],ar[oi][0]);
            res = (res*qexp(oival,MOD-2,MOD))%MOD;
            
            it1[0]--;
            if (it1[0]>0) am[valy]=it1;
            it2 = am[valy+1];
            am[valy+1]={it2[0]+1,it1[0]+it1[1]};
            arr[y]++;
            
            it2 = am[valy+1];
            ll oj = it2[1];
            ar[oj][0]=valy+1;
            ll ojval = min(br[oj][0],ar[oj][0]);
            res = (res*ojval)%MOD;
            
        }
        else 
        {
            ll valy = brr[y];
            auto it1 = bm[valy];
            auto it2 = it1;
            bm.erase(valy);

            
            ll oi = it1[1]+it1[0]-1;
            ll oival = min(br[oi][0],ar[oi][0]);
            res = (res*qexp(oival,MOD-2,MOD))%MOD;
            
            it1[0]--;
            if (it1[0]>0) bm[valy]=it1;
            it2 = bm[valy+1];
            bm[valy+1]={it2[0]+1,it1[0]+it1[1]};
            brr[y]++;
            
            it2 = bm[valy+1];
            ll oj = it2[1];
            br[oj][0]=valy+1;
            ll ojval = min(br[oj][0],ar[oj][0]);
            res = (res*ojval)%MOD;
        }
        ans = res;
        cout << res << " ";
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}