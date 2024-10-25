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
    vector<ll> brr(2*n+1), crr(2*n+1);
    for (int i=0;i<2*n;i++)
    {
        brr[i] = read();
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
    for (int i=1;i<=n;i++)
    {
        arr[i][0] = 0;
        arr[i][1] = 0;
        arr[i][2] = 0;
        arr[i][3] = 0;
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
    bool temp[4]={0,0,0,0};
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
    ll r=0;
    resu = LINF;
    bool check=false;
    int i,j;
    while(true)
    {
        if (check==true)
        {
            resu = min(resu,seg[r-1].first-seg[l].first);
            i = seg[l].second;
            j = i%4;
            i/=4;
            i++;
            arr[i][j]=!arr[i][j];
            update(1,1,n,i);
            auto tem = query(1,1,n,1,n);
            if (tem.dat[0]==1 || tem.dat[3]==1) check=true;
            else check=false;
            l++;
        }
        else
        {
            r++;
            if (r>4*n) break;
            i = seg[r-1].second;
            j = i%4;
            i/=4;
            i++;
            arr[i][j]=!arr[i][j];
            update(1,1,n,i);
            auto tem = query(1,1,n,1,n);
            if (tem.dat[0]==1 || tem.dat[3]==1) check=true;
            else check=false;
        }
    }
    
    // resu = seg[r].first-seg[l].first;
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