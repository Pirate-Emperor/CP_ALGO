// by Pirate-King

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const int MAX_K = 100+5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
const int OFF=40;
const int MDIF=100;
const int G=3;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l, ll r) {return uniform_int_distribution(l, r)(rng);}

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

string que(vector<ll> s){
    cout<<"? "<<s.size()<<" ";
    for(ll v:s){
        cout<<v<<" ";
    }
    cout<<"\n";
    cout.flush();
    string resu;
    cin>>resu;
    if(resu=="-1"||resu=="") exit(0);
    return resu;
}

void recur(vector<ll> a,vector<ll> b){
    if(b.empty()) return;
    if(edges.size()==n-1) return;
    if(a.size()==1){
        for(ll v:b){
            edges.push_back({a[0],v});
            if(edges.size()==n-1) return;
        }
        return;
    }
    ll mid=a.size()/2;
    vector<ll> a1(a.begin(),a.begin()+mid);
    vector<ll> a2(a.begin()+mid,a.end());
    vector<ll> arr=a1;
    arr.insert(arr.end(),all(b));
    string resu=que(arr);
    vector<ll> b1;
    for(ll i=0;i<b.size();i++) if(resu[a1.size()+i]=='0') b1.push_back(b[i]);
    set<ll> mpi(all(b1));
    vector<ll> bo2;
    for(ll v:b) if(!mpi.count(v)) bo2.push_back(v);
    vector<ll> b2=bo2;
    bool chk=(b1.size()>0&&bo2.size()>0);
    if(chk){
        vector<ll> brr=a2;
        brr.insert(brr.end(),all(b1));
        string crr=que(brr);
        for(ll i=0;i<b1.size();i++) if(crr[a2.size()+i]=='0') b2.push_back(b1[i]);
    }
    else if(b1.empty()){
        // vector<ll> brr=a2;
        // brr.insert(brr.end(),all(b));
        // string crr=que(brr);
        // for(ll i=0;i<b1.size();i++) if(crr[a2.size()+i]=='0') b2.push_back(b1[i]);
    }
    else if(bo2.empty()){
        vector<ll> brr=a2;
        brr.insert(brr.end(),all(b));
        string crr=que(brr);
        for(ll i=0;i<b.size();i++) if(crr[a2.size()+i]=='0') b2.push_back(b[i]);
    }
    if(b1.size()) recur(a1,b1);
    if(b2.size()) recur(a2,b2);
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    edges.clear();
    vector<ll> arr(n);
    for(ll i=0;i<n;i++) arr[i]=i+1;
    for(ll i=min(n-1,MAX_K);i>0;--i) swap(arr[i],arr[rand(0,i)]);
    vector<vector<ll>> col;
    vector<ll> crr=arr;
    while(crr.size()){
        string resu=que(crr);
        vector<ll> v1,ncrr;
        for(ll i=0;i<crr.size();i++){
            if(resu[i]=='1') v1.push_back(crr[i]);
            else ncrr.push_back(crr[i]);
        }
        col.push_back(v1);
        crr=ncrr;
    }
    for(ll i=0;i<col.size();i++){
        for(ll j=i+1;j<col.size();j++){
            if(edges.size()==n-1) break;
            vector<ll> u=col[i],v=col[j];
            if(u.size()>v.size()) swap(u,v);
            vector<ll> brr=u;
            brr.insert(brr.end(),all(v));
            string resu=que(brr);
            vector<ll> drr;
            for(ll ij=0;ij<v.size();ij++) if(resu[u.size()+ij]=='0') drr.push_back(v[ij]);
            if(drr.size()) recur(u,drr);
        }
        if(edges.size()==n-1) break;
    }
    cout<<"!\n";
    for(auto e:edges){
        cout<<e[0]<<" "<<e[1]<<"\n";
        cout.flush();
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
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}