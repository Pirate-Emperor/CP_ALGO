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
const ll LINF = 1e18;

struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void solve() {
    ll n=0,m=0,l=0,r=0,k=0;
    ll w=0,x=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0;
    cin >> l >> r >> g;
    if (g>r)
    {
        cout << "-1 -1\n";
        return;
    }

    a = l/g;
    if ((ll)(a*g)<l) a++;
    b = r/g;
    if (a>b) 
    {
        cout << "-1 -1\n";
        return;
    }
    x=-1;
    y=-1;
    w=-1;
    z=0;
    for (int i=a;i<=b-z;i++)
    {
        for (int j=b;j>=z+i;j--)
        {
            if (gcd(i,j)==1)
            {
                ll temp = j-i;
                if (temp>w)
                {
                    w=temp;
                    x=i;
                    y=j;
                    z=max(z,w);
                }
            }
        }
    }
    if (w<0)
    {
        cout << "-1 -1\n";
        return;
    }
    a=x*g;
    b=y*g;
    cout << a << " " << b << endl;
    


    
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