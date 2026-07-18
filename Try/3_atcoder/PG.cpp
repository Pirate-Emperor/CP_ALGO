// by Pirate_King

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const int MAX_L = 400+5;
const int MAX_K = 1e3+5;
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
ll arr[MAX_N];
vector<ll> brr[MAX_K];
vector<ll> crr[MAX_K];
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
    ll a=0,b=0,c=0,d=0,e=0;
    ll g=0,q=0,k=0;
    ll li=0,hi=0,u=0,v=0,tr=0;
    cin>>n>>q;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        brr[i/MAX_L].push_back(arr[i]);
    }
    for(int i=0;i<=n/MAX_L;i++){
        sort(all(brr[i]));
        crr[i].assign(brr[i].size()+1,0);
        for(int j=0;j<brr[i].size();j++) crr[i][j+1]=crr[i][j]+brr[i][j];
    }
    while(q--){
        cin>>c>>x>>l>>r>>k;
        c--;
        l--;
        r--;
        b=c/MAX_L;
        y=arr[c];
        arr[c]=x;
        brr[b].erase(lower_bound(all(brr[b]),y));
        brr[b].insert(lower_bound(all(brr[b]),x),x);
        crr[b].assign(brr[b].size()+1,0);
        for(int j=0;j<brr[b].size();j++) crr[b][j+1]=crr[b][j]+brr[b][j];
        vector<ll> drr;
        d=l/MAX_L;
        e=r/MAX_L;
        if(d==e){
            for(int i=l;i<=r;i++) drr.push_back(arr[i]);
        }
        else{
            for(int i=l;i<(d+1)*MAX_L;i++) drr.push_back(arr[i]);
            // for(int i=l;i<d*MAX_L;i++) drr.push_back(arr[i]);
            for(int i=e*MAX_L;i<=r;i++) drr.push_back(arr[i]);
        }
        sort(all(drr));
        vector<ll> err(drr.size()+1,0);
        for(int i=0;i<drr.size();i++) err[i+1]=err[i]+drr[i];
        z=err.back();
        for(int i=d+1;i<e;i++) z+=crr[i].back();
        if(z<k){
            cout<<"-1\n";
            continue;
        }
        li=1;
        hi=1e9;
        g=-1;
        while(li<=hi){
            ll mid=li+(hi-li)/2;
            w=0;a=0;
            u=lower_bound(all(drr),mid)-drr.begin();
            a+=drr.size()-u;
            // w+=err.back();
            w+=err.back()-err[u];
            for(int i=d+1;i<e;i++){
                v=lower_bound(all(brr[i]),mid)-brr[i].begin();
                a+=brr[i].size()-v;
                w+=crr[i].back()-crr[i][v];
                // w+=crr[i].back();
            }
            if(w>=k){
                g=mid;
                li=mid+1;
            }
            else hi=mid-1;
        }
        w=0;
        res=0;
        u=upper_bound(all(drr),g)-drr.begin();
        res+=drr.size()-u;
        // w+=err.back();
        w+=err.back()-err[u];
        for(int i=d+1;i<e;i++){
            v=upper_bound(all(brr[i]),g)-brr[i].begin();
            res+=brr[i].size()-v;
            w+=crr[i].back()-crr[i][v];
        }
        tr=k-w;
        tr=(tr>0)?(tr+g-1)/g:0;
        cout<<res+tr<<endl;
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