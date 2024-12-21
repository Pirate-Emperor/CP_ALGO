// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

// Graham's scan Algorithm -> Polar Angle Sorting and Orientation Comparison to finding the convex hull
struct pt {
    long long x, y;
    pt() {}
    pt(long long _x, long long _y) : x(_x), y(_y) {}
    
    friend std::ostream& operator<<(std::ostream& out, const pt& p) { return out << "(" << p.x << "," << p.y << ")"; }
    friend std::istream& operator>>(std::istream& in, pt& p) { return in >> p.x >> p.y; }

    pt operator+(const pt &p) const { return pt(x + p.x, y + p.y); }
    pt operator-(const pt &p) const { return pt(x - p.x, y - p.y); }
    long long cross(const pt &p) const { return x * p.y - y * p.x; }
    long long dot(const pt &p) const { return x * p.x + y * p.y; }
    long long cross(const pt &a, const pt &b) const { return (a - *this).cross(b - *this); }
    long long dot(const pt &a, const pt &b) const { return (a - *this).dot(b - *this); }
    long long sqrLen() const { return this->dot(*this); }
};

int orientation(pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(pt a, pt b, pt c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<pt>& a, bool include_collinear = false) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    a = st;
}

void solve() {
    int n; cin >> n;
    long double res=0.000000000000;
    vector<pt> a(n);
    
    for (pt &p : a) cin >> p;
    cout << fixed << setprecision(18);
    if (a.size()==1) 
    {
        cout << -1 << endl;
        return;
    }
    bool check=true;
    for (int i=1;i<a.size();i++)
    {
        auto t1 = a[i];
        auto t2 = a[i-1];
        long double sl = (long double)(t1.y-0);
        sl/=(long double)(t1.x-0);
        long double sl2 = (long double)(0-t2.y);
        sl2/=(long double)(0-t2.x);
        if (sl!=sl2) check=false;
    }
    if (check==true)
    {
        cout << res << endl;
        return;
    }
    // a.push_back(pt(0,0));
    convex_hull(a,true);
    int m = a.size();
    
    for (int i=1;i<m;i++)
    {
        auto t1 = a[i];
        auto t2 = a[i-1];
        long double sl = (long double)(t1.y-t2.y)*(-t1.x);
        sl/=(long double)(t1.x-t2.x);
        long double tem = sl + t1.y;
        res=max(res,tem);
    }
    if (res==0) 
    {
        res=-1;
        cout << setprecision(0);
        cout << res << endl;
        return;
    }
    else 
    res=res-(long double)1e-20;
    cout << res << "\n";
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