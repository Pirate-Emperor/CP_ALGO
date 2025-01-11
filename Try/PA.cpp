// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

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
vector<int> adj[MAX_N];
int vis[MAX_N];

void solve() {
    ll n=0,m=0,l=0,r=0,k=0;
    ll w=0,x=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0;
    cin >> n >> m >> a >> b;
    vector<int> arr;
    map<int,int> mpi, bad;
    bool check=true;
    for (int i=0;i<m;i++)
    {
        cin >> x >> y;
        if (y-x+1>20)
        {
            check=false;
        }
        else
        {
            for (int j=x;j<=y;j++)
            {
                bad[j]=1;
                
            }
        }
    }
    if (check==false)
    {
        cout << "No\n";
        return;
    }
    for (auto it: bad)
    {
        arr.push_back(it.first);
    }
    mpi[n]=1;
    while(true)
    {
        // cout << mpi.begin()->first << " ";
        map<int,int> tmp;
        for (auto it: mpi)
        {
            int fit = max(1LL,it.first-a);
            int lit = max(1LL,it.first-b);
            for (int i=lit;i<=fit;i++) 
            {
                if (bad.find(i)==bad.end()) tmp[i]=1;
            }
        }
        mpi.clear();
        for (auto it: tmp)
        {
            mpi[it.first]=1;
            if (mpi.size()>=20) break;
        }
        if (mpi.size()==0) 
        {
            check=false;
            break;
        }
        if (mpi.begin()->first==1) break;
        if (mpi.begin()->first+19 == mpi.rbegin()->first)
        {
            int temp = mpi.begin()->first;
            int val = temp-1;
            int fir = upper_bound(arr.begin(),arr.end(),val) - arr.begin();
            if (fir==0) return;
            fir--;
            if (temp-arr[fir]>20) 
            {
                auto tm = mpi;
                mpi.clear();
                for (int ji=0;ji<20;ji++)
                {
                    mpi[arr[fir]+ji+1]=1;
                }
            }
        }
        
        
    }
    if (check) cout << "Yes\n";
    else cout << "No\n";
    
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