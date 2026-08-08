#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 5e5 + 5;
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
// vector<ll> arr,brr;
// bool rec(ll u,ll v){
// 	for(ll i=0;i<m;++i){
//         if(arr[i]!=u&&brr[i]!=u&&arr[i]!=v&&brr[i]!=v) return 0;
//     }
// 	return 1;
// }

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n>>q;
    vector<ll> arr(n+1),brr(n+1);
    bool chk=false;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        brr[arr[i]]=i;
    }
    while(q--){
        cin>>x;
        if(x==2) chk=!chk;
        else{
            cin>>y>>z;
            if(!chk){
                a=arr[y];
                b=arr[z];
                arr[y]^=arr[z];
                arr[z]^=arr[y];
                arr[y]^=arr[z];
                brr[a]=z;
                brr[b]=y;
            }
            else{
                a=brr[y];
                b=brr[z];
                brr[y]^=brr[z];
                brr[z]^=brr[y];
                brr[y]^=brr[z];
                arr[a]=z;
                arr[b]=y;
            }
        }
    }
    if(!chk){
        for(int i=1;i<=n;i++) cout<<arr[i]<<" ";
        cout<<endl;
    }
    else{
        for(int i=1;i<=n;i++) cout<<brr[i]<<" ";
        cout<<endl;
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