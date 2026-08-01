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

ll rec(ll x){
	if(par[x]==x)return x;
	return par[x]=rec(par[x]);
}

void solve(){
	ll l=0,r=0;
	ll x=0,w=0,y=0,z=0;
	ll a=0,b=0,c=0,d=0;
	ll g=0,q=0,k=0;
	cin>>n;
	vector<ll> arr(n);
	m=0;
	for(int i=0;i<n;i++){
		cin>>arr[i];
		if(arr[i]>m) m=arr[i];
	}
	if(n==1){
		cout<<0<<endl;
		return;
	}
	vector<ll> crr(m+1,0);
	for(int i=0;i<n;i++) crr[arr[i]]++;
	par.assign(m+1,0);
	for(int i=0;i<=m;i++) par[i]=i;
	res=0;
	for(int i=1;i<=m;i++) if(crr[i]>0) res+=(crr[i]-1)*i;
	for(int i=m;i>=1;i--){
		a=-1;
		for(k=1;i*k<=m;k++){
			x=i*k;
			if(crr[x]>0){
				if(a==-1)a=x;
				else{
					b=rec(a);
					c=rec(x);
					if(b!=c){
						par[b]=c;
						res+=i;
					}
				}
			}
		}
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