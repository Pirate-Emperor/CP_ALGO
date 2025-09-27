// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e3 + 5;
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

int n, m, x;

bool checkGrid(vector<string> grid)
{
    for (int i=0;i<grid.size();i++)
    {
        for (int j=0;j<grid[i].size();j++)
        {
            if (grid[i][j]=='.')
            {
                grid[i][j]='x';
                if (i>0) grid[i-1][j]='x';
                if (j>0) grid[i][j-1]='x';
                if (i>0 && j>0) grid[i-1][j-1]='x';
            }
        }
    }
    for (int i=0;i<grid.size()-1;i++)
    {
        for (int j=0;j<grid[i].size()-1;j++)
        {
            if (grid[i][j]!='x') return false;
        }
    }
    return true;
}

bool permute(vector<string> grid, int k)
{
    if (k==0)
    {
        return checkGrid(grid);
    }
    for (int i=1;i<grid.size()-1;i++)
    {
        for (int j=1;j<grid[i].size()-1;j++)
        {
            if (grid[i][j]=='#')
            {
                grid[i][j]='.';
                if (permute(grid,k-1)) return true;
                grid[i][j]='#';
            }
        }
    }
    
    return false;

}
void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=-LINF,b=0,c=-LINF,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    vector<ll> arr(n);
    map<ll,ll> mpi;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        mpi[arr[i]]++;
    }
    m = mpi.size();
    vector<array<ll,2>> brr(m);
    map<array<ll,2>,ll,greater<array<ll,2>>> map_occ;
    map<ll,ll,greater<ll>> map_ele;
    for (auto it: mpi)
    {
        brr[i]={it.first,it.second};
        map_occ[{it.second,it.first}]=1;
        map_ele[it.second];
    }
    while(map_occ.begin()->first[0]>1)
    {
        auto it = map_occ.begin();
        map_occ.erase(it->first);
        auto it_el = map_ele.lower_bound(it->first[1]);
        auto it_el_nsml = map_ele.lower_bound(it->first[1]+1);
    }
    return;
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