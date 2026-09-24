#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

#define getbit(x,i) ((x>>i)&1LL)
#define setbit(x,i) ((x)|(1LL<<i))
#define clearbit(x,i) ~((~x)|(1LL<<i))
#define togglebit(x,i) ((x)^(1LL<<i))
#define lowbit(x) (x&(-x))
#define strip_low(x) (x-lowbit(x)) 
#define is_pow2(x) (x>0 && (((x-1)&x)==0))
#define is_ones(x) (((x+1)&x)==0)
#define all_ones(i) ((1LL<<i)-1LL)

int count1s_toN(int n){
    int c=0;
    for (int i=61;i>=0;i--){
        if (n&(1LL<<i)){
            c+=(i?((1LL<<(i-1))*i):0)+(n-(1LL<<i)+1);
            n-=(1LL<<i);
        }
    }
    return c;
}

ll qexp(ll a, ll b, ll m){
    ll res=1;
    a%=m;
    while(b>0){
        if (b%2) res=((__int128_t)res*a)%m;
        a=((__int128_t)a*a)%m;
        b/=2;
    }
    return res;
}

ll gcd(ll a, ll b){
    if (b==0) return a;
    return gcd(b, a%b); 
}

ll ext_gcd(ll a, ll b, ll& x, ll& y){
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    ll x1,y1;
    ll g = ext_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return g;
}

ll inv_mod(ll a, ll m){
    ll x,y;
    ll g=ext_gcd(a,m,x,y);
    if (g!=1) return -1;
    return (m+x%m)%m;
}

namespace Primes{
    const int MAX_N = 2e5;
    vector<int> primes;
    int spf[MAX_N], phi[MAX_N], mu[MAX_N];
    void sieve(){
        primes.clear();
        spf[1]=0;
        phi[1]=1;
        mu[1]=1;
        for (int i=2;i<MAX_N;i++){
            if (!spf[i]) {
                spf[i]=i;
                primes.push_back(i);
                phi[i]=i-1;
                mu[i]=-1;
            }
            for (auto it:primes){
                if (it>spf[i] || it*i>=MAX_N) break;
                spf[it*i]=it;
                mu[it*i]=(spf[i]==it)?0:-mu[i];
                phi[it*i]=phi[i]*((spf[i]==it)?it:(it-1));
            }
        }
    }
    vector<pair<int,int>> factorize(int a){
        vector<pair<int,int>> res;
        while(a>1){
            ll sp=spf[a];
            ll b=0;
            while(a%sp==0){
                a/=sp;
                b++;
            }
            res.push_back({sp,b});
        }
        return res;
    }
}
signed main(){
    return 0;
}