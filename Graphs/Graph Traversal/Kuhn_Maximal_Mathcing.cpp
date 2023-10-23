// Kuhn Maximal Bipartite matching.

#include <bits/stdc++.h>

using namespace std;
 
const int MAXN = 105;
 
int n, m;
vector <int> g[MAXN];
bool used[MAXN];
int mt[MAXN];
int ans;
 
bool kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i];
        if (mt[to] == 0 || kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }   
    return false;
}
 
int main() {
    //assert(freopen("input.txt","r",stdin));
    //assert(freopen("output.txt","w",stdout));
 
    scanf("%d %d", &n, &m);
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int can;
            scanf("%d", &can);
            if (can)
                g[i].push_back(j);
        }
    }
 
    for (int i = 1; i <= n; i++) {
        memset(used, 0, sizeof(used));
        if (kuhn(i))
            ans++;
    }
 
    printf("%d\n", ans);
 
    return 0;
}