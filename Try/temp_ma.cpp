// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long

const int MAXN = 3e6 + 5; 
const int MAX_N = 2e5 + 1;
ll MOD = 1000000007;
const ll MOD2 = 1073676287;
const ll MOD3 = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

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

void precompute(int n) {
    fact.assign(n + 1, 1); 
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    invf.assign(n + 1, 1);
    invf[n] = qexp(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i > 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
}

ll nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invf[k] % MOD * invf[n - k] % MOD;
    // return fact[n] * qexp(fact[k], MOD - 2, MOD) % MOD * qexp(fact[n - k], MOD - 2, MOD) % MOD;
}

void sol()
{
    
    ll a,b,c,n,m,k=-1,x,resu=0;
    cin >> n;
    vector<ll> arr(n,0),brr(n,0),crr(n,0);
    x=0;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        x+=arr[i];
    }
    for (int i=0;i<n;i++)
    {
        cin >> brr[i];
    }
    for (int i=0;i<n;i++)
    {
        cin >> crr[i];
    }
    int ii=-1,ij=0;
    ll sum=0;
    ll req=(x+2)/3;
    vector<ll> ac(n,-1),bc(n,-1),cc(n,-1);
    for (int i=0;i<n;i++)
    {
        
        ii=i;
        while(ij<n && sum<req) 
        {
            sum+=arr[ij++];
        }
        if (sum>=req) ac[i]=ij;
        sum-=arr[ii];
    }
    ii=-1;
    ij=0;
    sum=0;
    for (int i=0;i<n;i++)
    {
        
        ii=i;
        while(ij<n && sum<req) 
        {
            sum+=brr[ij++];
        }
        if (sum>=req) bc[i]=ij;
        sum-=brr[ii];
    }
    ii=-1;
    ij=0;
    sum=0;
    for (int i=0;i<n;i++)
    {
        
        ii=i;
        while(ij<n && sum<req) 
        {
            sum+=crr[ij++];
        }
        if (sum>=req) cc[i]=ij;
        sum-=crr[ii];
    }
    ll temp=LINF;
    
    for (int i=0;i<n;i++)
    {
        temp=LINF;
        ii=0;
        ij=0;
        while(i<n && ac[i]==-1) i++;
        if (i>=n) continue;
        while(i<n && ac[i]!=-1 && ac[i]<=temp) temp=ac[i++];
        ii=temp;
        if (ii>=n) continue;
        temp=LINF;
        while(ii<n && bc[ii]==-1) ii++;
        while(ii<n && bc[ii]!=-1 && bc[ii]<=temp) temp=bc[ii++];
        ij=temp;
        if (ij>=n) continue;
        temp=LINF;
        while(ij<n && cc[ij]==-1) ij++;
        while(ij<n && cc[ij]!=-1 && cc[ij]<=temp) temp=cc[ij++];
        if (temc)
        if (i<=n && ii<=n && ij<=n && temp<=n) 
        {
            cout << i << " " << ac[i-1] << " " << ii << " " << bc[ii-1] << " " << ij << " " << cc[ij-1] << endl;
            return;
        }
    }
    cout << -1 << endl;
    return;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    // precompute(100);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}