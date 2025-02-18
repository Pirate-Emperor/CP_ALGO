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
    ll g=0,q=0;
    cin >> n >> m;
    vector<vector<int>> arr(n,vector<int>(m,0));
    map<int,int> mpi;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            cin >> arr[i][j];
            mpi[arr[i][j]]=1;
        }
    }
    a=1;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            if (i>0 && arr[i][j]==arr[i-1][j]) 
            {
                mpi[arr[i][j]]=2;
            }
            if (i<n-1 && arr[i][j]==arr[i+1][j]) 
            {
                mpi[arr[i][j]]=2;
            }
            if (j>0 && arr[i][j]==arr[i][j-1]) 
            {
                mpi[arr[i][j]]=2;
            }
            if (j<m-1 && arr[i][j]==arr[i][j+1]) 
            {
                mpi[arr[i][j]]=2;
            }
            if (mpi[arr[i][j]]==2) a=2;
        }
    }
    for (auto it: mpi) b+=it.second;
    b-=a;
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