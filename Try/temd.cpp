// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long

const ll MAXN = 1e5 + 5; 
const ll MAX_N = 2e5 + 1;
ll MOD = 1000000007;
const ll MOD2 = 1073676287;
const ll MOD3 = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

pair<ll, ll> t[4*MAXN];

pair<ll, ll> combine(pair<ll, ll> a, pair<ll, ll> b) {
    if (a.first > b.first) 
        return a;
    if (b.first > a.first)
        return b;
    return make_pair(a.first, a.second + b.second);
}

void build(ll a[], ll v, ll tl, ll tr) {
    if (tl == tr) {
        t[v] = make_pair(a[tl], 1);
    } else {
        ll tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

pair<ll, ll> get_max(ll v, ll tl, ll tr, ll l, ll r) {
    if (l > r)
        return make_pair(-INF, 0);
    if (l == tl && r == tr)
        return t[v];
    ll tm = (tl + tr) / 2;
    return combine(get_max(v*2, tl, tm, l, min(r, tm)), 
                   get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(ll v, ll tl, ll tr, ll pos, ll new_val) {
    if (tl == tr) {
        t[v] = make_pair(new_val, 1);
    } else {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
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

vector<ll> fact, invf;

void precompute(ll n) {
    fact.assign(n + 1, 1); 
    for (ll i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    invf.assign(n + 1, 1);
    invf[n] = qexp(fact[n], MOD - 2, MOD);
    for (ll i = n - 1; i > 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
}

ll nCk(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invf[k] % MOD * invf[n - k] % MOD;
    // return fact[n] * qexp(fact[k], MOD - 2, MOD) % MOD * qexp(fact[n - k], MOD - 2, MOD) % MOD;
}

void sol()
{
    
    ll a,b,c,d,n,m,k=-1,x,y,z,r,resu=0,res=0;
    cin >> n;
    vector<ll> arr(n,0),brr(n,0);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    a=0;
    b=0;
    c=0;
    d=0;
    x=0;
    z=0;
    for (int i=0;i<n;i++)
    {
        cin >> brr[i];
        if (arr[i]==brr[i])
        {
            if (arr[i]==-1) c++;
            else if (arr[i]==1) d++;
        }
        else 
        {
            if (min(arr[i],brr[i])==-1)
            {
                a+=(arr[i]==-1)?0:arr[i];
                b+=(brr[i]==-1)?0:brr[i];
            }
            else if (min(arr[i],brr[i])==0)
            {
                a+=arr[i];
                b+=brr[i];
            }
        }
    }
    x=a;
    y=b;
    a=min(x,y);
    b=max(x,y);
    if (d<=b-a){
        a+=d;
        d=0;
    }
    else 
    {
        a=b;
        d-=(b-a);
        a+=d/2;
        b+=(d+1)/2;
        d=0;
    }
    if (c<=b-a)
    {
        b-=c;
        c=0;
    }
    else
    {
        b=a;
        c-=(b-a);
        b-=c/2;
        a-=(c+1)/2;
        c=0;
    }
    cout << a << endl;
    return;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    // precompute(100);
    ll tc = 1;
    cin >> tc;
    for (ll t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}