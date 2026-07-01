#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const double EPS = 1e-9;
const int INF = 1e9;

// === GEOMETRY PRIMITIVES (2D & 3D) ===
struct pt {
    double x, y;
    pt operator+(const pt& p) const { return {x + p.x, y + p.y}; }
    pt operator-(const pt& p) const { return {x - p.x, y - p.y}; }
    pt operator*(const double& d) const { return {x * d, y * d}; }
    pt operator/(const double& d) const { return {x / d, y / d}; }
    double cross(const pt& p) const { return x * p.y - y * p.x; }
    double cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
    double dot(const pt& p) const { return x * p.x + y * p.y; }
    double dot(const pt& a, const pt& b) const { return (a - *this).dot(b - *this); }
    double sqrLen() const { return dot(*this); }
    double len() const { return sqrt(sqrLen()); }
    pt perp() const { return {-y, x}; }
    pt rotate(double a) const { return {x*cos(a) - y*sin(a), x*sin(a) + y*cos(a)}; }
    bool operator<(const pt& p) const { return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS); }
    bool operator>(const pt& p) const { return p < *this; }
    bool operator==(const pt& p) const { return abs(x - p.x) < EPS && abs(y - p.y) < EPS; }
    friend istream& operator>>(istream& in, pt& p) { return in >> p.x >> p.y; }
    friend ostream& operator<<(ostream& out, const pt& p) { return out << "(" << p.x << "," << p.y << ")"; }
};

struct pt3 {
    double x, y, z;
    pt3 operator+(const pt3& p) const { return {x + p.x, y + p.y, z + p.z}; }
    pt3 operator-(const pt3& p) const { return {x - p.x, y - p.y, z - p.z}; }
    pt3 operator*(double d) const { return {x * d, y * d, z * d}; }
    pt3 operator/(double d) const { return {x / d, y / d, z / d}; }
    double dot(const pt3& p) const { return x * p.x + y * p.y + z * p.z; }
    pt3 cross(const pt3& p) const { return {y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x}; }
    double triple(const pt3& b, const pt3& c) const { return dot(b.cross(c)); }
};

struct circle : pt { double r; };

struct line {
    double a, b, c;
    line() {}
    line(pt p, pt q) { a = p.y - q.y; b = q.x - p.x; c = -a * p.x - b * p.y; norm(); }
    void norm() { double z = sqrt(a * a + b * b); if (abs(z) > EPS) a /= z, b /= z, c /= z; }
    double dist(pt p) const { return a * p.x + b * p.y + c; }
};

// === BASIC HELPERS ===
double sqr(double a) { return a * a; }
double det(double a, double b, double c, double d) { return a * d - b * c; }
int sgn(double x) { return (x > EPS) - (x < -EPS); }
bool betw(double l, double r, double x) { return min(l, r) <= x + EPS && x <= max(l, r) + EPS; }
bool intersect_1d(double a, double b, double c, double d) { if (a > b) swap(a, b); if (c > d) swap(c, d); return max(a, c) <= min(b, d) + EPS; }

// === LINE & SEGMENT INTERSECTIONS ===
bool parallel(line m, line n) { return abs(det(m.a, m.b, n.a, n.b)) < EPS; }
bool equivalent(line m, line n) { return parallel(m, n) && abs(det(m.a, m.c, n.a, n.c)) < EPS && abs(det(m.b, m.c, n.b, n.c)) < EPS; }
bool intersect_lines(line m, line n, pt& res) { double zn = det(m.a, m.b, n.a, n.b); if (abs(zn) < EPS) return false; res.x = -det(m.c, m.b, n.c, n.b) / zn; res.y = -det(m.a, m.c, n.a, n.c) / zn; return true; }

// Fast boolean check for segment intersection in O(1)
bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (abs(c.cross(a, d)) < EPS && abs(c.cross(b, d)) < EPS) return intersect_1d(a.x, b.x, c.x, d.x) && intersect_1d(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) && sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}

// Compute exact segment intersection into interval [left, right]
bool intersect_segments(pt a, pt b, pt c, pt d, pt& left, pt& right) {
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y)) return false;
    line m(a, b), n(c, d); double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS) { if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS) return false; if (b < a) swap(a, b); if (d < c) swap(c, d); left = max(a, c); right = min(b, d); return true; }
    left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn; left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
    return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) && betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
}

// === SWEEP LINE ALGORITHMS ===
// Calculate the length of the union of multiple 1D segments in O(N log N)
int length_union(const vector<pair<int, int>>& a) {
    vector<pair<int, bool>> x(a.size() * 2); for (size_t i = 0; i < a.size(); i++) { x[i * 2] = {a[i].first, 0}; x[i * 2 + 1] = {a[i].second, 1}; }
    sort(x.begin(), x.end()); int res = 0, c = 0;
    for (size_t i = 0; i < x.size(); i++) { if (i > 0 && x[i].first > x[i - 1].first && c > 0) res += x[i].first - x[i - 1].first; x[i].second ? c-- : c++; } return res;
}

// Area of union of orthogonal rectangles in O(N^2) (Compressible to N log N with SegTree)
ll rectangle_union_area(vector<array<int,4>> rects) { // {x1, y1, x2, y2}
    struct Event { ll x, y1, y2, val; bool operator<(const Event& o) const { return x < o.x; } };
    vector<Event> ev; for (auto r : rects) { ev.push_back({r[0], r[1], r[3], 1}); ev.push_back({r[2], r[1], r[3], -1}); }
    sort(ev.begin(), ev.end()); ll area = 0, last_x = ev[0].x; vector<pair<ll, ll>> act; 
    for (auto e : ev) {
        ll w = e.x - last_x, cov = 0, cur_y = -INF; sort(act.begin(), act.end());
        for (auto p : act) { if (p.first > cur_y) { cov += p.second - p.first; cur_y = p.second; } else if (p.second > cur_y) { cov += p.second - cur_y; cur_y = p.second; } }
        area += w * cov; last_x = e.x;
        if (e.val == 1) act.push_back({e.y1, e.y2}); else act.erase(find(act.begin(), act.end(), make_pair(e.y1, e.y2)));
    } return area;
}

// Find closest pair of points in O(N log N)
double closest_pair(vector<pt> p) {
    sort(p.begin(), p.end()); set<pair<double, double>> s; double d = INF; int l = 0;
    for (int i = 0; i < p.size(); i++) {
        while (l < i && p[i].x - p[l].x >= d) { s.erase({p[l].y, p[l].x}); l++; }
        for (auto it = s.lower_bound({p[i].y - d, p[i].x - d}); it != s.end() && it->first - p[i].y <= d; it++) d = min(d, hypot(p[i].x - it->second, p[i].y - it->first));
        s.insert({p[i].y, p[i].x});
    } return d;
}

// Bentley-Ottmann: Check if ANY two segments intersect in O(N log N)
struct Seg { pt p, q; int id; double get_y(double x) const { if(abs(p.x - q.x) < EPS) return p.y; return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x); } };
bool operator<(const Seg& a, const Seg& b) { double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x)); return a.get_y(x) < b.get_y(x) - EPS; }
bool any_segment_intersect(vector<pair<pt,pt>>& segs) {
    struct Event { double x; int type, id; bool operator<(const Event& e) const { return x < e.x - EPS || (abs(x - e.x) < EPS && type > e.type); } };
    vector<Event> ev; for (int i = 0; i < segs.size(); i++) { ev.push_back({min(segs[i].first.x, segs[i].second.x), 1, i}); ev.push_back({max(segs[i].first.x, segs[i].second.x), -1, i}); }
    sort(ev.begin(), ev.end()); set<Seg> s; vector<set<Seg>::iterator> where(segs.size());
    for (auto e : ev) {
        int id = e.id; Seg cur = {segs[id].first, segs[id].second, id};
        if (e.type == 1) {
            auto nxt = s.lower_bound(cur);
            if (nxt != s.end() && check_inter(cur.p, cur.q, nxt->p, nxt->q)) return true;
            if (nxt != s.begin() && check_inter(cur.p, cur.q, prev(nxt)->p, prev(nxt)->q)) return true;
            where[id] = s.insert(nxt, cur);
        } else {
            auto nxt = next(where[id]), prv = (where[id] == s.begin() ? s.end() : prev(where[id]));
            if (nxt != s.end() && prv != s.end() && check_inter(nxt->p, nxt->q, prv->p, prv->q)) return true;
            s.erase(where[id]);
        }
    } return false;
}

// === POLYGONS ===
// Area of polygon in O(N)
double polygon_area(const vector<pt>& p) { double a = 0; for(int i=0, n=p.size(); i<n; i++) a += p[i].cross(p[(i+1)%n]); return abs(a)/2.0; }

// Check if point inside Convex Polygon in O(log N)
bool point_in_triangle(pt a, pt b, pt c, pt p) { return abs(abs(a.cross(b, c)) - (abs(p.cross(a, b)) + abs(p.cross(b, c)) + abs(p.cross(c, a)))) < EPS; }
bool point_in_convex_polygon(const vector<pt>& p, pt pt) {
    int n = p.size(); if (n < 3) return false;
    if (p[0].cross(p[1], pt) < -EPS || p[0].cross(p[n-1], pt) > EPS) return false;
    int l = 1, r = n - 1; while (r - l > 1) { int m = (l + r) / 2; if (p[0].cross(p[m], pt) >= 0) l = m; else r = m; }
    return point_in_triangle(p[0], p[l], p[l+1], pt);
}

// Convex Hull (Monotone Chain) in O(N log N)
vector<pt> convex_hull(vector<pt> a) {
    if (a.size() <= 1) return a; sort(a.begin(), a.end()); vector<pt> up, dn;
    for (pt p : a) {
        while (up.size() > 1 && up[up.size()-2].cross(up.back(), p) >= 0) up.pop_back();
        while (dn.size() > 1 && dn[dn.size()-2].cross(dn.back(), p) <= 0) dn.pop_back();
        up.push_back(p); dn.push_back(p);
    } a = dn; for (int i = (int)up.size() - 2; i > 0; i--) a.push_back(up[i]); return a;
}

// Minkowski Sum of Polygons in O(N)
void reorder_polygon(vector<pt>& P) {
    size_t pos = 0; for (size_t i = 1; i < P.size(); i++) if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
    rotate(P.begin(), P.begin() + pos, P.end());
}
vector<pt> minkowski(vector<pt> P, vector<pt> Q) {
    reorder_polygon(P); reorder_polygon(Q); P.push_back(P[0]); P.push_back(P[1]); Q.push_back(Q[0]); Q.push_back(Q[1]);
    vector<pt> res; size_t i = 0, j = 0;
    while (i < P.size() - 2 || j < Q.size() - 2) {
        res.push_back(P[i] + Q[j]); auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if (cross >= 0 && i < P.size() - 2) ++i; if (cross <= 0 && j < Q.size() - 2) ++j;
    } return res;
}

// === CIRCLES ===
// Intersection of circle (0,0) radius r and line ax+by+c=0 (Graphical Method)
vector<pt> circle_line_intersect(double r, double a, double b, double c) {
    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS) return {};
    if (abs(c * c - r * r * (a * a + b * b)) < EPS) return {{x0, y0}};
    double d = r * r - c * c / (a * a + b * b), m = sqrt(d / (a * a + b * b));
    return {{x0 + b * m, y0 - a * m}, {x0 - b * m, y0 + a * m}};
}

// Common Tangents of Two Circles (Algebraic Method)
void tangents_helper(pt c, double r1, double r2, vector<line>& ans) {
    double r = r2 - r1, z = sqr(c.x) + sqr(c.y), d = z - sqr(r); if (d < -EPS) return;
    d = sqrt(abs(d)); line l; l.a = (c.x * r + c.y * d) / z; l.b = (c.y * r - c.x * d) / z; l.c = r1; ans.push_back(l);
}
vector<line> tangents(circle a, circle b) {
    vector<line> ans; for (int i = -1; i <= 1; i += 2) for (int j = -1; j <= 1; j += 2) tangents_helper(b - a, a.r * i, b.r * j, ans);
    for (auto& l : ans) l.c -= l.a * a.x + l.b * a.y; return ans;
}

// === CONVEX HULL TRICK (Li-Chao Segment Tree for Lines y = mx + c) ===
struct LiChao {
    struct Line { ll m, c; ll operator()(ll x) const { return m * x + c; } };
    vector<Line> tree; int n;
    LiChao(int n) : n(n), tree(4 * n, {0, (ll)INF*INF}) {} // Init with INF intercept
    void add_line(Line nw, int v = 1, int l = 0, int r = -1) {
        if (r == -1) r = n; int m = (l + r) / 2;
        bool lef = nw(l) < tree[v](l), mid = nw(m) < tree[v](m);
        if (mid) swap(tree[v], nw);
        if (r - l == 1) return; else if (lef != mid) add_line(nw, 2 * v, l, m); else add_line(nw, 2 * v + 1, m, r);
    }
    ll get(int x, int v = 1, int l = 0, int r = -1) {
        if (r == -1) r = n; int m = (l + r) / 2;
        if (r - l == 1) return tree[v](x);
        return min(tree[v](x), x < m ? get(x, 2 * v, l, m) : get(x, 2 * v + 1, m, r));
    }
};

// === SOLVE & MAIN ===
void solve() {
    // Template entry point
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int tc = 1; 
    // cin >> tc;
    while (tc--) solve();
    return 0;
}