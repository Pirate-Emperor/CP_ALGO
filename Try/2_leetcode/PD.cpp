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

vector<long long> solve(int n, vector<vector<int>>& edges, int power, vector<int>& cost, int source, int target){
    long long l=0,r=0,x=0,w=0,y=0,z=0,a=0,b=0,c=0,d=0;
    long long g=0,q=0,k=0; 
    vector<vector<array<long long,2>>> brr(n);
    for(auto&e:edges) brr[e[0]].push_back({e[1],e[2]});
    priority_queue<array<long long,3>> pq;
    vector<long long>arr(n,-1);
    pq.push({0,power,source});
    vector<long long>res={-1,-1};
    while(!pq.empty()){
        array<long long,3> cur=pq.top();
        pq.pop();
        long long nt=cur[0],p=cur[1],u=cur[2];
        if(u==target) return{-nt,p};
        if(p<=arr[u]) continue;
        arr[u]=p;
        if(p<cost[u]) continue;
        for(auto&v:brr[u]) pq.push({nt-v[1],p-cost[u],v[0]});
    }
    return res;
}

void solve() {
    long long l=0,r=0;
    long long x=0,w=0,y=0,z=0;
    long long a=0,b=0,c=0,d=0;
    long long g=0,q=0,k=0;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    auto brr = subsequenceSumAfterCapping(arr, k);
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