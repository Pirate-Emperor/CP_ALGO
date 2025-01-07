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
    cin >> n;
    vector<vector<int>> arr(n,vector<int> (n,0));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            cin >> x;
            arr[i][x-1]++;
        }
    }
    int i=0;
    vector<ar<int,100>> res;
    bool ev = true;
    while(i<n)
    {
        ev = true;
        while(ev && i<n)
        {
            for (int ij=0;ij<n;ij++)
            {
                if (arr[i][ij]>1) 
                {
                    ev = false;
                    break;
                }
            }
            if (ev) i++;
        }
        if (i==n) break;
        ar<int,100> temp;
        for (int j=i;j<n;j++)
        {
            for (int k=0;k<n;k++)
            {
                if (arr[j][k]>1)
                {
                    arr[j][k]--;
                    arr[(j+1)%n][k]++;
                    temp[j]=k;
                    break;
                }
            }
        }
        for (int j=0;j<i;j++)
        {
            for (int k=0;k<n;k++)
            {
                if (arr[j][k]>1)
                {
                    arr[j][k]--;
                    arr[(j+1)%n][k]++;
                    temp[j]=k;
                    break;
                }
            }
        }
        res.push_back(temp);
    }
    vector<ar<int,100>> st;
    ar<int,100> temp;
    for (int i=0;i<n;i++)
    {
        temp[i]=i;
    }
    st.push_back(temp);
    for (int k=1;k<n;k++)
    {
        ar<int,100> temp;
        int la = st.size()-1;
        for (int i=0;i<n;i++)
        {
            temp[i] = st[la][(i+1)%n];
        }
        st.push_back(temp);
        for (int i=st.size()-1;i>0;i--)
        {
            res.push_back(st[i]);
        }
    }
    m = res.size();
    cout << m << endl;
    for (int i=0;i<m;i++)
    {
        for (int j=0;j<n;j++)
        {
            cout << res[i][j]+1 << " ";
        }
        cout << endl;
    }
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