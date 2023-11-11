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

// // A trick to calculate large factorial without overflowing is to take log at every step when precompute and take exponential when calculating
// // Don't need invf[] now because it is the same as negative log of fact
// vector<double> log_fact;
// void precompute_log(int n) {
//     log_fact.assign(n + 1, 0.0);
//     log_fact[0] = 0.0; 
//     for (int i = 1; i <= n; i++) log_fact[i] = log_fact[i - 1] + log(i); 
// }

// ll log_nCk(int n, int k) { 
//     if (k < 0 || k > n) return 0;
//     return exp(log_fact[n] - log_fact[n - k] - log_fact[k]); 
// }
// map<string, int> mps;
// map<string,pair<int,pair<int,int>>> dp;
// auto dfs(string cur, int nmax, int nsum)
// {
//     if (dp.find(cur)!=dp.end()) return dp[cur];
//     auto &res = dp[cur];
//     for (char c='a';c<='z';c++)
//     {
//         int x = c-'a'+1;
//         for (string s: {cur+c,c+cur})
//         {
//             int mmax=max(nmax,x);
//             int msum=nsum+x;
//             if (mps.find(s)!=mps.end())
//             {
//                 int score = msum*mmax+mps[s];
//                 auto nex=dfs(s,mmax,msum);
//                 res=max(res,{!nex.first,{score-nex.second.second,-nex.second.first}});
//             }
//         }
//         // cout << c;
//     }
//     return res;
// }

// int ask(int x1, int y1){
//     cout << "? " << x1  << ' ' << y1 << endl;
//     cin >> x1; return x1;
// }
 
// // void solve(){
// //     int ans1 = ask(1,1);
// //     int ans2 = ask(1,INF);
// //     int ans3 = ask(INF,1);
// //     int ans4 = ask(INF,INF);
 
// //     int ysum = ans3-ans4+INF+1;
// //     int x1 = ask(1,ysum/2)+1;
// //     int y1 = ans1-x1+2;
// //     int y2 = x1-ans2+INF-1;
// //     int x2 = y1-ans3+INF-1;
// //     cout << "! " << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2  << endl;
// // }
// void solve() {
//     ll ni=1,nj=1e9,a1=0,a2=0,x=0,y=0,d1=0,x1=0,y1=0,d2=0,x2=0,y2=0,mid=0;
//     cout << "? " << ni << " " << ni << endl;
//     cin >> a1;
//     cout << "? " << ni << " " << nj << endl;
//     cin >> a2;
    
//     cout << "? " << nj << " " << ni << endl;
//     cin >> x;
//     cout << "? " << nj << " " << nj << endl;
//     cin >> y;
//     mid=1+((nj-y+x-ni)/2);
//     cout << "? " << ni << " " << mid << endl;
//     cin >> d1;
//     cout << "? " << nj << " " << mid << endl;
//     cin >> d2;
    
//     x1=1+d1;
//     y1=2+a1-x1;
//     y2=x1-a2+nj-1;
//     x2=y1-x+nj-1;
//     // y1=x-x1;
//     // y1++;
//     // x1++;
    
//     // x2=d2;
//     // y2=y-x2;
//     // x2=nj-x2;
//     // y2=nj-y2;
//     cout << "! " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
//     return;
// }
// const int MAXL=4*1e5+5;
// ll seg[8*MAX_N][2],lazy[8*MAX_N][2], st[2*MAX_N][2], dp[2*MAX_N][2];
// ll MODA[2]={MOD,MOD2};
// ll bas[2]={11,13};

// ll val(int l, int r,int k)
// {
//     l--,r--;
//     // cout << "val" << l << r << endl;
//     if(!l)return dp[r][k];else return ((dp[r][k]-dp[l-1][k])%MODA[k]+MODA[k])%MODA[k];
// //   return (((l==0)?dp[r][k]:(dp[r][k]-dp[l-1][k])+MODA[k])%MODA[k]);   
// }
// void push(int v, int l, int r, int k)
// {
//     if (!lazy[v][k]) return;
//     int mid = (r+l)/2;
//     seg[v*2][k]=(lazy[v][k]*val(l,mid,k))%MODA[k];
//     seg[v*2+1][k]=(lazy[v][k]*val(mid+1,r,k))%MODA[k];
//     lazy[v*2][k]=lazy[v*2+1][k]=lazy[v][k];
//     lazy[v][k]=0;
//     return;
// }
// void update(int v, int k, int l, int r, int tl, int tr, ll g)
// {
//     if (l>r) return;
//     if (l==tl && r==tr)
//     {
//             seg[v][k]=(g*val(l,r,k))%MODA[k];
//             lazy[v][k]=g;
//             return;
//     }
    
//     int mid=(tr+tl)/2;
//     push(v,tl,tr,k);
//     update(2*v,k,l,min(r,mid),tl,mid,g);
//     update(2*v+1,k,max(l,mid+1),r,mid+1,tr,g);
//     seg[v][k]=(seg[2*v][k]+seg[2*v+1][k]);
//     return;
// }
// ll get(int v, int k, int l, int r, int tl, int tr)
// {
//     if (l>r) return 0;
//     if (l==tl && r==tr)
//     {
//         return seg[v][k];
//     }
//     push(v,tl,tr,k);
//     int mid=tl+(tr-tl)/2;
//     return (get(2*v,k,l,min(r,mid),tl,mid)+get(2*v+1,k,max(l,mid+1),r,mid+1,tr))%MODA[k]; 
// }
// void sol()
// {
//     int n;
//     cin >> n;
//     vector<pair<int,int>> arr(n);
//     for (int i=0;i<n;i++)
//     {
//         cin >> arr[i].first;
//         arr[i].second=i+1;
//     }
//     ll res=0;
//     for (int i=1;i<=n;i++) res+=(ll)(i-1)*(n-i+1);
//     sort(arr.begin(),arr.end());
//     set<int> hi = {0,n+1}, lo = {0,n+1};
//     for (int i=1;i<=n;i++)
//     {
//         hi.emplace(i);
//     }
//     for (int i=1;i<=n;i++)
//     {
//         int k=arr[i-1].second;
//         hi.erase(k);
//         lo.emplace(k);
//         int i1=*hi.lower_bound(k);
//         int x=*prev(hi.lower_bound(k));
//         if (i1==n+1) continue;
//         int y=*lo.lower_bound(i1);
//         res-=(ll)(k-x)*(y-i1);
//     }
//     cout << res << endl;
// }

// typedef struct item * Treap;
// struct item{
//     ll val;
//     ll prior;
//     ll cnt;
//     ll sum=0,ans=0;
//     item* l=NULL;
//     item* r=NULL;
//     item(int val) : val(val), prior(rand()), l(NULL), r(NULL), cnt(1), sum(0), ans(0) {}
// };

// ll val(Treap t)
// {
//     return t?t->val:0;
// }
// ll cnt(Treap t)
// {
//     return t?t->cnt:0;
// }
// ll sum(Treap t)
// {
//     return t?t->sum:0;
// }
// ll ans(Treap t)
// {
//     return t?t->ans:0;
// }
// void upd_cnt(Treap t)
// {
//     if (t)
//     {
//         t->cnt=1+cnt(t->l)+cnt(t->r);
//         t->sum=val(t)+sum(t->l)+sum(t->r);
//         t->ans=ans(t->l)+ans(t->r)+sum(t->r)*cnt(t->l)-sum(t->l)*cnt(t->r)+sum(t->r)-(ll)val(t)*cnt(t->r)-sum(t->l)+(ll)val(t)*cnt(t->l);
//     }
// }
// void split(Treap t, Treap& l, Treap& r, int val, int add=0)
// {
//     if (!t)
//     {
//         l=r=NULL;
//     }
//     else if (t->val<=val)
//     {
//         split(t->r,t->r,r,val);
//         l=t;
//     }
//     else 
//     {
//         split(t->l,l,t->l,val);
//         r=t;
//     }
//     upd_cnt(t);
    
// }
// void merge(Treap& t, Treap l, Treap r)
// {
//     if (!l || !r) t = l?l:r;
//     else if (l->prior>r->prior) 
//     {
//         merge(l->r,l->r,r);
//         t=l;
//     }
//     else
//     {
//         merge(r->l,l,r->l);
//         t=r;
//     }
//     upd_cnt(t);
// }
// void insert(Treap &t, Treap it)
// {
//     // if (!t) 
//     // {
//     //     t=it;
//     //     return;
//     // }
//     Treap r1,r2;
//     split(t,r1,r2,it->val);
//     merge(t,r1,it);
//     merge(t,t,r2);
//     // if (!t) 
//     // {
//     //     t=it;
//     // }
//     // else if (t->prior<it->prior)
//     // {
//     //     split(t,it->l,it->r,it->val);
//     //     t=it;
//     // }
//     // else
//     // {
//     //     insert (t->val<=it->val?t->r:t->l,it);
//     // }
// }



// void erase(Treap& t, int val)
// {
//     if (t)
//     {
//         if (t->val==val)
//         {
//             Treap th = t;
//             merge(t,t->l,t->r);
//             delete th;
//         }
//         else erase(val<t->val?t->l:t->r,val);
//     }
    
// }
// vector<ll> query(Treap tre, int l, int r)
// {
//     vector<ll> res(3,0);
//     Treap l1, l2, l3,l4;
//     split(tre,l1,l4,r);
//     if (!l1) return res;
//     split(l1,l2,l3,l-1);
//     res[0]=ans(l3);
//     res[1]=sum(l3);
//     res[2]=cnt(l3);
//     merge(l1,l2,l3);
//     merge(tre,l1,l4);
//     return res;
// }
// ll ceil(ll a, ll b)
// {
//     if (a<=0 || b<=0) return 0;
//     return (a+b-1)/b;

// }

// vector<pair<int,int>> radj[MAX_N];
// vector<int> adj[MAX_N], nadj[MAX_N];
// bool vis[MAX_N];
// int vin[MAX_N],low[MAX_N], node2comp[MAX_N], bel[MAX_N],up[MAX_N],down[MAX_N];
// int index,scc_ind,bel_ind;
// stack<int> st;

// void dfs_scc(int u, int p)
// {
//     vis[u]=true;
//     vin[u]=low[u]=index++;
//     st.push(u);
//     for (auto it:radj[u])
//     {
//         int v=it.first;
        
//         // if (v==p) continue;
//         if (!vis[v])
//         {
//             dfs_scc(v,it.second);
//             low[u]=min(low[u],low[v]);
//         }
//         else if (it.second^p)
//         {
//             low[u]=min(low[u],vin[v]);
//         }
//     }
//     if (low[u]==vin[u])
//     {
//         int z;
//         while(!st.empty())
//         {
//             z=st.top();
            
//             node2comp[z]=scc_ind;
//             st.pop();
//             if (z==u) break;
            
//         }
//         scc_ind++;
//     }
// }

// void dfs0(int u)
// {
//     bel[u]=bel_ind;
//     for (int v:nadj[u])
//     {
//         if (bel[v]) continue;
//         dfs0(v);
//     }
// }
// int dep[MAX_N],fa[MAX_N][30];
// void dfs1(int u,int fath){
//     fa[u][0]=fath;
//     dep[u]=dep[fath]+1;
//     for (int i=1;i<=20;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
//     for(int v:nadj[u]){
//         if(v==fath)continue;
//         dfs1(v,u);
//     }
// }
// int lca(int u,int v){
//     if(dep[u]<dep[v])swap(u,v);
//   for (int i=20;i>=0;i--)
//         if(dep[fa[u][i]]>=dep[v])
//             u=fa[u][i];
//     if(v==u)return u;
//   for (int i=20;i>=0;i--)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
//     return fa[u][0];
// }
// bool flag = true;
// void dfs2(int u, int p)
// {
//     for (int v:nadj[u])
//     {
//         if (v==p) continue;
//         dfs2(v,u);
//         up[u]+=up[v];
//         down[u]+=down[v];
//     }
//     if (up[u] && down[u])
//     {
//         flag=false;
//     }
// }


ll tre[MAX_N+1];
long long lowbit(long long x){return x-(x&(x-1));}
void add(long long val,long long x){for(;x<=MAX_N;x+=lowbit(x)){tre[x]=max(tre[x],val);}}
long long qmax(long long x){long long amax=-LINF;for(;x>0;x-=lowbit(x)){amax=max(amax,tre[x]);}return amax;}



using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int& fac) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
        {
            fac = a;
            return false;
        }
    }
    return true;
}


ll gcd (ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
ll lcm (ll a, ll b) {
    return a / gcd(a, b) * b;
}


// const int N = 10000000;
// vector<int> lp(N+1);


// // C++ program to demonstrate Range Update
// // and Range Queries using BIT
// #include <bits/stdc++.h>
// using namespace std;

// // Returns sum of arr[0..index]. This function assumes
// // that the array is preprocessed and partial sums of
// // array elements are stored in BITree[]
// int getSum(int BITree[], int index)
// {
// 	int sum = 0; // Initialize result

// 	// index in BITree[] is 1 more than the index in arr[]
// 	index = index + 1;

// 	// Traverse ancestors of BITree[index]
// 	while (index > 0) {
// 		// Add current element of BITree to sum
// 		sum += BITree[index];

// 		// Move index to parent node in getSum View
// 		index -= index & (-index);
// 	}
// 	return sum;
// }

// // Updates a node in Binary Index Tree (BITree) at given
// // index in BITree. The given value 'val' is added to
// // BITree[i] and all of its ancestors in tree.
// void updateBIT(int BITree[], int n, int index, int val)
// {
// 	// index in BITree[] is 1 more than the index in arr[]
// 	index = index + 1;

// 	// Traverse all ancestors and add 'val'
// 	while (index <= n) {
// 		// Add 'val' to current node of BI Tree
// 		BITree[index] += val;

// 		// Update index to that of parent in update View
// 		index += index & (-index);
// 	}
// }
// void updateBIT2(int BITree[], int BITree2[], int n, int index, int val)
// {
// 	// index in BITree[] is 1 more than the index in arr[]
// 	index = index + 1;

// 	// Traverse all ancestors and add 'val'
// 	while (index <= n) {
// 		// Add 'val' to current node of BI Tree
// 		BITree[index] = val*(BITree2[index]-BITree[index]);

// 		// Update index to that of parent in update View
// 		index += index & (-index);
// 	}
// }

// // Returns the sum of array from [0, x]
// int sum(int x, int BITTree1[], int BITTree2[])
// {
// 	return (getSum(BITTree1, x) * x) - getSum(BITTree2, x);
// }

// void updateRange(int BITTree1[], int BITTree2[],  int n,
// 				int val, int l, int r)
// {
// 	// Update Both the Binary Index Trees
// 	// As discussed in the article

// 	// Update BIT1
// 	updateBIT(BITTree1, n, l, val);
// 	updateBIT(BITTree1, n, r + 1, -val);

// 	// Update BIT2
// 	updateBIT(BITTree2, n, l, val * (l - 1));
// 	updateBIT(BITTree2, n, r + 1, -val * r);
// }
// void updateRange2(int BITTree1[], int BITTree2[], int BITTree3[], int BITTree4[],  int n,
// 				int val, int l, int r)
// {
// 	// Update Both the Binary Index Trees
// 	// As discussed in the article

// 	// Update BIT1
// 	updateBIT2(BITTree1,BITTree3, n, l, val);
// 	updateBIT2(BITTree1,BITTree3, n, r + 1, -val);

// 	// Update BIT2
// 	updateBIT2(BITTree2,BITTree4, n, l, val * (l - 1));
// 	updateBIT2(BITTree2,BITTree4, n, r + 1, -val * r);
// }

// int rangeSum(int l, int r, int BITTree1[], int BITTree2[])
// {
// 	// Find sum from [0,r] then subtract sum
// 	// from [0,l-1] in order to find sum from
// 	// [l,r]
// 	return sum(r, BITTree1, BITTree2)
// 		- sum(l - 1, BITTree1, BITTree2);
// }

// int* constructBITree(int n)
// {
// 	// Create and initialize BITree[] as 0
// 	int* BITree = new int[n + 1];
// 	for (int i = 1; i <= n; i++)
// 		BITree[i] = 0;

// 	return BITree;
// }

bool isPowerOfTwo(int n)
{
    if (n == 0)
        return 0;
    while (n != 1) {
        if (n % 2 != 0)
            return 0;
        n = n / 2;
    }
    return 1;
}

const int N = 10000000;
vector<int> lp(N+1);
vector<int> pr;

void init_linear_sieve(){
for (int i=2; i <= N; ++i) {
    if (lp[i] == 0) {
        lp[i] = i;
        pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= N; ++j) {
        lp[i * pr[j]] = pr[j];
        if (pr[j] == lp[i]) {
            break;
        }
    }
}
}
void sol()
{
    
    ll a,b,c,n,m,k=-1,x,res=0;
    cin >> n >> k;
    vector<ll> arr(n);

    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    bool resu=true;
    int j=n;
    for (int i=0;i<k;i++)
    {
        if (arr[j-1]<=n)
        {
            j=(j+n-arr[j-1])%n;
        }
        else
        {
            resu=false;
            break;
        }
    }
    if (resu) cout << "YES\n";
    else cout << "NO\n";

   
    return;
}




int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //precompute(MAXN);
    init_linear_sieve();
    // For Prime Checking
    // vector<int> pr;

    // for (int i=2; i <= N; ++i) {
    //     if (lp[i] == 0) {
    //         lp[i] = i;
    //         pr.push_back(i);
    //     }
    //     for (int j = 0; i * pr[j] <= N; ++j) {
    //         lp[i * pr[j]] = pr[j];
    //         if (pr[j] == lp[i]) {
    //             break;
    //         }
    //     }
    // }
    
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}