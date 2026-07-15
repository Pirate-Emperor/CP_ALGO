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
const ll LINF = 4e18;
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

ll recur(ll i){
    return par[i]==i?i:par[i]=recur(par[i]);
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n>>k;
    string arr;
    cin>>arr;
    for(char ch:arr) if(ch=='0') a++;
    b=n-a;
    if(a<k||b<k){
        cout<<arr<<"\n0\n";
        return;
    }
    
    if(a==k&&b==k){
        string brr=arr;
        for(char& ch:brr) ch=(ch=='0'?'1':'0');
        if(arr<=brr) cout<<arr<<"\n0\n";
        else cout<<brr<<"\n1\n";
        return;
    }
    string crr=string(a,'0')+string(b,'1');
    for(ll i=0;i<a;i++) if(arr[i]=='1') c++;
    if(!c){
        cout<<crr<<"\n0\n";
        return;
    }
    d=min(a,b);
    par.assign(d+2,0);
    dis.assign(d+1,-1);
    for(ll i=0;i<d+2;i++) par[i]=i;
    queue<ll> qu;
    qu.push(c);
    // queue<ll> qui;
    // qui.push(c);
    dis[c]=0;
    par[c]=recur(c+1);
    while(!qu.empty()){
        x=qu.front();
        qu.pop();
        if(!x) break;
        l=max(0ll,k-b+x);
        r=min(k,x);
        y=max(0ll,k-a+x);
        z=min(k,x);
        if(l>r||y>z) continue;
        w=x+k-(r+z);
        q=x+k-(l+y);
        // w=x+z-(r+k);
        // q=x+k-l+y;
        g=recur(w);
        while(g<=q){
            dis[g]=dis[x]+1;
            qu.push(g);
            par[g]=recur(g+1);
            g=recur(g);
        }
    }
    cout<<crr<<"\n"<<dis[0]<<"\n";
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