#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

const int MAXN =2e5+5;
const int INF =1e9;
const ll LINF =1e18;
const int MOD =1e9+9; // +7

#define setbit(x,i) (x|(1LL<<i))
#define getbit(x,i) ((x>>i)&1LL)
#define clearbit(x,i) (x&~(1LL<<i))
#define togglebit(x,i) (x^(1LL<<i))
#define lowbit(x) (x&(-x))
#define clearlowbit(x) ((x)-(x&(-x)))
#define is_pow2(x) ((x)&& ((((x)-1LL)&(x))==0))
#define is_allones(x) ((x)&& ((x+1LL)&(x))==0)

long long count1s_to_n(int n){
    long long res=0;
    for (int i=62;i>=0;i--){
        if (n&(1LL<<i)){
            res+=(i?(i*(1LL<<(i-1))):0)+(n-(1LL<<i)+1);
            n^=(1LL<<i);
        }   
    }
    return res;
}
long long qexp(long long a,long long b,long long m=-1){
    long long res=1;
    while(b>0){
        if (b%2) res=(m==-1)?res*a:(res*a)%m;
        a=(m==-1)?(a*a):(a*a)%m;
        b/=2;
    }
    return res;
}
long long gcd(long long a, long long b){
    return (b==0)?a:gcd(b,a%b);
}
long long ext_gcd(long long a, long long b, long long &x, long long &y){
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    long long x1,y1;
    long long g=ext_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return g;
}

long long inv_mod(long long a, long long m){
    long long x,y;
    long long g=ext_gcd(a,m,x,y);
    return (g==1)?(x%m+m)%m:-1;
}


// Monday
vector<long long> two_sum(vector<long long>& arr, long long target){
    unordered_map<long long,int> mpi;
    for (int i=0;i<arr.size();i++){
        long long u=arr[i];
        auto it=mpi.find(target-u);
        if (it==mpi.end()){
            mpi[u]=i;
        }
        else return {it->second,i};
    }
    // for (auto u:arr){
    //     if (u*2==target){
    //         if (mpi[u]>1) return {u,u};
    //     }
    //     else{
    //         if (mpi[target-u]>0) return {u,target-u};
    //     }
    // } 
    return {};
}

vector<vector<int>> three_sum(vector<long long>& arr){
    int n=arr.size();
    const int INF=1e9;
    sort(arr.begin(),arr.end());
    vector<vector<int>> res;
    for (int i=0;i<n;i++){
        int target=-arr[i];
        int l=i+1,r=n-1;
        if (i!=0 && arr[i]==arr[i-1]) continue;
        while(l<r){
            if (arr[l]+arr[r]==target){
                res.push_back({arr[i],arr[l],arr[r]});
                int x=arr[l],y=arr[r];
                while (l<r && x==arr[l]) l++;
                while(l<r && y==arr[r]) r--;
            }
            else if (arr[l]+arr[r]<target){
                l++;
            }
            else r--;
        }
    }
    return res;
}
int lower_bound_idx(const vector<int>& arr, int x){
    int l=0,n=arr.size(),r=n-1;
    int res=-1;
    while(l<=r){
        int m=l+(r-l)/2;
        if (arr[m]<x){
            res=m;
            l=m+1;
        }
        else r=m-1;
    }
    return res+1;
}
int upper_bound_idx(const vector<int>& arr, int x){
    int l=0,n=arr.size(),r=n-1;
    int res=-1;
    while(l<=r){
        int m=l+(r-l)/2;
        if (arr[m]<=x){
            res=m;
            l=m+1;
        }
        else r=m-1;
    }
    return res+1;
}

bool can_put(const vector<int>& arr, int k, int d){
    int last=arr[0],cnt=1;
    for (int i=1;i<arr.size();i++){
        if (arr[i]-last>=d){
            cnt++;
            last=arr[i];
        }
    }
    return cnt>=k;
}
int agg_cows(vector<int>& arr, int k){
    
    sort(arr.begin(),arr.end());
    int l=0,r=arr.back()-arr.front();
    int res=0;
    while(l<=r){
        int m=l+(r-l)/2;
        if (can_put(arr,k,m)){
            res=m;
            l=m+1;
        }
        else r=m-1;
    }
    return res;
}
// sorted array rotated/shifted by a pivot element 
int search_rotated(const vector<int>& arr, int k){
    int n=arr.size();
    if (n<1) return -1;
    int l=0,r=n-1;
    int ki=0;
    while(l<=r){
        int m=l+(r-l)/2;
        if (arr[m]>=arr[0]){
            ki=m;
            l=m+1;
        }
        else r=m-1;
    }
    if (k>arr[ki]) return -1;
    if (k>=arr[0]){
        l=0;
        r=ki;
    }
    else {
        l=ki+1;
        r=n-1;
    }
    int res=-1;
    while(l<=r){
        int m=l+(r-l)/2;
        if (arr[m]<=k){
            if (arr[m]==k) res=m;
            l=m+1;
        }
        else r=m-1;
    }
    return res;
}

// 01 Shortest Walk Covering Required Tree Nodes
// STATEMENT Find the minimum vertex visits in a walk covering all required nodes; start and end are unrestricted.
// CONSTRAINTS n >= 1; connected unweighted tree; 1 <= |R| <= n; code uses 0-indexed vertex IDs.
int findTravelCost(vector<pair<int,int>>& edges, vector<int>& reqVert){
    int n=edges.size()+1;
    vector<vector<int>> adj(n);
    vector<int> deg(n,0);
    for (int i=0;i<n-1;i++){
        deg[edges[i].first]++;
        deg[edges[i].second]++;
        adj[edges[i].first].push_back(edges[i].second);
        adj[edges[i].second].push_back(edges[i].first);
    }
    vector<int> alive(n,1),required(n,0);
    for (int u:reqVert) required[u]=1;
    queue<int> q;
    for (int i=0;i<n;i++) if (deg[i]<=1 && !required[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if (!alive[u] || required[u] || deg[u]>1) continue;
        alive[u]=0;
        for (int v:adj[u]){
            deg[v]--;
            if (alive[v] && !required[v] && deg[v]==1) q.push(v);
        }
    } 
    auto farthest = [&alive, &adj, n](int u) -> array<int,2>{
        vector<int> dep(n,-1);
        queue<int> q;
        q.push(u);
        dep[u]=0;
        array<int,2> res = {u,0};
        while(!q.empty()){
            int u=q.front();
            q.pop();
            if (dep[u]>res[1]) res={u,dep[u]};
            for (int v:adj[u]){
                if (alive[v] && dep[v]==-1){
                    dep[v]=dep[u]+1;
                    q.push(v);
                }
            }
        }
        return res;
    };
    int res=0;
    for (int i=0;i<n;i++){
        if (alive[i]){
            for (auto v:adj[i]){
                if (alive[v]) res++;
            }
        }
    }
    auto it=farthest(reqVert[0]);
    auto it2=farthest(it[0]);
    res-=it2[1]-1;
    return res;
}


int earliestDayToComplete(vector<int> nums, vector<int> days){
    int n=nums.size();
    int m=days.size();
    auto isValid = [&nums, &days, m, n](int d)-> bool{
        vector<int> last(m,-1);
        for (int i=0;i<d;i++){
            last[nums[i]]=i;
        }
        int fre=0;
        int cmp=0;
        for (int i=0;i<d;i++){
            if (last[nums[i]]==i){
                if (fre>=days[nums[i]]){
                    fre-=days[nums[i]];
                    cmp++;
                }
                else return false;
            }
            else fre++;
        }
        return cmp==m;
    };
    int l=0,r=nums.size();
    int res=-1;
    while(l<=r){
        int m=l+(r-l)/2;
        if (isValid(m)){
            res=m;
            r=m-1;
        }
        else l=m+1;
    }
    return res;
}

long long kthLargeSubArrayOR(const vector<int>& nums, int k){
    int n=nums.size();
    vector<array<int,2>> prev;
    map<int,int,greater<int>> mpi;
    // prev[0]={0,1};
    for (int i=0;i<n;i++){
        vector<array<int,2>> cur;
        cur.emplace_back(nums[i],1);
        for (auto [p,cnt]:prev) cur.emplace_back(p|nums[i],cnt);
        sort(cur.begin(),cur.end());
        vector<array<int,2>> imp;
        for (auto [p,cnt]:cur){
            if (imp.size()>=1 && imp.back()[0]==p) imp[imp.size()-1][1]+=cnt;
            else imp.emplace_back(p,cnt);
        }
        for (auto [p,cnt]:imp) mpi[p]+=cnt;
        prev=imp;
    }
    int tmp=0,i=0;
    for (auto it:mpi){
        if (tmp+it.second>=k) return it.first; 
        tmp+=it.second;
    }
    return -1;
}

void solve(){

}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;

}