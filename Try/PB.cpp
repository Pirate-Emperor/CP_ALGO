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
ll query(ll l, ll r)
{
    ll res;
    cout << "? "  << l << " " << r;
    cout.flush()
    cin >> res;
    return res; 
}

void solve() {
    ll n;
    cin >> n;
    ll m = n/4;
    ll a = query(1,m);
    ll b = query(m+1,2*m);
    ll c = query(2*m+1,3*m);
    ll d = query(3*m+1,4*m);
    if (a==b)
    {
        if (a==1)
        {
            ll i = n/2;
            ll k=0;
            while(i>1)
            {
                i/=2;
                ll l=1;
                ll r=l+k+i-1;
                ll ti = query(l,r);
                if (ti==1)
                {
                    k+=i;
                }
            }
            cout << "! " << k;
        }
        else
        {
            ll i = n/2;
            ll k=i;
            ll ti = query(i+1,4*m);
            if (ti==1)
            {
                k=k/2;
                i=i/2;
            }
            while(i>1)
            {
                i/=2;
                ll r=4*m;
                ll l=r-k-i+1;
                ll ti = query(l,r);
                if (ti==0)
                {
                    k+=i;
                }
            }
            cout << "! " << k;
            
        }
    }
    else
    {
        if (c==1)
        {
            ll i = n/2;
            ll k=0;
            while(i>1)
            {
                i/=2;
                ll l=2*m;
                ll r=l+k+i-1;
                ll ti = query(l,r);
                if (ti==1)
                {
                    k+=i;
                }
            }
            cout << "! " << k;
        }
        else
        {
            ll i = n/2;
            ll k=i;
            ll ti = query(1,i);
            if (ti==1)
            {
                k=k/2;
                i=i/2;
            }
            while(i>1)
            {
                i/=2;
                ll l=1;
                ll r=l+k+i-1;
                ll ti = query(l,r);
                if (ti==0)
                {
                    k+=i;
                }
            }
            cout << "! " << k;
        }
    }
    cout.flush()
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