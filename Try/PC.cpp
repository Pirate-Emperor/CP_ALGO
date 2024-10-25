#include <bits/stdc++.h>
using namespace std;


mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

const int MAXN = 3e6 + 5; 
const int MAX_N = 1e5 + 5;
// ll MOD = 998244353;
// const ll MOD2 = 1073676287;
// const ll MOD3 = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

struct tdata {
    bool dat[4];
    tdata(){

    }
    tdata(bool a, bool b, bool c, bool d) : dat{a,b,c,d}{}
};
 
tdata operator*(const tdata &l, const tdata &r) {
    tdata c {(l.dat[0]&&r.dat[0])||(l.dat[1]&&r.dat[2]),
                (l.dat[0]&&r.dat[1])||(l.dat[1]&&r.dat[3]),
                (l.dat[2]&&r.dat[0])||(l.dat[3]&&r.dat[2]),
                (l.dat[2]&&r.dat[1])||(l.dat[3]&&r.dat[3])};
    return c;
}

bool arr[MAX_N][4];
tdata st[4 * MAX_N];
int mp[MAX_N]; 
void build(int node, int start, int end) {
    if (start == end) {
        st[node] = tdata(arr[start][0],arr[start][1],arr[start][2],arr[start][3]);
        mp[start]=node;
        return;
    }
    int mid = (start + end) / 2;
    node<<=1;
    build(node, start, mid);
    build(node + 1, mid + 1, end);
    st[node/2] = st[node]* st[node + 1];
}

void update(int node, int start, int end, int idx) {
    node = mp[idx];
    st[node] = tdata(arr[idx][0],arr[idx][1],arr[idx][2],arr[idx][3]);
    do{
        node>>=1;
        st[node] = st[2*node]* st[2*node + 1];
        
    }while(node>1);
}
 
tdata query(int node, int start, int end, int l, int r) {
    if (start > r || end < l) 
    {
        return st[0];
    };
    if (l <= start && end <= r) return st[node];
    int mid = (start + end) / 2;
    node<<=1;
    return query(node, start, mid, l, r)* query(node + 1, mid + 1, end, l, r);
}

int read() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int ret = 0;
	while (c >= '0' && c <= '9') ret = ret*10 + (c - '0'), c = getchar();
	return ret;
}

void sol()
{
    ll a,b,c,d,n,resu=LINF;
    n = read();
    string s;
    vector<ll> brr(n), crr, drr;
    for (int i=0;i<n;i++)
    {
        brr[i] = read();
    }
    cin >> s;
    crr.push_back(0);
    a = brr[0];
    for (int i=1;i<n;i++)
    {
        if (brr[i]>a)
        {
            a=brr[i];
            crr.push_back(i);
        }
    }
    drr.push_back(n-1);
    a=brr[n-1];
    for (int i=n-2;i>=0;i--)
    {
        if (brr[i]>a)
        {
            a=brr[i];
            drr.push_back(i);
        }
    }
    drr.pop_back();
    while(!drr.empty())
    {
        crr.push_back(drr.back());
        drr.pop_back();
    }
    drr.clear();
    drr.resize(crr.size());
    vector<pair<ll,ll>> ar;
    resu = 0;
    n = crr.size();
    for (int i=0;i<crr.size();i++)
    {
        a = (i==0)?0:(crr[i]-crr[i-1]-1);
        b = (i==n-1)?0:(crr[i+1]-crr[i]-1);
        // cout << a << " " << b << "T";
        ar.push_back(make_pair(a,b));
        drr[i]=max(a,b);
        if (ar.size()>1)
        {
            ll temp = max(ar[i-1].first+1LL+max(ar[i].first,ar[i].second),ar[i-1].second+1LL+ar[i].second); 
            resu = max(resu, temp);
        }
    }
    priority_queue<pair<ll,ll>> pq;
    for (int i=n-3;i>=0;i--)
    {
        pq.push(make_pair(drr[i+2]+i+2,i+2));
        auto tem = pq.top();
        ll temp = drr[i]+drr[tem.second]+tem.second-i;
        resu = max(resu,temp);
    }
    cout << resu << endl;
    return;
}


int main() {

    // ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
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