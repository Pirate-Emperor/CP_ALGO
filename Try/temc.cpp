// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;


mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

const int MAXN = 3e6 + 5; 
const int MAX_N = 2e2 + 5;
ll MOD = 998244353;
const ll MOD2 = 1073676287;
const ll MOD3 = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

struct tdata {
    ll sum, pref, suff, ans, tmax, tmin;
    vector<ll> dat;
    tdata() {
        sum = pref = suff = ans = 0;
        tmax = -LINF;
        tmin = LINF;
    }
    tdata(int val) {
        sum = val;
        pref = suff = ans = max(0, val);
        tmax = val;
        tmin = val;
    }
    tdata(vector<ll> dVal)
    {
        dat = dVal;
    }
    tdata(tdata l, tdata r) {
        sum = l.sum + r.sum;
        pref = max(l.pref, l.sum + r.pref);
        suff = max(r.suff, r.sum + l.suff);
        ans = max({l.ans, r.ans, l.suff + r.pref});
        tmax = max(l.tmax,r.tmax);
        tmin = min(l.tmin,r.tmin);
        dat = l.dat;
        dat[0] = (l.dat[0]*r.dat[0])|(l.dat[1]*r.dat[2]);
        dat[1] = (l.dat[0]*r.dat[1])|(l.dat[1]*r.dat[3]);
        dat[2] = (l.dat[2]*r.dat[0])|(l.dat[3]*r.dat[2]);
        dat[3] = (l.dat[2]*r.dat[1])|(l.dat[3]*r.dat[3]);
    }
};
 
vector<ll> arr[MAX_N];
tdata st[4 * MAX_N];
 
void build(int node, int start, int end) {
    if (start == end) {
        st[node] = tdata(arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    st[node] = tdata(st[2 * node], st[2 * node + 1]);
}
 
void update(int node, int start, int end, int idx, vector<ll> val) {
    if (start == end) {
        arr[idx] = val;
        st[node] = tdata(val);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    st[node] = tdata(st[2 * node], st[2 * node + 1]);
}
 
tdata query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) 
    {
        vector<ll> zero(4,0);
        return tdata(zero);
    };
    if (l <= start && end <= r) return st[node];
    int mid = (start + end) / 2;
    return tdata(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}

int read() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int ret = 0;
	while (c >= '0' && c <= '9') ret = ret*10 + (c - '0'), c = getchar();
	return ret;
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
    ll a,b,c,d,n,k,m,q=0,p,x,resu=LINF;
    n = read();
    vector<ll> brr(2*n+1), crr(2*n+1);
    for (int i=0;i<2*n;i++)
    {
        cin >> brr[i];
    }
    if (n==1)
    {
        cout << 0 << endl;
        return;
    }
    if (n%2==0)
    {
        ll mi = LINF;
        ll ma = -INF;
        for (int i=0;i<n/2;i++)
        {
            int j = i+n/2;
            a = brr[2*i]+brr[2*i+1];
            b = brr[2*i]+brr[2*j+1];
            c = brr[2*j]+brr[2*i+1];
            d = brr[2*j]+brr[2*j+1];
            mi = min(mi,max(min(a,d),min(b,c)));
            ma = max(ma,min(max(a,d),max(b,c)));
        }
        resu = ma-mi;
        cout << resu << endl;
        return;
    }
    vector<ll> one(4,1);
    for (int i=1;i<=n;i++)
    {
        arr[i] = one;
    }
    for (int i=0;i<n/2;i++)
    {
        crr[4*i]=brr[2*i];
        crr[4*i+1]=brr[2*i+1];
        crr[4*i+2]=brr[2*(i+n/2+1)];
        crr[4*i+3]=brr[2*(i+n/2+1)+1];
    }
    crr[2*n-2] = brr[n-1];
    crr[2*n-1] = brr[n];
    build(1,1,n);
    vector<pair<ll,ll>> seg(4*n);
    vector<ll> temp(4,0);
    ll val=0;
    int N = 2*n;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<4;j++)
        {
            temp[j]=1;
            val = crr[(2*i-j/2+N)%N]+crr[(2*i+1+j%2)%N];
            seg[4*i+j]=make_pair(val,4*i+j);
            temp[j]=0;
        }
    }
    sort(seg.begin(),seg.end());
    ll l=0;
    ll r=4*n-1;
    while(true)
    {
        int i = seg[l].second;
        int j = i%4;
        i/=4;
        i++;
        arr[i][j]^=1;
        update(1,1,n,i,arr[i]);
        auto tem = query(1,1,n,1,n).dat;
        if (tem[0]==1 || tem[3]==1)
        {
            l++;
            continue;
        }
        else
        {
            arr[i][j]^=1;
            update(1,1,n,i,arr[i]);
            break;
        }
    }
    while(true)
    {
        int i = seg[r].second;
        int j = i%4;
        i/=4;
        i++;
        arr[i][j]^=1;
        update(1,1,n,i,arr[i]);
        auto tem = query(1,1,n,1,n).dat;
        if (tem[0]==1 || tem[3]==1)
        {
            r--;
            continue;
        }
        else
        {
            arr[i][j]^=1;
            update(1,1,n,i,arr[i]);
            break;
        }
    }
    
    resu = seg[r].first-seg[l].first;
    cout << resu << endl;
    return;
}


int main() {

    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    
    // precompute(2e5+10);
    // TxtIO;
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}