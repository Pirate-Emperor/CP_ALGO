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
    ll x=0,w=0,y=0,z=0;
    ll b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    vector<int> arr(n),h(n),s(n);
    for(int i=0;i<n;i++) cin>>arr[i]>>h[i]>>s[i];
    vector<pair<int,int>> S;
    S.push_back({1,1});

    for(int i=0;i<n;i++) {
        int A=arr[i],H=h[i],tr=s[i];
        if(H<=0) H=1;
        vector<pair<int,int>> val;
        if(A==0) {
            val=S;
        } 
        else {
            for(auto p:S) {
                int L=p.first,R=p.second,P=L;
                if(tr>0) {
                    int psk=(H-1)/tr;
                    if(P<=psk) P=psk+1;
                } else {
                    P=R+1;
                }

                while(P<=R) {
                    int cmx=tr/A;
                    if(cmx>0) {
                        int pth=(H+cmx-1)/cmx;
                        if(P>=pth) {
                            val.push_back({P,R});
                            break;
                        }
                    }
                    int C=(H+P-1)/P;
                    int pmx=R;
                    if(C>1) {
                        int mxc=(H-1)/(C-1);
                        if(mxc<pmx) pmx=mxc;
                    }
                    int m=tr/C;
                    if(m>0) {
                        int rk=(A+m-1)/m;
                        int plm=(i+2)-rk;
                        int vl=P,vr=min(pmx,plm);
                        if(vl<=vr) val.push_back({vl,vr});
                    }
                    P=pmx+1;
                }
            }
        }
        if(val.empty()) {
            cout<<"No\n";
            return;
        }
        vector<pair<int,int>> nxt;
        for(auto p:val) nxt.push_back({p.first,p.second+1});
        sort(all(nxt));

        vector<pair<int,int>> v2;
        for(auto p:nxt) {
            if(v2.empty()) {
                v2.push_back(p);
            } else {
                if(p.first<=v2.back().second+1) {
                    if(p.second>v2.back().second) v2.back().second=p.second;
                } else {
                    v2.push_back(p);
                }
            }
        }
        S=v2;
    }
    cout<<"Yes\n";
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