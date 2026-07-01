// by Pirate-Emperor

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define long long long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const int MAX_K = 360+5;
const long long MOD = 998244353;
const long long INF = 1e9;
const long long LINF = 1e18;
const int K = 11;
const int OFF=40;
const int MDIF=100;
const int G=3;

long long gcd(long long a, long long b){
    return b?gcd(b,a%b):a;
}
 
long long qexp(long long a, long long b, long long m){
    long long res=1;
    while(b){
        if (b%2)res=res*a%m;
        a=a*a%m;
        b/=2;
    }
    return res;
}

long long n, m;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<long long> vis;
vector<long long> dis;
vector<long long> par;
long long res=0;
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

vector<vector<int>>solve(vector<vector<int>>&occupiedIntervals,int freeStart,int freeEnd){
    long long l=0,r=0,x=0,w=0,y=0,z=0,a=0,b=0,c=0,d=0,g=0,q=0,k=0;
    vector<vector<int>> res;
    if(occupiedIntervals.empty()) return res;
    sort(occupiedIntervals.begin(),occupiedIntervals.end());
    vector<vector<int>> resu;
    x=occupiedIntervals[0][0];
    y=occupiedIntervals[0][1];
    for(w=1;w<occupiedIntervals.size();++w){
        if(occupiedIntervals[w][0]<=y+1) y=max(y,(long long)occupiedIntervals[w][1]);
        else{
            res.push_back({(int)x,(int)y});
            x=occupiedIntervals[w][0];
            y=occupiedIntervals[w][1];
        }
    }
    res.push_back({(int)x,(int)y});
    for(auto&i:res){
        l=i[0];
        r=i[1];
        if(r<freeStart||l>freeEnd) resu.push_back(i);
        else{
            if(l<freeStart) resu.push_back({(int)l,freeStart-1});
            if(r>freeEnd) resu.push_back({freeEnd+1,(int)r});
        }
    }
    return resu;
}

void solve() {
    long long l=0,r=0;
    long long x=0,w=0,y=0,z=0;
    long long a=0,b=0,c=0,d=0;
    long long g=0,q=0,k=0;
    cin >> n >> k;
    vector<int> occupiedIntervals(n);
    for (int i=0;i<n;i++)
    {
        cin >> occupiedIntervals[i];
    }
    auto brr = subsequenceSumAfterCapping(occupiedIntervals, k);
    for (int i=0;i<n;i++)
    {
        cout << brr[i] << " ";
    }
    cout << endl;
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