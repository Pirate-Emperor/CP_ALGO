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

ll recur(vector<ll>&arr, vector<ll>&tmp, ll l, ll r){
    if(l>=r) return 0;
    ll m=l+(r-l)/2;
    ll res=recur(arr,tmp,l,m)+recur(arr,tmp,m+1,r);
    ll i=l,j=m+1,k=l;
    while(i<=m&&j<=r){
        if(arr[i]<=arr[j]) tmp[k++]=arr[i++];
        else{
            tmp[k++]=arr[j++];
            res+=(m-i+1);
        }
    }
    while(i<=m) tmp[k++]=arr[i++];
    while(j<=r) tmp[k++]=arr[j++];
    for(i=l;i<=r;i++) arr[i]=tmp[i];
    return res;
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n;
    vector<ll>arr(n),brr(n),crr(n*n,0);
    for(int i=0;i<n;i++) cin>>arr[i];
    for(int i=0;i<n;i++) cin>>brr[i];
    if(n==1){
        cout<<0<<endl;
        return;
    }
    vector<ll> tmpa(n);
    vector<ll>arrc=arr;
    x=recur(arrc,tmpa,0,n-1);
    sort(all(brr));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) crr[i*n+j]=arr[i]*brr[j];;
    vector<ll>tmpc(n*n);

    y=recur(crr,tmpc,0,n*n-1);
    z=(y-n*x)%MOD;
    if(z<0) z+=MOD;
    w=(n*(n-1))%MOD;
    res=(z*qexp(w,MOD-2,MOD))%MOD;
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