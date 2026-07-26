// by Pirate-King

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
// void recur(int u, int dep)
// {
//     vis[u]=1;
//     for (int it: adj[u])
//     {
//         if (vis[it]==0) 
//         {
//             par[it]=u;
//             recur(it, dep+1);
//         }
//     }
//     dis[u]=dep;
// }

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
	if(n==1){
        cout<<1<<endl;
        return;
    }
	vector<ll> arr(n),brr(n+1,0),crr(n+1,0);
	bool chk=true;
    bool check=false;
	for(ll i=0;i<n-1;++i){
		cin>>arr[i];
		if(arr[i]<1||arr[i]>=n){
            chk=false;
            continue;
        }
		brr[arr[i]]++;
		a=max(a,arr[i]);
		if(i>0){
			if(arr[i]<arr[i-1]) check=true;
			if(arr[i]>arr[i-1]&& check) chk=false;
			if(arr[i]!=arr[i-1]&& crr[arr[i]]){
                if (crr[arr[i]]>0) chk=false;
                else{
                    // check=false;
                }
            }
		}
		crr[arr[i]]=1;
	}
	if(!chk||a!=n-1){
        cout<<0<<endl;
        return;
    }
	res=2;
    a=0;
	for(x=n-1;x>=1;--x){
		if(brr[x]>0) a+=brr[x]-1;
		else{
			if(a<=0){
                res=0;
                break;
            }
			res=(res*a)%MOD;
			a--;
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
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}