// by rumbling

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const int MAX_K = 360+5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
const int OFF=40;
const int MDIF=100;
const int G=3;

ll gcd(ll a, ll b){
    return b?gcd(b,a%b):a;
}
 
ll qexp(ll a, ll b, ll m){
    ll res=1;
    while(b){
        if (b%2)res=res*a%m;
        a=a*a%m;
        b/=2;
    }
    return res;
}

ll n, m;
vector<array<ll,2>> adj[MAX_N];
vector<array<ll,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
ll res=0;
vector<ll>arr[MAX_N];
ll brr[MAX_N], crr[MAX_N], drr[MAX_N];
ll li;

void rec(ll u,ll p){
	drr[u]=1;
	arr[u].assign(2,INF);
	arr[u][1]=0;
	ll ind=0;
	bool chk=true;
	for(auto&e:adj[u]){
		if(e[0]==p) continue;
		ll v=e[0],typ=e[1];
		rec(v,u);
		ll cct=(typ==0)?min(brr[v],crr[v]):brr[v];
        // ll cct=(typ==0)?min(crr[v],brr[v]):brr[v];
		ll ns=min(li,drr[u]+drr[v]);
		vector<ll>nd(ns+1,INF);
		for(ll i=1;i<arr[u].size();++i){
			if(arr[u][i]==INF) continue;
			if(cct!=INF) nd[i]=min(nd[i],arr[u][i]+cct);
            // if(cct!=INF) nd[i]=min(nd[i],arr[u][i-1]+cct);
			for(ll j=1;j<arr[v].size();++j)
				if(arr[v][j]!=INF){
                    if (i+j<=li) nd[i+j]=min(nd[i+j],arr[u][i]+arr[v][j]);
                    else {
                        // nd[i+j]=arr[u][i]+arr[v][j];
                    }
                }
		}
		drr[u]=ns;
		swap(arr[u],nd);
		ll ih=INF;
		for(ll i=1;i<arr[v].size();++i) ih=min(ih,arr[v][i]);
		ll bv=min(ih,cct);
		if(bv==INF) chk=false;
		ind+=bv;
	}
	brr[u]=crr[u]=INF;
	if(chk){
		crr[u]=min(INF,ind+1);
		for(auto&e:adj[u]){
			if(e[0]!=p &&e[1]==0){
				ll v=e[0];
				ll cct=min(brr[v],crr[v]);
				ll ih=INF;
				for(ll i=1;i<arr[v].size();++i) ih=min(ih,arr[v][i]);
				ll cmd=min(ih,brr[v]);
				if(cmd!=INF) brr[u]=min(brr[u],1+ind-min(ih,cct)+cmd);
			}
            else if(e[1]==0){
                // ll v=e[0];
				// ll cct=min(brr[v],crr[v]);
				// ll ih=INF;
				// for(ll i=1;i<arr[v].size();++i) ih=min(ih,arr[v][i]);
				// ll cmd=min(ih,brr[v]);
                // brr[u]=min(brr[u],ind-min(ih,cct)+cmd);
            }
		}
	}
}

bool ischk(ll mid,ll k){
	li=mid;
	rec(1,0);
	ll rw=INF;
	for(ll i=1;i<arr[1].size();++i) rw=min(rw,arr[1][i]);
	return min(rw,brr[1])<=k;
}

void solve(){
	ll l=1,r=0;
	ll x=0,w=0,y=0,z=0;
	ll a=0,b=0,c=0,d=0;
	ll g=0,q=0,k=0;
	cin>>n>>k;
	for(ll i=1;i<=n;++i) adj[i].clear();
	for(ll i=0;i<n-1;++i){
		cin>>a>>b>>w;
		adj[a].push_back({b,w});
		adj[b].push_back({a,w});
	}
	r=n;
	res=n;
	while(l<=r){
		ll mid=l+(r-l)/2;
		if(ischk(mid,k)){
			res=mid;
			r=mid-1;
		}
        else l=mid+1;
	}
	cout<<res<<endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // sieve(MAX_N);
    // prec();
    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}