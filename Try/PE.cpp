#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
// struct st{
//     ll id;
//     mutable ll len,t;
//     bool operator < (const st &A) const { return id<A.id;} 
// };

// ll gcd(ll a, ll b) {
//     return b ? gcd(b, a % b) : a;
// }

// ll qexp(ll a, ll b, ll m) {
//     ll res = 1;
//     while (b) {
//         if (b % 2) res = res * a % m;
//         a = a * a % m;
//         b /= 2;
//     }
//     return res;
// }

// vector<int> briarr;
// void briCnt(int v)
// {
//     briarr.push_back(v);
// }
int n;
// vector<int> adj[MAX_N];

// vector<bool> visited;
// vector<int> tin, low;
// int timer;

// void dfs(int v, int p = -1) {
//     visited[v] = true;
//     tin[v] = low[v] = timer++;
//     int children=0;
//     for (int to : adj[v]) {
//         if (to == p) continue;
//         if (visited[to]) {
//             low[v] = min(low[v], tin[to]);
//         } else {
//             dfs(to, v);
//             low[v] = min(low[v], low[to]);
//             if (low[to] >= tin[v] && p!=-1)
//                 briCnt(v);
//             ++children;
//         }
//     }
//     if(p == -1 && children > 1)
//         briCnt(v);
// }

// void find_art() {
//     timer = 0;
//     visited.assign(n, false);
//     tin.assign(n, -1);
//     low.assign(n, -1);
//     for (int i = 0; i < n; ++i) {
//         if (!visited[i])
//             dfs (i);
//     }
// }

// ll ct(ll ch,ll x,ll y,ll a,ll b,ll s) {
//     ll cv=s-ch;
//     ll h=max(x,abs(ch));
//     ll v=max(y,abs(cv));
//     ll na=(h+v+ch-cv)/2;
//     ll nb=(h+v-ch+cv)/2;
//     return (a*na)+(b*nb);
// }

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    vector<int> arr(n+1),brr(n+1);
    for(int i=1;i<=n;i++) cin>>arr[i];
    for(int i=1;i<=n;i++) cin>>brr[i];
    vector<int> cyc(n+1),pos(n+1);
    vector<vector<int>> el;
    vector<bool> vs(n+1,0);
    for(int i=1;i<=n;i++){
        if(!vs[i]){
            int cur=i;
            vector<int> ce;
            while(!vs[cur]){
                vs[cur]=1;
                cyc[cur]=el.size();
                pos[cur]=ce.size();
                ce.push_back(cur);
                cur=arr[cur];
            }
            el.push_back(ce);
        }
    }
    int nc=el.size();
    vector<int> mt(nc,-1),mf(nc,-1),off(nc,-1);
    bool check=1;
    for(int i=1;i<=n;i++){
        if(brr[i]!=-1){
            l=cyc[i];
            r=cyc[brr[i]];
            if(el[l].size()!=el[r].size()){
                check=0;
                break;
            }
            int len=el[l].size();
            int ro=(pos[brr[i]]-pos[i]+len)%len;
            // if(mt[l]!=-1&&mt[l]!=r&&mt[r]!=l)check=0;
            if(mt[l]!=-1&&mt[l]!=r)check=0;
            if(mf[r]!=-1&&mf[r]!=l)check=0;
            if(mt[l]==r&&off[l]!=ro) check=0;
            if(!check)break;
            mt[l]=r;
            mf[r]=l;
            off[l]=ro;
        }
    }
    if(!check){
        cout<<"NO\n";
        return;
    }
    map<int,int> s_c,t_c;
    for(int i=0;i<nc;i++){
        if(mt[i]==-1)s_c[el[i].size()]++;
        if(mf[i]==-1)t_c[el[i].size()]++;
    }
    if(s_c!=t_c){
        cout<<"NO\n";
        return;
    }
    map<int,vector<pair<int,int>>> unm;
    for(int i=0;i<nc;i++){
        if(mf[i]==-1){
            int me=el[i][0];
            for(int v:el[i])me=min(me,v);
            unm[el[i].size()].push_back({me,i});
        }
    }
    for(auto& p:unm) sort(p.second.rbegin(),p.second.rend());
    for(int i=1;i<=n;i++){
        int cy=cyc[i];
        if(mt[cy]==-1){
            z=el[cy].size();
            if(unm[z].empty()){
                check=0;
                break;
            }
            int r=unm[z].back().second;
            unm[z].pop_back();
            // int me=n+1,mp=-1;
            int me=n+2,mp=-1;
            for(int j=0;j<z;j++){
                if(el[r][j]<me){
                    me=el[r][j];
                    mp=j;
                }
            }
            mt[cy]=r;
            mf[r]=cy;
            off[cy]=(mp-pos[i]+z)%z;
        }
    }
    if(!check){
        cout<<"NO\n";
        return;
    }
    vector<int> resu(n+1);
    for(int i=0;i<nc;i++){
        int r=mt[i],z=el[i].size();
        for(int j=0;j<z;j++){
            int v=el[i][j];
            int tp=(j+off[i])%z;
            resu[v]=el[r][tp];
        }
    }
    for(int i=1;i<=n;i++){
        if(brr[i]!=-1&&brr[i]!=resu[i]) check=0;
    }
    if(!check) cout<<"NO\n";
    else{
        cout<<"YES\n";
        for(int i=1;i<=n;i++)cout<<resu[i]<<" ";
        cout<<endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
        
    }
}