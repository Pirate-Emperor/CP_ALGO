// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e3 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
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

int n,m,x;
void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=-LINF,b=0,c=-LINF,d=0;
    ll g=0,q=0,k=0;
    cin >> a >> b;
    vector<ll> arr(a);
    vector<ll> pref(a+1);
    vector<ll> pre3(a+1);
    pref[0]=0;
    pre3[0]=0;
    for (int i=0;i<a;i++)
    {
        cin >> arr[i];
        ll temp=arr[i];
        ll tem=0;
        ll ch=0;
        while (temp>0)
        {
            // if (temp==3) ch=1;
            temp/=2;
            tem++;
        }
        if (arr[i]==1<<(tem-1)) ch++;
        pref[i+1]=pref[i]+tem-ch;
        pre3[i+1]=pre3[i]+((arr[i]-1)==1<<(tem-1));
        // cout << tem+ch-1 << " ";
        // g=arr[i]^(1<<(tem-2));
        // if (g < arr[i]) pref[i+1]++;
    }
    for (int j=0;j<b;j++)
    {
        cin >> l >> r;
        ll res = pref[r]-pref[l-1] - (pre3[r]-pre3[l-1]+1)/2;
        // if (pre3[r]-pre3[l-1]>0) res--;
        cout << res << endl;
    }
    return;
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