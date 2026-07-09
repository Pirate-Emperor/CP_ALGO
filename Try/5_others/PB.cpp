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

struct Tr { ll lv; ll pl; ll pi; 
};

vector<vector<ll>> getp(ll v) {
    vector<vector<ll>> r;
    r.push_back({v});
    if(v>1) {
        if(1!=v-1) {
            r.push_back({1,v-1});
            r.push_back({v-1,1});
        }
        if(2!=v-2&&v-2>0) {
            r.push_back({2,v-2});
            r.push_back({v-2,2});
        }
        if(3!=v-3&&v-3>0) {
            r.push_back({3,v-3});
            r.push_back({v-3,3});
        }
    }
    if(v>2) {
        if(1!=v-2) r.push_back({1,v-2,1});
        if(v-4>0&&2!=v-4) r.push_back({2,v-4,2});
        if(v-3>0&&2!=v-3) r.push_back({1,2,v-3});
        if(v-3>0&&v-3!=2) r.push_back({v-3,2,1});
        if(v-3>0&&1!=v-3) r.push_back({2,1,v-3});
        if(v-3>0&&v-3!=1) r.push_back({v-3,1,2});
    }
    sort(r.begin(),r.end());
    r.erase(unique(r.begin(),r.end()),r.end());
    return r;
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    vector<ll> arr(n),brr(n),crr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    for(int i=0;i<n;i++) cin>>brr[i];
    for(int i=0;i<n;i++){
        auto it=lower_bound(brr.begin(),brr.end(),arr[i]);
        if(it==brr.end()) crr[i]=-1;
        else crr[i]=distance(brr.begin(),it)+1;
    }
    set<int> av;
    for(int i=1;i<=n;i++) av.insert(i);
    vector<int> p(n);
    bool check=true;
    for(int i=0;i<n;i++){
        if(crr[i]==-1){
            check=false;
            break;
        }
        auto it=av.lower_bound(crr[i]);
        if(it==av.end()){
            check=false;
            break;
        }
        p[i]=*it;
        av.erase(it);
    }
    if(!check){
        cout<<-1<<endl;
        return;
    }
    ll res=0;
    vector<int> bit(n+1,0);
    auto fa=[&](int i,int v){
        for(;i<=n;i+=i&-i) bit[i]+=v;
    };
    auto get=[&](int i){
        int s=0;
        for(;i>0;i-=i&-i) s+=bit[i];
        return s;
    };
    for(int i=0;i<n;i++){
        res+=i-get(p[i]);
        fa(p[i],1);
    }
    cout<<res<<endl;
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