#include <bits/stdc++.h>
using namespace std;

// Daily

#define ll long long
#define int long long
const int INF=1e9;
const ll LINF=1e18;
const int MAX_N=2e5;

#define getbit(x,i) (((x)>>(i))&1LL)
#define setbit(x,i) ((x)|(1LL<<(i)))
#define togglebit(x,i) (x^(1LL<<i))
#define lowbit(x) ((x)&(-(x)))
#define strip_lowbit(x) ((x)-((x)&(-(x))))
#define is_pow2(x) (x&&((x&(x-1LL))==0))
#define is_allones(x) (x&&((x&(x+1LL))==0))
#define all_ones(i) ((1LL<<i)-1LL)

ll count1s_ton(ll n){
    ll res=0;
    for (int i=61;i>=0;i--){
        if ((1LL<<i)&n){
            res+=(i?(1LL<<(i-1))*i:0)+(n-(1LL<<i)+1);
            n-=(1LL<<i);
        }
    }
    return res;
}

ll qexp(ll a, ll b, ll m){
    ll res=1;
    while(b>0){
        if (b%2) res=((__int128_t)res*a)%m;
        a=((__int128_t)a*a)%m;
        b/=2;
    }
    return res;
}
ll gcd(ll a, ll b){
    return (b)?gcd(b,a%b):a;
}
ll ext_gcd(ll a, ll b, ll &x, ll &y){
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    ll x1,y1;
    ll g=ext_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return g;
}
ll inv_mod(ll a, ll m){
    ll x,y;
    ll g=ext_gcd(a,m,x,y);
    if (g!=1) return -1;
    return (x%m+m)%m;
}

namespace Primes{
    const int MAX_N=2e5;
    vector<int> primes;
    int spf[MAX_N], phi[MAX_N], mu[MAX_N];
    void prec(){
        spf[2]=2;
        for (int i=2;i<MAX_N;i++){
            if (!spf[i]){
                primes.push_back(i);
                spf[i]=i;
                phi[i]=i-1;
                mu[i]=-1;
            }
            for (auto it:primes){
                if (it>spf[i] || i*it>=MAX_N) break;
                spf[i*it]=it;
                phi[i*it]=phi[i]*((it==spf[i])?it:(it-1));
                mu[i*it]=mu[i]*((it==spf[i])?0:-1);
            }
        }
    }
    vector<array<ll,2>> factorize(ll n){
        ll i=2;
        vector<array<ll,2>> res;
        while (i*i<=n){
            int c=0;
            while(n%i==0){
                n/=i;
                c++;
            }
            if (c>0) res.push_back({i,c});
            i++;
        }
        if (n>1) res.push_back({n,1});
        return res;
    }
    vector<array<ll,2>> factors_spf(ll n){
        vector<array<ll,2>> res;
        while (n>1){
            int c=0;
            ll i=spf[n];
            while(n%i==0){
                n/=i;
                c++;
            }
            res.push_back({i,c});
        }
        return res;
    }
    ll NOD(ll n){
        auto factors=factorize(n);
        ll res=1;
        for (auto it:factors) res*=(it[1]+1);
        return res;
    }
    ll SOD(ll n){
        auto factors=factorize(n);
        ll res=1;
        for (auto [p,c]:factors){
            ll sum=1;
            ll pr=1;
            while(c--){
                pr*=p;
                sum+=pr;
            }
            res*=sum;
        }
        return res;
    }
    array<ll,2> count_prime_factors(ll n){
        auto factors = factorize(n);
        array<ll,2> res={0,0};
        for (auto it:factors){
            res[0]++;
            res[1]+=it[1];
        }
        return res;
    }
    ll get_phi(int n){
        auto factors = factorize(n);
        ll res=n;
        for (auto it: factors){
            res-=res/it[0];
        }
        return res;
    }
}


// Batch-2
vector<vector<array<ll,2>>> adj;
// vector<array<ll,2>> adj[MAX_N];
vector<ll> dijkstra(int s, int n){
    priority_queue<array<ll,2>,vector<array<ll,2>>,greater<array<ll,2>>> pq;
    vector<ll> dist(n,LINF);
    pq.push({0,s}); 
    dist[s]=0;
    while(!pq.empty()){
        auto [uc,u]=pq.top();
        pq.pop();
        if (dist[u]>uc) continue;
        for (auto [v,c]: adj[u]){
            if (dist[v]>uc+c){
                dist[v]=uc+c;
                pq.push({uc+c,v});
            }
        }
    }
    return dist;
}
vector<ll> bfs_01(int s, int n){
    deque<ll> dq;
    vector<ll> dist(n,LINF);
    dq.push_back(s);
    dist[s]=0;
    while(!dq.empty()){
        auto u=dq.front();
        dq.pop_front();
        for (auto [v,c]:adj[u]){
            if (dist[v]>dist[u]+c){
                dist[v]=dist[u]+c;
                (c)?dq.push_back(v):dq.push_front(v);
            }
        }
    }
    return dist;
}

void solve(){

}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(null);

    int t=0;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}