// Treap data structure supporting split and merge function
// Problem link: https://codeforces.com/gym/102787/problem/A

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// typedef struct item * pitem;
// struct item {
//     int prior, value, cnt;
//     bool rev;
//     pitem l, r;
// };

// int cnt (pitem it) {
//     return it ? it->cnt : 0;
// }

// void upd_cnt (pitem it) {
//     if (it)
//         it->cnt = cnt(it->l) + cnt(it->r) + 1;
// }

// void push (pitem it) {
//     if (it && it->rev) {
//         it->rev = false;
//         swap (it->l, it->r);
//         if (it->l)  it->l->rev ^= true;
//         if (it->r)  it->r->rev ^= true;
//     }
// }

// void merge (pitem & t, pitem l, pitem r) {
//     push (l);
//     push (r);
//     if (!l || !r)
//         t = l ? l : r;
//     else if (l->prior > r->prior)
//         merge (l->r, l->r, r),  t = l;
//     else
//         merge (r->l, l, r->l),  t = r;
//     upd_cnt (t);
// }

// void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
//     if (!t)
//         return void( l = r = 0 );
//     push (t);
//     int cur_key = add + cnt(t->l);
//     if (key <= cur_key)
//         split (t->l, l, t->l, key, add),  r = t;
//     else
//         split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
//     upd_cnt (t);
// }

// void reverse (pitem t, int l, int r) {
//     pitem t1, t2, t3;
//     split (t, t1, t2, l);
//     split (t2, t2, t3, r-l+1);
//     t2->rev ^= true;
//     merge (t, t1, t2);
//     merge (t, t, t3);
// }

// void output (pitem t) {
//     if (!t)  return;
//     push (t);
//     output (t->l);
//     printf ("%d ", t->value);
//     output (t->r);
// }


// Treap data structure supporting split and merge function
// Problem link: https://codeforces.com/gym/102787/problem/A

struct tdata {
    int  pri, sz;
    char val;
    bool rev;
    tdata *ln, *rn;
    tdata(char val): val(val), pri(rng()), sz(1), ln(), rn() {} 
};
int sz(tdata *node) {return node ? node->sz : 0;}
void propagate(tdata *node) {
    if (node && node->rev) {
        node->rev = false;
        swap (node->ln, node->rn);
        if (node->ln)  node->ln->rev ^= true;
        if (node->rn)  node->rn->rev ^= true;
    }
    if (!node) return;
}
void combine(tdata *node) {
    
    
    if (!node) return;
    propagate(node->ln); propagate(node->rn);
    node->sz = sz(node->ln) + sz(node->rn) + 1;
}
void heapify(tdata *node) {
    if (!node) return;
    auto mx = node;
    if (node->ln && node->ln->pri > node->pri) mx = node;
    if (node->rn && node->rn->pri > node->pri) mx = node;
    if (node != mx) {
        swap(node->pri, mx->pri);
        heapify(mx);
    }
}
tdata* build(vector<char> &arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    auto node = new tdata(arr[mid]);
    node->ln = build(arr, start, mid - 1);
    node->rn = build(arr, mid + 1, end);
    heapify(node); combine(node);
    return node;
}
void push (tdata* it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->ln, it->rn);
        if (it->ln)  it->ln->rev ^= true;
        if (it->rn)  it->rn->rev ^= true;
    }
}

void split(tdata *node, tdata *&ln, tdata *&rn, int k) { // k nodes to ln
    // push(node);
    propagate(node);
    if (!node) {
        ln = rn = NULL;
        return;
    }
    
    if (sz(node->ln) >= k) split(node->ln, ln, node->ln, k), rn = node;
    else split(node->rn, node->rn, rn, k - sz(node->ln) - 1), ln = node;
    combine(node);
}
void merge(tdata *&node, tdata *ln, tdata *rn) {
    // push(ln); push(rn);
    propagate(ln); propagate(rn);
    if (!ln || !rn) {
        node = ln ? ln : rn;
        return;
    }
    if (ln->pri > rn->pri) merge(ln->rn, ln->rn, rn), node = ln;
    else merge(rn->ln, ln, rn->ln), node = rn;
    combine(node);
}
void reverse (tdata *&t, int l, int r) {
    tdata *t1, *t2, *t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}
void print(tdata *node) {
    if (!node) return;
    print(node->ln);
    cout << node->val;
    print(node->rn);
}


void solve() {
    ll n,k,q,x; 
    cin >> n >> k;
    vector<int> mp(2*MAX_N),l(k),r(k);
    vector<char> arr(n);
    string si;
    cin >> si;
    for (int i=0;i<n;i++)
    {
        arr[i]=si[i];
    }
    
    
    for (int i=0;i<k;i++) cin >> l[i];
    for (int i=0;i<k;i++) 
    {
        cin >> r[i];
        for (int j=l[i];j<=r[i];j++) mp[j]=i;
        
    }
    auto tr = build(arr, 0, n - 1);
    cin >> q;
    for (int i=0;i<q;i++)
    {
        cin >> x;
        int x1,y1,a,b;
        x1 = l[mp[x]];
        y1 = r[mp[x]];
        a = min(x,x1+y1-x);
        b = max(x,x1+y1-x);
        

        if (a >= b) continue;
        reverse(tr,a-1,b-1);
        print(tr);
    }
    
    
    print(tr);
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}