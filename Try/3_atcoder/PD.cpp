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
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
ll res=0;
vector<ll> arr,brr;
bool rec(ll u,ll v){
	for(ll i=0;i<m;++i){
        if(arr[i]!=u&&brr[i]!=u&&arr[i]!=v&&brr[i]!=v) return 0;
    }
	return 1;
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>m;
	arr.resize(m);
    brr.resize(m);
	for(int i=0;i<m;++i) cin>>arr[i]>>brr[i];
	a=arr[0];
    b=brr[0];
	bool chk1=true,chk2=true;
	for(k=0;k<m;++k) if(arr[k]!=a&&brr[k]!=a){
        chk1=false;
        break;
    }
	for(l=0;l<m;++l) if(arr[l]!=b&&brr[l]!=b){
        chk2=false;
        break;
    }
	if(chk1&&chk2){
        // res=2*n-4;
        // res=n-3+n+1;
        res=2*n-3;
    }
	else if(chk1){
		res=n-1;
		if(arr[k]!=a&& rec(b,arr[k])) res++;
		if(brr[k]!=a&&rec(b,brr[k])) res++;
	}
    else if(chk2){
		res=n-1;
		if(arr[l]!=b&& rec(a,arr[l])) res++;
		if(brr[l]!=b&&rec(a,brr[l])) res++;
	}
    else{
		set<pair<ll,ll>> st;
		st.insert({min(a,arr[k]),max(a,arr[k])});
		st.insert({min(a,brr[k]),max(a,brr[k])});
		st.insert({min(b,arr[l]),max(b,arr[l])});
		st.insert({min(b,brr[l]),max(b,brr[l])});
		for(auto p:st) if(rec(p.first,p.second)) res++;
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
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}