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

void recur(){
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n>>k;
    vector<ll> arr(n,0),brr;
    b=1;
    while(b*2<=n) b*=2;
    c=b*2;
    if(k>=c||(n==b &&k<n)){
        cout<<"NO\n";
        return;
    }
    cout<<"YES\n";
    arr[n-1]=n;
    y=k^n;
    if(n>1){
        if(y<=n-1) arr[n-2]=y;
        else{
            arr[n-2]=b;
            arr[n-3]=y^b;
        }
    }
    vector<bool> chk(n,false);
    x=0;
    for(ll i=0;i<n;i++) if(arr[i]>x){
        chk[x]=true;
        x=arr[i];
    }
    for(ll i=0;i<n;i++) if(!chk[i]) {
        // if (i && arr[i]>x) brr.pop_back();
        brr.push_back(i);
    }
    vector<ll> resu(n);
    x=0;
    for(ll i=0;i<n;i++){
        if(arr[i]>x){
            resu[i]=x;
            x=arr[i];
        }
        else{
            resu[i]=brr.back();
            brr.pop_back();
        }
    }
    for(ll i=0;i<n;i++) cout<<resu[i]<<" ";
    cout<<endl;
} 

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    if(cin>>t){
        while(t--)solve();
    }
    return 0;
}