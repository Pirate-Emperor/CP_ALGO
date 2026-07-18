// by Pirate_King

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
ll arr[MAX_N],brr[MAX_N],st[MAX_N*4],resu[MAX_N*4],q1[MAX_N],q2[MAX_N],q3[MAX_N],sz=1;
vector<ll> val;

void rec(ll i,ll d){
	ll p=sz+i;
	st[p]+=d;
	resu[p]=st[p]?st[p]+val[i]:-LINF;
	for(p/=2;p>0;p/=2){
		st[p]=st[p*2]+st[p*2+1];
		resu[p]=max(resu[p*2+1],resu[p*2]+st[p*2+1]);
	}
}

void solve(){
	ll l=0,r=0;
	ll x=0,w=0,y=0,z=0;
	ll a=0,b=0,c=0,d=0;
	ll g=0,q=0,k=0;
	cin>>n>>q;
	for(ll i=1;i<=n;++i) cin>>arr[i];
	for(ll i=1;i<=n;++i){
        cin>>brr[i];
        val.push_back(brr[i]);
    }
	for(ll i=0;i<q;++i){
        cin>>q1[i]>>q2[i]>>q3[i];
        if(q1[i]==2) val.push_back(q3[i]);
    }
	sort(all(val));
	val.erase(unique(all(val)),val.end());
	m=val.size();
	while(sz<m) sz*=2;
    for(ll i=0;i<2*sz;++i) resu[i]=-LINF;
	for(ll i=1;i<=n;++i) rec(lower_bound(all(val),brr[i])-val.begin(),arr[i]);
	for(ll i=0;i<q;++i){
		a=lower_bound(all(val),brr[q2[i]])-val.begin();
		if(q1[i]==1){
			rec(a,q3[i]-arr[q2[i]]);
			arr[q2[i]]=q3[i];
		}
        else{
			rec(a,-arr[q2[i]]);
			brr[q2[i]]=q3[i];
			rec(lower_bound(all(val),brr[q2[i]])-val.begin(),arr[q2[i]]);
		}
		cout<<resu[1]<<endl;
	}
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