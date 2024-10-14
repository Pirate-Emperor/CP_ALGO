// Segment tree with lazy propagation for range sum query, range add update, range set update
// Problem link: https://cses.fi/problemset/task/1735/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 5e3 + 100;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

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
 
int n, q, arr[MAX_N];
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
 
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 3) cout << query(1, 1, n, l, r).sum << "\n";
        else {
            int x; cin >> x;
            update(1, 1, n, l, r, x, t);
        }
    }
}

void sol()
{
    
    ll a,b,c,d,n,m,q=0,k=-1,x,resu=LINF;
    cin >> n >> m;
    // vector<vector<ll>> dp(2,vector<ll>(m+10,0));
    // ll sq = 70;
    // ll sqSize = m/sq;
    // vector<ll> mat(80,0);
    a=0;
    // map<ll,ll> mpi,npi;
    // ll np=0,mp=0;
    int maxN = 5e3+10;
    for (int i=0;i<=maxN;i++) arr[i]=0;
    build(1,1,maxN);
    for (int i=0;i<n;i++) 
    {
        cin >> x;
        if (x==0)
        {
            a++;
        }
        else
        {
            if (x>0 && x<=a) 
            {
                update(1, 1, maxN, x+1, m+1, 1, 1);
                // mpi[x]++;
                // int tem = ((x+sq-1)/sq)*sq;
                // for (int j=x;j<=tem;)
                // for (int j=x;j<=m;j++) dp[0][j]=dp[0][j]+1;
                // mp++;
            }
            else if (x<0 && abs(x)<=a) 
            {
                update(1, 1, maxN, 1, a+x+1, 1, 1);
                // npi[a+x]++;
                // for (int j=0;j<=a+x;j++) dp[0][j] = dp[0][j]+1;
                // np++;
            }
        }
    }
    // int last = 0;
    // // int ni = npi.size();
    // // for (int i=0;i<ni;i++)
    // // {
    // //     for (int j=last;j<=npi[i];j++) dp[0][j]+=np;
    // //     np-=npi[i];
    // //     last=npi[i]+1;
    // // }
    // last=m;
    // int mi = mpi.size();
    // for (int i=mi-1;i>=0;i--) 
    // {
    //     for (int j=last;j>=mpi[i];j--) dp[0][j]+=mp;
    //     mp-=mpi[i];
    //     last=mpi[i]-1;
    // }   
    resu=0;
    for (int i=0;i<=m;i++)
    {
        ll tem = query(1, 1, maxN, i+1, i+1).sum;
        resu=max(resu,tem);
    }
    cout << resu << endl;
    return;
}


int main() {

    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    
    // precompute(2e5+10);
    // TxtIO;
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}