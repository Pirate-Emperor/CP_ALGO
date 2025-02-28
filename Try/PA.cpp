// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 2e5 + 5;
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
    ll n=0,m=0,l=0,r=0;
    ll w=0,x=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n >> l >> r;
    vector<ar<int,2>> arr(n);
    vector<int> brr(n+5,0);
    for (int i=0;i<n;i++)
    {
        cin >> x;
        arr[i]={x,i+1};
    }
    
    a=0;
    for (int i=0;i<(n+1)/2;i++) 
    {
        a^=arr[i][0];
    }
    if (n%2==0) arr.push_back({a,1});
    n=arr.size();
    c=0;
    for (int i=0;i<n;i++) 
    {
        c^=arr[i][0];
        brr[i]=c;
        // cout << brr[i] << " ";
    }

    b=0;
    // cout << "-";
    while(l>n)
    {
        l>>=1;
        if (l<=0) break;
        if (l<=n) 
        {
            b^=brr[l-1];
            l=-1;
            break;
        }
        else
        {
            b^=brr[n-1];
            if (l%2==1) 
            {
                l=-1;
                break;
            }
        }
        // cout << l << " ";
    }
    if (l>0)
    {
        b^=arr[l-1][0];
    }
    cout << b << endl;
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