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
    ll n=0,m=0,k=0,l=0,x=0,bi=0;
    cin >> n;
    vector<ll> arr(n);
    k = ceil(log2(n));
    m = 1<<k;
    // cout << k << " " << m << endl;
    ll one = m-1;
    vector<ll> brr(m,-1),crr(m);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        brr[one^i]=arr[i];
    }
    for (int i=0;i<m;i++)
    {
        crr[i^one]=max(brr[i],0LL);
    }
    for (int i=0;i<k;i++)
    {
        for (int j=0;j<m;j++)
        {
            if ((j&(1<<i))!=0)
            {
                crr[j]^=crr[j^(1<<i)];
            }
        }
    }
    for (int i=0;i<m;i++)
    {
        if (brr[i]==-1)
        {
            crr[i^one] = 0;
        }
    }
    for (int i=0;i<k;i++)
    {
        for (int j=0;j<m;j++)
        {
            if ((j&(1<<i))!=0)
            {
                crr[j]^=crr[j^(1<<i)];
            }
        }
    }
    for (int i=0;i<m;i++)
    {
        if (brr[i]==-1)
        {
            brr[i] = crr[i^one];
        }
    }
    for (int i=0;i<k;i++)
    {
        for (int j=0;j<m;j++)
        {
            if ((j&(1<<i))!=0)
            {
                brr[j]^=brr[j^(1<<i)];
            }
        }
    }
    for (int i=n-1;i>=0;i--)
    {
        cout << brr[i] << " ";
    }
    cout << endl;
}






int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}