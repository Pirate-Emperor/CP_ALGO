#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define all(x) x.begin(), x.end()
 
using namespace __gnu_pbds; using namespace std;
 
template<class T> using ordered_set = tree<T, null_type , less<T> , rb_tree_tag , tree_order_statistics_node_update>; template<class T> using ordered_multiset = tree<T, null_type , less_equal<T> , rb_tree_tag , tree_order_statistics_node_update>; typedef long long ll;  typedef pair<int, int> ii;  typedef tuple<int, int, int> iii; typedef tuple<int, int, int, int> iiii; typedef vector<int> vi; 
const ll oo = 1e9 + 7;
 
template<class It> void db(It b, It e) { for (auto it = b; it != e; it++) cout << *it << ' '; cout<< endl; } template<typename A> istream& operator>>(istream& fin, vector<A>& v) { for (auto it = v.begin(); it != v.end(); ++it) fin >> *it; return fin; } template<typename A, typename B> istream& operator>>(istream& fin, pair<A, B>& p){ fin >> p.first >> p.second; return fin; } template<typename T> void chmin(T &a, T b){ a = min(a, b); } template<typename T> void chmax(T &a, T b){ a = max(a, b); } template <typename T, typename S> ostream& operator<<(ostream& os, const pair<T, S>& v) { os << "(" << v.first << "," << v.second << ")"; return os; }
 
const int MAX = 4123;
int c[MAX][MAX];
int pref[MAX + 1][MAX + 1];
int dp[2][MAX], K;
int n, k;
 
int read() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int ret = 0;
	while (c >= '0' && c <= '9') ret = ret*10 + (c - '0'), c = getchar();
	return ret;
}
 
inline int getbit(int lx, int ly, int rx, int ry) {  // entrada - fechado
  rx++;                                       // aberto
  ry++;
  return pref[rx][ry] - pref[rx][ly] - pref[lx][ry] + pref[lx][ly];
}
 
void solve(int l, int r, int optl, int optr){
    if (l > r) return;
    int mid = (l + r)/2;
    ii mi = {oo, -1};
    for (int pos=optl; pos <= min(mid, optr); pos++){
        chmin(mi, {(pos == 0 ?  0 : dp[(K & 1)^1][pos - 1]) + c[pos][mid], pos});
    }
    int opt = mi.second;
    dp[(K & 1)][mid] = mi.first;
    solve(l, mid - 1, optl, opt);
    solve(mid + 1, r, opt, optr);
}
 
 
 
signed main(){
    n = read();
    k = read();
    for (int i=0; i < n; i++){
        dp[0][i] = oo;
        for (int j=0; j < n; j++){
            int x = read();
            pref[i + 1][j + 1] = pref[i + 1][j] + pref[i][j + 1] - pref[i][j] + x;
            // cout << pref[i + 1][j + 1] << " ";
        }
        // cout << endl;
    }
    for (int i=0; i < n; i++){
        for (int j=i; j < n; j++){
            c[i][j] = getbit(i, i, j, j);
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    for (int kk=1; kk <= k; kk++){
        K = kk;
        solve(0, n - 1, 0, n - 1);
    }
    printf("%d\n", dp[K & 1][n - 1] / 2);
}