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

int n, m, x;

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=-LINF,b=0,c=-LINF,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    vector<array<ll,2>> arr(n);

    for (int i=0;i<n;i++)
    {
        cin >> arr[i][0] >> arr[i][1];
        a=max(a,arr[i][0]+arr[i][1]);
        c=max(c,arr[i][0]-arr[i][1]);
    }
    ll mxl = 1e9;
    cout << "? U " << mxl << "\n";
    cout.flush();
    cin >> x;
    cout << "? U " << mxl << "\n";
    cout.flush();
    cin >> x;
    cout << "? R " << mxl << "\n";
    cout.flush();
    cin >> x;
    cout << "? R " << mxl << "\n";
    cout.flush();
    cin >> x;

    b = x+a-4*mxl;

    cout << "? D " << mxl << "\n";
    cout.flush();
    cin >> x;
    cout << "? D " << mxl << "\n";
    cout.flush();
    cin >> x;
    cout << "? D " << mxl << "\n";
    cout.flush();
    cin >> x;
    cout << "? D " << mxl << "\n";
    cout.flush();
    cin >> x;

    d = x+c-4*mxl;
    l = (b+d)>>1;
    r = b-l;
    cout << "! " << l << " " << r << "\n";
    cout.flush();
    return;
}

signed main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}