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

map<long long, ll> trial_division1(long long n) {
    map<long long, ll> factorization;
    for (long long d = 2; d * d <= n; d++) {
        while (n % d == 0) {
            factorization[d]++;
            n /= d;
        }
    }
    if (n > 1)
        factorization[n]++;
    return factorization;
}
const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

vector < vector<double> > arr;
int check_val () {
    vector<double> ans;
    int n = (int) arr.size();
    int m = (int) arr[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (arr[i][col]) > abs (arr[sel][col]))
                sel = i;
        if (abs (arr[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (arr[sel][i], arr[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = arr[i][col] / arr[row][col];
                for (int j=col; j<=m; ++j)
                    arr[i][j] -= arr[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = arr[where[i]][m] / arr[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * arr[i][j];
        if (abs (sum - arr[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}
void sol()
{
    
    ll a,b,c,n,m,k=-1,l,x,resu=0;
    cin >> a >> b >> l;
    map<ll,ll> facl = trial_division1(l);
    map<ll,ll> fac_ind;
    ll ta=a;
    ll tb=b;
    arr.resize(facl.size(),vector<double> (3,0.0));
    // vector<vector<double>> arr(facl.size(),3);
    ll itm=0;
    for (auto it: facl)
    {
        fac_ind[it.first]=itm;
        while (ta%it.first)
        {
            ta/=it.first;
            arr[itm][0]+=1.0;
        }
        while (tb%it.first)
        {
            tb/=it.first;
            arr[itm][1]+=1.0;
        }
        arr[fac_ind[it.first]][2]=it.second;
        itm++;
    }
    // resu+=(check_val()!=0);
    map<ll,ll> fac;
    ll temp=0;
    for (int i=1;i*i<=l;i++)
    {
        if (l%i==0)
        {
            fac = trial_division1(l/i);
            for (auto it: facl) arr[fac_ind[it.first]][2]=0;
            for (auto it: fac) arr[fac_ind[it.first]][2]=it.second;
            resu+=(check_val()!=1);
            fac = trial_division1(i);
            for (auto it: facl) arr[fac_ind[it.first]][2]=0;
            for (auto it: fac) arr[fac_ind[it.first]][2]=it.second;
            resu+=(check_val()!=1);
            temp++;
        }
    }
    cout << temp << " " << resu << endl;
    
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