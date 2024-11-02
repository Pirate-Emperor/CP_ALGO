// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
ll m;
struct tdata {
    ll sum, setval, addval;
    bool lazyset;
    tdata() {
        sum = setval = addval = lazyset = 0;
    }
    tdata(ll val) {
        sum = val;
        setval = addval = lazyset = 0;
    }
    tdata(tdata l, tdata r) {
        sum = l.sum + r.sum; 
    }
};
 
int n, arr[MAX_N];
tdata st[4 * MAX_N];
 
void build(int node, int start, int end) {
    if (start == end) {
        st[node] = tdata(arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
}
 
void down(int node, int start, int end) { 
    int mid = (start + end) / 2;
    if (st[node].lazyset) {
        st[2 * node] = st[2 * node + 1] = st[node];
        st[2 * node].sum = (st[node].setval + st[node].addval) * (mid - start + 1);
        st[2 * node + 1].sum = (st[node].setval + st[node].addval) * (end - mid);
    }
    else {
        st[2 * node].addval += st[node].addval;
        st[2 * node + 1].addval += st[node].addval;
        st[2 * node].sum += st[node].addval * (mid - start + 1);
        st[2 * node + 1].sum += st[node].addval * (end - mid);
    }
    st[node].addval = st[node].setval = st[node].lazyset = 0;
}

// t = 1 means range add update, t = 2 means range set update
void update(int node, int start, int end, int l, int r, ll val, int t) { 
    if (r < start || end < l) return;
    if (l <= start && end <= r) {
        if (t == 2) {
            st[node].setval = val;
            st[node].lazyset = 1;
            st[node].addval = 0;
            st[node].sum = val * (end - start + 1);
        }
        else {
            st[node].addval += val;
            st[node].sum += val * (end - start + 1);
        }
        return;
    }
    down(node, start, end);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val, t);
    update(2 * node + 1, mid + 1, end, l, r, val, t);
    st[node].sum = st[2 * node].sum + st[2 * node + 1].sum;
}
 
tdata query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return tdata(0);
    if (l <= start && end <= r) return st[node];
    down(node, start, end);
    int mid = (start + end) / 2;
    return tdata(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
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

void solve() {
    cin >> n >> m;
    vector<ll> brr(n+1);
    ll sum=0;
    for (int i = 1; i <= n; i++) 
    {
        cin >> brr[i];
        brr[i]%=m;
        ll temp = brr[i]*(i)*(n-i+1);
        sum+=temp;
        arr[i]=0;
    }
    for (int i=0;i<=m;i++) arr[i]=0;
    build(1, 1, m);
    int idx = m-1;
    ll resu=0;
    for (int i=1;i<=n;i++) 
    {
        if (brr[i]==0)
        {
            update(1, 1, n, idx+1, idx+1, 1, 1);
            continue;
        }
        if (idx>brr[i])
        {
            resu+=query(1, 1, n, idx-brr[i]+2, idx+1).sum;
        }
        else
        {
            resu+=query(1, 1, n, 1, idx+1).sum;
            resu+=query(1, 1, n, (idx-brr[i]+1+m)%m+1, m).sum;
        }
        idx = (m-brr[i]+idx)%m; 
        update(1, 1, n, idx+1, idx+1, 1, 1);

    }
    cout << resu << endl;
    resu = sum - resu*m;
    cout << resu << endl;
    return;
}






int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}