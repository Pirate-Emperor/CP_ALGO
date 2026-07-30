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
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
ll res=0;

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    res=0;
    cin>>n;
    vector<int> arr(n+1);
    for(int i=1;i<=n;++i) cin>>arr[i];
    sort(arr.begin()+1,arr.end());
    res=LINF;
    for(l=2;l<n;++l){
        for(r=l;r<n;++r){
            // res=min(res,max(2*arr[r]-arr[1]-2*arr[r+1],arr[l-1]+arr[n]-arr[l]));
            res=min(res,max(2*arr[r]-arr[1]-arr[r+1],arr[l-1]+arr[n]-2*arr[l]));
        }
    }
    for(l=1;l<=n;++l){
        for(r=1;r<=l+1 &&r<=n;++r){
            for(int j=0;j<3;++j){
                if(j==1){ 
                    y=-1; 
                    a=2*arr[n]-arr[1]; 
                    b=arr[l]-2*arr[r]; 
                    // c=(a-b)/4; 
                    c=(a-b)/2; 
                }
                else if(!j){ 
                    y=2; 
                    a=-(arr[1]+arr[r]); 
                    // b=arr[l]+arr[n]-1; 
                    b=arr[l]+arr[n]; 
                    c=(b-a)/4; 
                    // c=(b-a)/2; 
                }
                else{ 
                    y=-1; 
                    // a=1*arr[l]-arr[r]; 
                    a=2*arr[l]-arr[r]; 
                    b=arr[n]-2*arr[1]; 
                    c=(a-b)/2; 
                }
                k=lower_bound(arr.begin()+1,arr.end(),c)-arr.begin();
                for(int i=k-1;i<=k+1;++i){
                    if(i>0&&i<=n) res=min(res,max(y*arr[i]+a,b-y*arr[i]));
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
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}