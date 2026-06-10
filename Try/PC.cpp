#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18+100;
const int K = 11;
struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

int n, m, x;
vector<array<int,2>> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> curS;
int res=0;
void recur(int N, int node, int cur)
{
    if (cur>(N-1)/2 || node>=N) return;
    for (int i=node;i<N;i++)
    {
        curS[i]=1;
        int temp=0;
        for (int j=0;j<m;j++)
        {
            temp+=curS[edges[j][0]]!=curS[edges[j][1]];
        }
        res=max(temp,res);
        recur(N, i+1,cur+1);
        curS[i]=0;
    }
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>k;
    string s;
    cin>>s;
    vector<int> pl,pr;
    for(int i=0;i<n;++i) {
        if(s[i]=='(') pl.push_back(i);
        else pr.push_back(i);
    }
    int mp=n+1;
    string bm="";
    for(int a=0;a<=k;++a){
        int b=k-a;
        if(a>pl.size() || b>pr.size()) continue;
        string cm(n,'0');
        for(int i=0;i<a;++i)cm[pl[i]]='1';
        for(int i=0;i<b;++i)cm[pr[pr.size()-1-i]]='1';
        int cp=0,oc=0;
        for(int i=0;i<n;++i){
            if(cm[i]=='1') continue;
            if(s[i]=='(') oc++;
            else if(s[i]==')'&&oc>0){
                oc--;cp++;
            }
        }
        if(cp<mp){
            mp=cp;
            bm=cm;
        }
    }
    cout<<bm<<endl;
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