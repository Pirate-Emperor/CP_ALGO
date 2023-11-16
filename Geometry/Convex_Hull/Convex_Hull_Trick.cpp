// DP Optimization of finding minimum/maximum of set of kx+b for a paricular x
// Forming a convex hull -> Collection of points such that y-coordinate for a paticular x is smallest/highest
// Representing kx+b as dot product of (k,b) and (x,1)
// Segment Tree containing vertex as (k,b) where path to leaf node will yield the minimum (k,b)

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

ftype f(point a,  ftype x) {
    return dot(a, {x, 1});
}
// We will keep functions in the array line and use binary indexing of the segment tree.
// If you want to use it on large numbers or doubles, you should use a dynamic segment tree.
// The segment tree should be initialized with default values, e.g. with lines 0x + infty.
const int maxn = 2e5;

point line[4 * maxn];

void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if(mid) {
        swap(line[v], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}

//Now to get the minimum in some point  
//x we simply choose the minimum value along the path to the point.
ftype get(int x, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(line[v], x);
    } else if(x < m) {
        return min(f(line[v], x), get(x, 2 * v, l, m));
    } else {
        return min(f(line[v], x), get(x, 2 * v + 1, m, r));
    }
}


void solve() {
    int n; cin >> n;
    vector<pt> a(n);
    for (pt &p : a) cin >> p;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}