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
    long long l=0,r=0,x=0,w=0,y=0,z=0;
    long long a=nums.size(),b=0,c=0,d=0;
    long long g=0,q=0,k=0; 
    long long res=nums[0];
    vector<long long>brr(a*2,0),crr(a+1,0);
    for(x=0;x<a;++x) crr[x+1]=crr[x]+nums[x];
    for(b=0;b<a*2-1;++b){
        l=b/2;
        r=l+b%2;
        k=0;
        if(d>r){
            y=2*c-b;
            k=min(brr[y],d-r);
        }
        l-=k;r+=k;
        while(l>=0&&r<a&& nums[l]==nums[r]){
            ++k;
            // w+=nums[l];
            // if(l!=r) w+=nums[r];
            // if(w>res) res=w;
            --l;
            ++r;
        }
        brr[b]=k;
        if(r>d){
            d=r;
            c=b;
        }
        w=crr[r]-crr[l+1];
        if(w>res) res=w;
    }
    return res;
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