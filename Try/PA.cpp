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
    cin >> n >> m;
    string s;
    cin >> s;
    vector<pair<int,int>> path;
    map<ar<int,2>,int> mpi;
    a=0;
    b=0;
    path.push_back({a,b});
    mpi[{a,b}]=0;
    for (int i=0;i<n+m-2;i++)
    {
        if (s[i]=='D') a++;
        else b++;
        path.push_back({a,b});
        mpi[{a,b}]=i+1;
    }
    vector<int> sola(n+m-1,0);
    vector<vector<int>> arr(n,vector<int>(m));
    int sum=0;
    vector<int> col(m,0), row(n,0);
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            cin >> arr[i][j];
            sum+=arr[i][j];
            row[i]+=arr[i][j];
            col[j]+=arr[i][j];
        }
    }
 
    vector<ar<int,2>> inter(n+m-1, {LINF,LINF});
    a=0;
    b=0;
    
    for (int i=0;i<n+m-2;i++)
    {
        if (s[i]=='D') 
        {
            ar<int,2> temp = {0,0};
            for (int j=0;j<m;j++)
            {
                if (j==b) break;
                if (mpi.find({a,j})!=mpi.end()) 
                {
                    temp[0] += inter[mpi[{a,j}]][0];
                    temp[1] += inter[mpi[{a,j}]][1];
                }
            }
            ar<int,2> nex = {1-temp[0],-row[a]-temp[1]};
            inter[mpi[{a,b}]]=nex;
            a++;
            
        }
        else 
        {
            ar<int,2> temp = {0,0};
            for (int j=0;j<n;j++)
            {
                if (j==a) break;
                if (mpi.find({j,b})!=mpi.end()) 
                {
                    temp[0] += inter[mpi[{j,b}]][0];
                    temp[1] += inter[mpi[{j,b}]][1];
                }
            }
            ar<int,2> nex = {1-temp[0],-col[b]-temp[1]};
            inter[mpi[{a,b}]]=nex;
            b++;
            
        }
    }
    ar<int,2> temp = {0,0};
    for (int j=0;j<m;j++)
    {
        if (j==b) break;
        if (mpi.find({a,j})!=mpi.end()) 
        {
            temp[0] += inter[mpi[{a,j}]][0];
            temp[1] += inter[mpi[{a,j}]][1];
        }
    }
    ar<int,2> nex = {1-temp[0],-row[a]-temp[1]};
    inter[mpi[{a,b}]]=nex;

    temp = {0,0};
    for (int j=0;j<n;j++)
    {
        if (j==a) break;
        if (mpi.find({j,b})!=mpi.end()) 
        {
            temp[0] += inter[mpi[{j,b}]][0];
            temp[1] += inter[mpi[{j,b}]][1];
        }
    }
    nex = {1-temp[0],-col[b]-temp[1]};
    nex[0]-=inter[mpi[{a,b}]][0];
    nex[1]-=inter[mpi[{a,b}]][1];

    int val = 0;
    if (nex[0]!=0) val = -nex[1]/nex[0];

    // cout << val << endl;
    for (int i=0;i<n+m-1;i++)
    {
        // cout << inter[i][0] << " " << inter[i][1] << " | ";
        sola[i]=inter[i][0]*val+inter[i][1];
        int a = path[i].first;
        int b = path[i].second;
        arr[a][b]=sola[i];
    }
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
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