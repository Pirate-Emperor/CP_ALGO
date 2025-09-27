// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

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

vector<int> briarr;
void briCnt(int v)
{
    briarr.push_back(v);
}
int n;
vector<int> adj[MAX_N];

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                briCnt(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        briCnt(v);
}

void find_art() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i);
    }
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    ll v=0,m=0,x=0;
    cin >> a >> b;
    const int MAX_L = 5e3+100;
    int brr[MAX_L];
    vector<ll> prime;
    memset(brr,0,sizeof(brr));
    int sqrtn=(int)sqrt(MAX_L);
    for(int i=3; i<=sqrtn; i+=2)
    {
        if(brr[i]==0){
            for(int j=i*i; j<MAX_L; j+=i+i){
                brr[j]=1;
            }
        }
    }
    prime.push_back(2);
    for(int i=3; i<MAX_L; i+=2){
        if(brr[i]==0)
            prime.push_back(i);
    }
    while(a--)
    {
        cin >> n;
        c=0;
        vector<ll> arr(n);
        map<int,int> mpi;
        for (int i=0;i<n;i++)
        {
            cin >> arr[i];
            c+=arr[i];
            mpi[arr[i]]--;
        }
        mpi[c]++;
        vector<ll> primset(prime.size());
        for (auto it: mpi)
        {
            if (it.first>1)
            {
                // cout << it.first << " ";
                for (int j=0;j<prime.size();j++)
                {
                    if (prime[j]>it.first) break;
                    else 
                    {
                        ll temp=0;
                        ll tem = prime[j];
                        while(tem<=it.first)
                        {
                            temp+=it.first/tem;
                            tem*=prime[j];
                        }
                        primset[j]+=temp*it.second;
                    }
                }
            }
        }
        ll res=1;
        for (int i=0;i<prime.size();i++)
        {
            if (primset[i]==0) continue;
            else 
            {
                // cout << prime[i] << " " << primset[i] << endl;
                res = (res*qexp(prime[i],abs(primset[i]),b))%b;
            } 
        }
        cout << res << endl;
    }
    
    
    return;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
        
    }
}