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
    
    cin>>n;
    vector<ll> arr(n);
    for(int i=0;i<n;++i) cin>>arr[i];
    
    auto getp = [](ll x) {
        vector<vector<ll>> p = {{x}};
        if(x>=2) p.push_back({1,x-1}), p.push_back({x-1,1});
        // if(x>=3) p.push_back({2,x-1}), p.push_back({x-2,2}), p.push_back({1,x-1,1});
        if(x>=3) p.push_back({2,x-2}), p.push_back({x-2,2}), p.push_back({1,x-2,1});
        if(x>=4) p.push_back({1,2,x-3}), p.push_back({x-3,2,1}), p.push_back({2,1,x-3}), p.push_back({x-3,1,2});
        if(x>=5) p.push_back({2,x-4,2});
        vector<vector<ll>> val;
        for(auto& v:p) {
            bool ok=true;
            for(size_t i=1;i<v.size();++i) if(v[i]==v[i-1]) ok=false;
            if(ok) val.push_back(v);
        }
        return val;
    };

    vector<map<ll,pair<ll,int>>> dp(n);
    auto p0 = getp(arr[0]);
    for(int j=0;j<p0.size();++j) dp[0][p0[j].back()] = {-1,j};
    // for(int j=0;j<p0.size();++j) dp[0][p0[j].back()] = {1,j};
    for(int i=1;i<n;++i) {
        auto p = getp(arr[i]);
        for(int j=0;j<p.size();++j) {
            for(auto& [pl,_]:dp[i-1]) {
                if(p[j].front()!=pl) {
                    dp[i][p[j].back()] = {pl,j};
                    break;
                }
            }
        }
        if(dp[i].empty()) {
            cout<<"-1\n";
            return;
        }
    }
    vector<ll> ans;
    ll cur = dp.back().begin()->first;
    for(int i=n-1;i>=0;--i) {
        auto [pr,j] = dp[i][cur];
        auto p = getp(arr[i]);
        for(int k=p[j].size()-1;k>=0;--k) ans.push_back(p[j][k]);
        cur = pr;
    }
    reverse(ans.begin(),ans.end());

    cout<<ans.size()<<endl;
    for(ll x:ans) cout<<x<<" ";
    cout<<endl;
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
