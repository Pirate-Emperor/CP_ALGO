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
    long double eps = 1e-6;
    long double sx1,sx2,sy1,sy2;
    long double tx1,tx2,ty1,ty2;
    cin >> sx1 >> sy1 >> tx1 >> ty1;
    cin >> sx2 >> sy2 >> tx2 >> ty2;
    long double dis1 = (tx1-sx1)*(tx1-sx1)+(ty1-sy1)*(ty1-sy1);
    long double dis2 = (tx2-sx2)*(tx2-sx2)+(ty2-sy2)*(ty2-sy2);
    if (dis1>dis2)
    {
        swap(dis1,dis2);
        swap(sx1,sx2);
        swap(sy1,sy2);
        swap(tx1,tx2);
        swap(ty1,ty2);
    }
    long double k1 = sqrt((tx1-sx1)*(tx1-sx1)+(ty1-sy1)*(ty1-sy1));
    long double k2 = sqrt((tx2-sx2)*(tx2-sx2)+(ty2-sy2)*(ty2-sy2));
    long double mx1,mx2,my1,my2;
    mx1 = (tx1-sx1)/k1;
    my1 = (ty1-sy1)/k1;
    mx2 = (tx2-sx2)/k2;
    my2 = (ty2-sy2)/k2;
    
    long double tc = (sx1-sx2)*(sx1-sx2) + (sy1-sy2)*(sy1-sy2);
    long double ta = (mx1-mx2)*(mx1-mx2) + (my1-my2)*(my1-my2);
    long double tb = (sx1-sx2)*(mx1-mx2) + (sy1-sy2)*(my1-my2);
    tb*=2;
    long double res=1000000.0;
    long double dist = sqrt((sx1-sx2)*(sx1-sx2)+(sy1-sy2)*(sy1-sy2));
    res=min(dist,res);
    dist = sqrt((tx1-tx2)*(tx1-tx2)+(ty1-ty2)*(ty1-ty2));
    res=min(dist,res);
    if (abs(ta)<eps) 
    {
        // cout << res << endl;
    }
    else
    {
        long double temx1=sx1,temy1=sy1,temx2=sx2,temy2=sy2;
        long double t = (-tb)/(2*ta);
        // cout << temx1+t*mx1 << " ";
        if (t>=eps && ((tx1>=sx1 && temx1+t*mx1<=tx1) || (tx1<sx1 && temx1+t*mx1>=tx1)) && ((ty1>=sy1 && temy1+t*my1<=ty1) || (ty1<sy1 && temy1+t*my1>=ty1))){
            // cout << t << " ";
            temx1+=t*mx1;
            temy1+=t*my1;
            temx2+=t*mx2;
            temy2+=t*my2;
            dist = sqrt((temx1-temx2)*(temx1-temx2)+(temy1-temy2)*(temy1-temy2));
            res = min(dist,res);
        }
        long double ti = sqrt(dis1);
        temx2=sx2+ti*mx2;
        temy2=sy2+ti*my2;
        long double tc = (tx1-temx2)*(tx1-temx2) + (ty1-temy2)*(ty1-temy2);
        long double ta = (-mx2)*(-mx2) + (-my2)*(-my2);
        long double tb = (tx1-temx2)*(-mx2) + (ty1-temy2)*(-my2);
        if (abs(ta)>=eps) 
        {
            long double temx1=sx1,temy1=sy1;
            long double t = (-tb)/(ta);
            if (t>=eps){
                temx1=tx1;
                temy1=ty1;
                temx2+=t*mx2;
                temy2+=t*my2;
                dist = sqrt((temx1-temx2)*(temx1-temx2)+(temy1-temy2)*(temy1-temy2));
                res = min(dist,res);
            }
        }
    }
    // long double temx1=sx1,temy1=sy1,temx2=sx2,temy2=sy2;
    // long double t=0;
    // while ((temx1+t*mx1<=tx1) && (temx2+t*mx2<=tx2) && (temy1+t*my1<=ty1) && (temy2+t*my2<=ty2))
    // {
    //     temx1+=t*mx1;
    //     temy1+=t*my1;
    //     temx2+=t*mx2;
    //     temy2+=t*my2;
    //     long double dist = sqrt((temx1-temx2)*(temx1-temx2)+(temy1-temy2)*(temy1-temy2));
    //     cout << setprecision(2) << dist << " ";
    //     res = min(dist,res);
    //     t++;
    // }
    // while ((temx1+t*mx1<=tx1) && (temy1+t*my1<=ty1))
    // {
    //     temx1+=t*mx1;
    //     temy1+=t*my1;
    //     long double dist = sqrt((temx1-temx2)*(temx1-temx2)+(temy1-temy2)*(temy1-temy2));
    //     cout << setprecision(2) << dist << " ";
    //     res = min(dist,res);
    //     t++;
    // }
    // while ((temx2+t*mx2<=tx2) && (temy2+t*my2<=ty2))
    // {
    //     temx2+=t*mx2;
    //     temy2+=t*my2;
    //     long double dist = sqrt((temx1-temx2)*(temx1-temx2)+(temy1-temy2)*(temy1-temy2));
    //     cout << setprecision(2) << dist << " ";
    //     res = min(dist,res);
    //     t++;
    // }
    cout << fixed << setprecision(15) << res << endl;
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