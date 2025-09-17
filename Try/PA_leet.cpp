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
vector<array<int,2>> adj[MAX_N];
vector<array<int,2>> radj[MAX_N];
vector<ll> dist;
vector<ll> vis;
array<int,K> basis[MAX_N];



vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
    vector<int> temp = nums;
    int n = temp.size();
    for (int i=0;i<n;i++)
    {
        int ki = i;
        for (int j=i+1;j<n;j++)
        {
            if (temp[j]<temp[ki]) ki = j;
        }
        int tem = temp[i];
        temp[i] = temp[ki];
        temp[ki] = tem;
    }
    int oki = -1;
    int nki = -1;
    vector<int> sumcnt(k+5,-1);
    vector<bool> res(n,false);
    vector<bool> temres(n,false);
    sumcnt[0]=0;
    for (int i=0;i<n;i++)
    {
        while(nki<n-1 && temp[nki+1]<i+1) nki++;
        temres[i]=nki!=oki;
        if (oki!=nki)
        {
            for (int kil = oki+1;kil<=nki;kil++)
            {
                for (int j=k-1;j>=0;j--)
                {
                    if (j+temp[kil]>k) continue;
                    if (sumcnt[j]==0) sumcnt[j+temp[kil]] = 0;
                }
            }
        }
        // for (int j=0;j<=k;j++) cout << sumcnt[j] << " ";
        // cout << endl; 
        int ksum = k;
        for (int j=nki+1;j<n;j++)
        {
            if (sumcnt[ksum]==0) 
            {
                res[i]=true;
                // break;
            }
            ksum-=i+1;
            if (ksum<0) break;
        }
        oki = nki;
    }
    return res;
}

void solve() {
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    auto brr = subsequenceSumAfterCapping(arr, k);
    for (int i=0;i<n;i++)
    {
        cout << brr[i] << " ";
    }
    cout << endl;
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