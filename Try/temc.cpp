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


struct tdata {
    ll sum, pref, suff, ans, tmax, tmin, imax, imin;
    tdata() {
        sum = pref = suff = ans = 0;
        tmax = -LINF;
        tmin = LINF;
        imax = -1;
        imin = -1;
    }
    tdata(int val, int ind) {
        sum = val;
        pref = suff = ans = max(0, val);
        tmax = val;
        tmin = val;
        imax =ind;
        imin = ind;
    }
    tdata(tdata l, tdata r) {
        sum = l.sum + r.sum;
        pref = max(l.pref, l.sum + r.pref);
        suff = max(r.suff, r.sum + l.suff);
        ans = max({l.ans, r.ans, l.suff + r.pref});
        tmax = max(l.tmax,r.tmax);
        if (r.tmax>l.tmax) imax = r.imax;
        else imax = min(l.imax,r.imax);
        tmin = min(l.tmin,r.tmin);
        if (r.tmin<l.tmin) imin = r.imin;
        else imin = min(l.imin,r.imin);
    }
};
 
int n, q, arr[MAX_N],brr[MAX_N];
tdata st[4 * MAX_N];
tdata st2[4 * MAX_N];
 
void build2(int node, int start, int end) {
    if (start == end) {
        st2[node] = tdata(brr[start], start);
        return;
    }
    int mid = (start + end) / 2;
    build2(2 * node, start, mid);
    build2(2 * node + 1, mid + 1, end);
    st2[node] = tdata(st2[2 * node], st2[2 * node + 1]);
}
 
void update2(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        st2[node] = tdata(val, start);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update2(2 * node, start, mid, idx, val);
    else update2(2 * node + 1, mid + 1, end, idx, val);
    st2[node] = tdata(st2[2 * node], st2[2 * node + 1]);
}
 
tdata query2(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return tdata(0,0);
    if (l <= start && end <= r) return st2[node];
    int mid = (start + end) / 2;
    return tdata(query2(2 * node, start, mid, l, r), query2(2 * node + 1, mid + 1, end, l, r));
}

void build(int node, int start, int end) {
    if (start == end) {
        st[node] = tdata(arr[start], start);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    st[node] = tdata(st[2 * node], st[2 * node + 1]);
}
 
void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        st[node] = tdata(val, start);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    st[node] = tdata(st[2 * node], st[2 * node + 1]);
}
 
tdata query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return tdata(0,0);
    if (l <= start && end <= r) return st[node];
    int mid = (start + end) / 2;
    return tdata(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}

void sol(){
    ll a,b,c,m,k=-1,x,resu=0;
    cin >> n;
    vector<ll> crr(n+1,-1);
    map<ll,vector<ll>> mpi;
    x=0;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i+1];
        brr[i+1]=arr[i+1];
        mpi[arr[i+1]].push_back(i+1);
    }
    build(1, 1, n);
    build2(1, 1, n);
    set<ll> path;
    for (int i=n;i>=1;i--)
    {
        if (crr[arr[i]]==-1)
        {
            crr[arr[i]]=i;
            resu++;
            path.insert(i);
        }
        
        
    }
    cout << resu << endl;
    ll past=0;
    vector<ll>  res;
    resu=0;
    while(!path.empty())
    {
        int tem = *path.end();
        if (resu%2==0)
        {
            auto q1 = query(1,1,n,past+1,tem);
            ll tem2 =  q1.tmax;
            res.push_back(tem2);
            x=crr[tem2];
            auto it = upper_bound(path.begin(),path.end(),x);
            auto ti = it;
            ti--;
            if (it!= path.begin() && *(ti)==x)
            {
                path.erase(--it);
            }
            else if (it!= path.end()) path.erase(it);
            for (auto it2: mpi[tem2])
            {
                update(1,1,n,it2,-INF);
            }
            mpi[tem2].clear();
            past = q1.imax;
        }
        else
        {
            auto q1 = query2(1,1,n,past+1,tem);
            ll tem2 =  q1.tmin;
            res.push_back(tem2);
            x=crr[tem2];
            auto it = upper_bound(path.begin(),path.end(),x);
            auto ti = it;
            ti--;
            if (it!= path.begin() && *(ti)==x)
            {
                path.erase(--it);
            }
            else if (it!= path.end()) path.erase(it);
            for (auto it2: mpi[tem2])
            {
                update2(1,1,n,it2,INF);
            }
            mpi[tem2].clear();
            past = q1.imin;
        }
        resu++;
    }
    for (int i=0;i<res.size();i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
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