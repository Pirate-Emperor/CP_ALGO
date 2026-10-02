#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
const int INF=1e9;
const int MOD=1e9+7; // 1e9+9 or 998244353
const ll LINF=1e18;
// Batch-5

bool is_goal(){ return false;}

bool backtrack(int r, int c, vector<vector<bool>>& vis, const vector<vector<int>>& grid){
    if (is_goal()) return true;
    int ri[4]={0,1,0,-1}, ci[4]={1,0,-1,0};
    for (int i=0;i<4;i++){
        int nr=ri[i]+r,nc=ci[i]+c;
        if (nr<0 || nc<0 || nr>=grid.size() || nc>=grid[0].size()) continue;
        vis[nr][nc]=true;
        if (backtrack(nr,nc,vis,grid)) return true;
        vis[nr][nc]=false;
    }
    return false;
}

vector<vector<int>> bitmask(int n, int u, const vector<vector<int>>& grid){
    vector<vector<int>> dp(n,vector<int>(1<<n,INF));
    dp[u][0]=0;
    for (int mask=0;mask<(1<<n);mask++){
        for (int ui=0;ui<n;ui++){
            if (dp[ui][mask]==INF) continue;
            for (int i=0;i<n;i++){
                if (mask&(1<<i)==0){
                    int nmask=mask^(1<<i);
                    dp[i][nmask]=min(dp[i][nmask],grid[ui][i]+dp[ui][mask]);
                }
            }
        }
    }
    return dp;
}

string num; // flag=0 means that limit is till the num[i]
long long dp[20][180][2]; // Reset this to have -1 value everywhere
long long digit_dp(int pos, int sum, int flag){
    if (pos==num.size()) return 0;
    if (dp[pos][sum][flag]!=-1) return dp[pos][sum][flag];
    long long res=0;
    int limit=(flag)?9:nums[pos]-'0';
    for (int i=0;i<=limit;i++) res+=digit_dp(pos+1,sum+i,flag||(i<limit));
    return dp[pos][sum][flag]=res;
}

vector<int> slidingWinMax(const vector<int>& arr, int k){
    deque<int> dq;
    vector<int> res;
    for (int i=0;i<n;i++){
        if (i>=k){
            while(!dq.empty() && dq.front()<=i-k) dq.pop_front();
        }
        while(!dq.empty && arr[dq.back()]<=arr[i]) dq.pop_back();
        dq.push_back(i);
        if (i>=k-1) res.push_back([dq.front()]);
    }
    return res;
}

struct Trie{
    int nums;
    vector<vector<int>> nodes, vector<int> cnt;
    Trie(int maxnodes):nums(0),nodes(maxnodes,vector<int>(26,0)),cnt(maxnodes,0){
    }
    void insert(string s){
        int u=0;
        for (char c:s){
            if (!nodes[u][c-'a']) nodes[u][c-'a']=++nums;
            u=nodes[u][c-'a'];
        }
        cnt[u]++;
    }
};

// Bit Trie (0-1) (Max XOR queries)
struct BitTrie{
    int nums;   // 1-based indexing
    vector<vector<int>> nodes;
    BitTrie(int maxnum):nums(1),nodes(maxnum*32,vector<int>(2,0)){}
    void insert(int x){
        int u=1;
        for (int i=30;i>=0;i--){
            int bit=(x>>i)&1;
            if (!nodes[u][bit]) nodes[u][bit]=++nums;
            u=nodes[u][bit];
        }
    }
    void get_max_xor(int x){
        int u=1;
        int res=0;
        for (int i=30;i>=0;i--){
            int bit=(x>>i)&1;
            if (nodes[u][bit^1]){
                res|=(1<<i);
                u=nodes[u][bit^1];
            }
            else if (nodes[u][bit]) u=nodes[u][bit];
            else break;
        }
        return res;
    }
};

void solve(){
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}