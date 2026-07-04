// by Pirate-Emperor

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
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

ll solve(string word1, string word2, string target){
    long long l=0,r=0,x=0,w=1e9+7,y=0,z=0;
    long long a=0,b=0,c=0,d=0;
    long long g=0,q=0,k=0; 
    a=word1.length();
    b=word2.length();
    c=target.length();
    long long resu=0;
    vector<vector<long long>>arr(a+1,vector<long long>(b+1,0));
    vector<vector<long long>>brr(a+1,vector<long long>(b+1,0));
    vector<vector<long long>>crr(a+1,vector<long long>(b+1,0));
    vector<vector<long long>>drr(a+1,vector<long long>(b+1,0));
    arr[0][0]=1;
    for(l=0;l<c;++l){
        for(x=0;x<=a;++x){
        for(y=0;y<=b;++y){
            brr[x][y]=0;
            crr[x][y]=arr[x][y];
            if(x>0) crr[x][y]=(crr[x][y]+crr[x-1][y])%w;
            drr[x][y]=arr[x][y];
            if(y>0) drr[x][y]=(drr[x][y]+drr[x][y-1])%w;
        }
        }
        // for(x=0;x<a;++x) if(word1[x]==target[l]) for(y=0;y<=b;++y) brr[x][y+1]=(brr[x][y+1]+crr[x][y])%w;
        for(x=0;x<a;++x) if(word1[x]==target[l]) for(y=0;y<=b;++y) brr[x+1][y]=(brr[x+1][y]+crr[x][y])%w;
        for(y=0;y<b;++y) if(word2[y]==target[l]) for(x=0;x<=a;++x) brr[x][y+1]=(brr[x][y+1]+drr[x][y])%w;
        arr=brr;
    }
    for(x=1;x<=a;++x) for(y=1;y<=b;++y) resu=(resu+arr[x][y])%w;
    return resu;
}

void solve() {
    long long l=0,r=0;
    long long x=0,w=0,y=0,z=0;
    long long a=0,b=0,c=0,d=0;
    long long g=0,q=0,k=0;
    string s1,s2,s3;
    cin >>s1>>s2>>s3;

    ll res = solve(s1,s2,s3);
    cout << res << endl;
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