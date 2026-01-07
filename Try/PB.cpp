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


int reduce(array<int, K> &b, int x) {  // reducing x using basis vectors b
	for (int i = K - 1; i >= 0; i--) {
		if (x & (1 << i)) {  // check if the ith bit is set
			x ^= b[i];
		}
	}
	return x;
}

bool add(array<int, K> &b, int x) {
	x = reduce(b, x);  // reduce x using current basis
	if (x != 0) {
		for (int i = K - 1; i >= 0; i--) {
			if (x & (1 << i)) {
				b[i] = x;  // add x to the basis if it is independent
				return true;
			}
		}
	}
	return false;
}

bool check(array<int, K> &b, int x) {
	return (reduce(b, x) ==
	        0);  // if x reduces to 0, it can be represented by the basis
}

bool basis_check(array<int, K> &b, array<int, K> &c, int w)
{
    bool chec = false;
    for (auto it: c)
    {
        if (add(b,it^w)) chec=true;
    }
    return chec;
}

int min_val_from_basis(array<int, K> b, int mask)
{
    int mi = LINF;
    for (int i=0;i<K;i++)
    {
        if ((1<<i) & mask==0) 
        {
            mi = min(mi,b[i]);
            mask = mask|(1<<i);
            for (int j=0;j<K;j++)
            {
                if ((1<<j)&mask ==0)
                {
                    mi = min(mi,b[j]);
                    b[j]^=b[i];
                    mi = min(mi,b[j]);
                }
            }
            mi = min(mi,min_val_from_basis(b, mask));
        }
    }
    return mi;
}

void recur(int st)
{
    vis[st]=1;
    for (auto it: adj[st])
    {
        if (basis_check(basis[it[0]], basis[st], it[1])) recur(it[0]);
    }
    return;
}

void solve() {
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    vector<array<ll,2>> arr(n), dp(n,{INF,INF});
    
    for (int i=0;i<n;i++){
        cin >> arr[i][0];
    }
    for (int i=0;i<n;i++){
        cin >> arr[i][1];
    }
    dp[0][0]=min(arr[0][0],arr[0][1]);
    dp[0][1]=max(arr[0][0],arr[0][1]);
    // int ind=0;
    // for (int i=1;i<n;i++)
    // {
    //     a=min(arr[i][0],arr[i][1]);
    //     b=max(arr[i][0],arr[i][1]);
    //     if (dp[i-1][0]<=a) {
    //         dp[i][0]=a;
    //         dp[i][1]=b;
    //         ind=i;
    //     }
    //     else break;
    // }
    // if (ind==n-1) {
    //     cout << "Yes\n";
    //     return;
    // }
    // int val=0;
    // for (int i=n-1;i>ind;i--){
    //     a=min(arr[i][0],arr[i][1]);
    //     b=max(arr[i][0],arr[i][1]);
    //     if (i==n-1) val=b;
    //     else {
    //         if (b<=val) val=b;
    //         else if (a<=val) val=a;
    //         else {
    //             cout << "No\n";
    //             return;
    //         }
    //     }
    // }
    // for (int i=ind;i>=0;i--){
    //     a=min(arr[i][0],arr[i][1]);
    //     b=max(arr[i][0],arr[i][1]);
    //     if (dp[i][1]<=val) {
    //         val=dp[i][1];
    //         cout << "Yes\n";
    //         return;
    //     }
    //     else {
    //         if (b<=val) val=b;
    //         else if (a<=val) val=a;
    //         else {
    //             cout << "No\n";
    //             return;
    //         }
    //     }
    // }
    // cout << "No\n";
    // return;
    for (int i=1;i<n;i++)
    {
        // cout << dp[i-1][0] << " " << dp[i-1][1] << " - ";
        a=min(arr[i][0],arr[i][1]);
        b=max(arr[i][0],arr[i][1]);
        if (dp[i-1][0]<=a) {
            dp[i][0]=a;
            if (dp[i-1][1]<=a){
                dp[i][1]=a;
            }
            else {
                dp[i][1]=b;
            }
        }
        else if (dp[i-1][0]<=b){
            dp[i][0]=b;
            if (dp[i-1][1]<=b){
                dp[i][1]=b;
            }
            else {
                // cout << "No\n";
                // return;
            }
        }
        else {
            cout << "No\n";
            return;
        }
        
    }
    if (dp[n-1][1] == INF) cout << "No\n";
    else cout << "Yes\n";
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