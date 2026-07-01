#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

// ==========================================
// Z-ALGORITHM
// ==========================================
vector<int> z_func(const string& s) {
    int n = s.size(); vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

// ==========================================
// KMP (PREFIX FUNCTION)
// ==========================================
vector<int> prefix_func(const string& s) {
    int n = s.size(); vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        pi[i] = j + (s[i] == s[j]);
    }
    return pi;
}
void compute_automaton(string s, vector<vector<int>>& aut) {
    s += '#'; int n = s.size(); aut.assign(n, vector<int>(26));
    vector<int> pi = prefix_func(s);
    for (int i = 0; i < n; i++) for (int c = 0; c < 26; c++)
        aut[i][c] = (i > 0 && 'a' + c != s[i]) ? aut[pi[i - 1]][c] : i + ('a' + c == s[i]);
}

// ==========================================
// MANACHER'S ALGORITHM
// ==========================================
vector<int> manacher(string s) {
    int n = s.size(), l = 1, r = 1; s = "$" + s + "^"; vector<int> p(n + 2);
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) p[i]++;
        if (i + p[i] > r) l = i - p[i], r = i + p[i];
    }
    return vector<int>(p.begin() + 1, p.end() - 1);
}
vector<int> manacher_even(string s) {
    string t; for (char c : s) t += string("#") + c;
    auto res = manacher(t + "#");
    return vector<int>(res.begin() + 1, res.end() - 1);
}

// ==========================================
// LYNDON FACTORIZATION
// ==========================================
vector<string> duval(const string& s) {
    int n = s.size(), i = 0; vector<string> fact;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) { s[k] < s[j] ? k = i : k++; j++; }
        while (i <= k) { fact.push_back(s.substr(i, j - k)); i += j - k; }
    }
    return fact;
}
string min_cyclic_string(string s) {
    s += s; int n = s.size(), i = 0, ans = 0;
    while (i < n / 2) {
        ans = i; int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) { s[k] < s[j] ? k = i : k++; j++; }
        while (i <= k) i += j - k;
    }
    return s.substr(ans, n / 2);
}

// ==========================================
// STRING HASHING (RABIN-KARP)
// ==========================================
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int BASE = uniform_int_distribution<ll>(300, 1e9)(rng);
const ll MODS[] = {(ll)1e9 + 2277, (ll)1e9 + 5277};
struct Hash {
    vector<ll> H[2], P[2];
    Hash(string s) {
        for (int i = 0; i < 2; i++) P[i].assign(1, 1), H[i].assign(1, 0);
        for (char c : s) for (int i = 0; i < 2; i++) {
            P[i].push_back(P[i].back() * BASE % MODS[i]);
            H[i].push_back((H[i].back() * BASE + c) % MODS[i]);
        }
    }
    array<ll, 2> operator()(int l, int r) {
        array<ll, 2> res;
        for (int i = 0; i < 2; i++) {
            res[i] = (H[i][r + 1] - H[i][l] * P[i][r + 1 - l]) % MODS[i];
            if (res[i] < 0) res[i] += MODS[i];
        }
        return res;
    }
};

// ==========================================
// AHO-CORASICK AUTOMATON
// ==========================================
struct AhoCorasick {
    struct Node {
        int next[26], go[26], p = -1, link = -1; char pch; bool out = false;
        Node(int p = -1, char ch = '$') : p(p), pch(ch) {
            fill(begin(next), end(next), -1); fill(begin(go), end(go), -1);
        }
    };
    vector<Node> t = {Node()};
    void add(string s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) { t[v].next[c] = t.size(); t.emplace_back(v, ch); }
            v = t[v].next[c];
        }
        t[v].out = true;
    }
    int get_link(int v) {
        if (t[v].link == -1) t[v].link = (v == 0 || t[v].p == 0) ? 0 : go(get_link(t[v].p), t[v].pch);
        return t[v].link;
    }
    int go(int v, char ch) {
        int c = ch - 'a';
        if (t[v].go[c] == -1)
            t[v].go[c] = (t[v].next[c] != -1) ? t[v].next[c] : (v == 0 ? 0 : go(get_link(v), ch));
        return t[v].go[c];
    }
};

// ==========================================
// EXPRESSION PARSING
// ==========================================
namespace Expr {
    int prio(char op) { return op < 0 ? 3 : (op == '+' || op == '-' ? 1 : (op == '*' || op == '/' ? 2 : -1)); }
    void proc(stack<int>& st, char op) {
        if (op < 0) { int l = st.top(); st.pop(); st.push(-op == '+' ? l : -l); }
        else {
            int r = st.top(); st.pop(); int l = st.top(); st.pop();
            st.push(op == '+' ? l+r : (op == '-' ? l-r : (op == '*' ? l*r : l/r)));
        }
    }
    int eval(string s) {
        stack<int> st; stack<char> op; bool may_unary = true;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == ' ') continue;
            if (s[i] == '(') { op.push('('); may_unary = true; }
            else if (s[i] == ')') {
                while (op.top() != '(') { proc(st, op.top()); op.pop(); }
                op.pop(); may_unary = false;
            } else if (string("+-*/").find(s[i]) != string::npos) {
                char cur = (may_unary && (s[i] == '+' || s[i] == '-')) ? -s[i] : s[i];
                while (!op.empty() && ((cur >= 0 && prio(op.top()) >= prio(cur)) || (cur < 0 && prio(op.top()) > prio(cur))))
                    { proc(st, op.top()); op.pop(); }
                op.push(cur); may_unary = true;
            } else {
                int val = 0; while (i < (int)s.size() && isalnum(s[i])) val = val * 10 + s[i++] - '0';
                i--; st.push(val); may_unary = false;
            }
        }
        while (!op.empty()) { proc(st, op.top()); op.pop(); }
        return st.top();
    }
}

// ==========================================
// REPETITIONS
// ==========================================
namespace Repetitions {
    vector<pair<int, int>> reps;
    void add(int sh, bool L, int cntr, int l, int k1, int k2) {
        for (int l1 = max(1, l - k2); l1 <= min(l, k1); l1++) {
            if (L && l1 == l) break;
            int pos = sh + (L ? cntr - l1 : cntr - l - l1 + 1);
            reps.emplace_back(pos, pos + 2 * l - 1);
        }
    }
    void find(string s, int sh = 0) {
        int n = s.size(); if (n == 1) return;
        int nu = n / 2, nv = n - nu; string u = s.substr(0, nu), v = s.substr(nu);
        string ru(u.rbegin(), u.rend()), rv(v.rbegin(), v.rend());
        find(u, sh); find(v, sh + nu);
        auto z1 = z_func(ru), z2 = z_func(v + '#' + u), z3 = z_func(ru + '#' + rv), z4 = z_func(v);
        auto get_z = [](const vector<int>& z, int i) { return (i >= 0 && i < (int)z.size()) ? z[i] : 0; };
        for (int c = 0; c < n; c++) {
            int l, k1, k2;
            if (c < nu) l = nu - c, k1 = get_z(z1, nu - c), k2 = get_z(z2, nv + 1 + c);
            else l = c - nu + 1, k1 = get_z(z3, n - 1 - (c - nu)), k2 = get_z(z4, c - nu + 1);
            if (k1 + k2 >= l) add(sh, c < nu, c, l, k1, k2);
        }
    }
}

// ==========================================
// SUFFIX ARRAY & LCP
// ==========================================
struct SuffixArray {
    vector<int> p, c, lcp;
    SuffixArray(string s) {
        s += "$"; int n = s.size(), classes = 1;
        p.resize(n); c.resize(n); vector<int> cnt(max(256, n), 0), pn(n), cn(n);
        for(char ch : s) cnt[ch]++;
        for(int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
        for(int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
        for(int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i - 1]]) classes++;
            c[p[i]] = classes - 1;
        }
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) pn[i] = (p[i] - (1 << h) + n) % n;
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int x : pn) cnt[c[x]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0; classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev) classes++;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        p.erase(p.begin()); // remove '$'

        n--; vector<int> rank(n); lcp.assign(n - 1, 0);
        for (int i = 0; i < n; i++) rank[p[i]] = i;
        for (int i = 0, k = 0; i < n; i++) {
            if (rank[i] == n - 1) { k = 0; continue; }
            int j = p[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
            if (k) k--;
        }
    }
};

// ==========================================
// SUFFIX TREE
// ==========================================
struct SuffixTree {
    struct Node {
        int l, r, par, link; map<char, int> next;
        Node(int l = 0, int r = 0, int p = -1) : l(l), r(r), par(p), link(-1) {}
        int len() { return r - l; }
        int& get(char c) { if (!next.count(c)) next[c] = -1; return next[c]; }
    };
    string s; int n, sz; vector<Node> t;
    struct State { int v, pos; }; State ptr{0, 0};
    
    SuffixTree(string str) : s(str), n(str.size()), sz(1), t(2 * n + 5) {
        for (int i = 0; i < n; ++i) extend(i);
    }
    State go(State st, int l, int r) {
        while (l < r) {
            if (st.pos == t[st.v].len()) {
                st = {t[st.v].get(s[l]), 0}; if (st.v == -1) return st;
            } else {
                if (s[t[st.v].l + st.pos] != s[l]) return {-1, -1};
                if (r - l < t[st.v].len() - st.pos) return {st.v, st.pos + r - l};
                l += t[st.v].len() - st.pos; st.pos = t[st.v].len();
            }
        }
        return st;
    }
    int split(State st) {
        if (st.pos == t[st.v].len()) return st.v;
        if (st.pos == 0) return t[st.v].par;
        Node v = t[st.v]; int id = sz++;
        t[id] = Node(v.l, v.l + st.pos, v.par);
        t[v.par].get(s[v.l]) = id; t[id].get(s[v.l + st.pos]) = st.v;
        t[st.v].par = id; t[st.v].l += st.pos;
        return id;
    }
    int get_link(int v) {
        if (t[v].link != -1) return t[v].link;
        if (t[v].par == -1) return 0;
        int to = get_link(t[v].par);
        return t[v].link = split(go({to, t[to].len()}, t[v].l + (t[v].par == 0), t[v].r));
    }
    void extend(int pos) {
        for (;;) {
            State nptr = go(ptr, pos, pos + 1);
            if (nptr.v != -1) { ptr = nptr; return; }
            int mid = split(ptr), leaf = sz++;
            t[leaf] = Node(pos, n, mid); t[mid].get(s[pos]) = leaf;
            ptr.v = get_link(mid); ptr.pos = t[ptr.v].len();
            if (!mid) break;
        }
    }
};

// ==========================================
// SOLVE & MAIN
// ==========================================
void solve() {
    string s; cin >> s;
    ll n = s.length();
    cout << (n * (n + 1)) / 2 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc = 1; 
    // cin >> tc;
    while (tc--) solve();
    return 0;
}