#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
const int INF =1e9;
const ll LINF = 1e18;
const int MAX_N = 2e5+5;
const int MOD = 1e9+9;

ListNode* reverseList(ListNode* head){
    ListNode dummy(0);
    dummy.next=head;
    ListNode* prev=&dummy,cur=head;
    while(cur){
        ListNode* nex=cur->next;
        cur->next=prev;
        prev=cur;
        cur=nex;
    }
    return dummy.next;
}

ListNode* merge2List(ListNode* list1, ListNode* list2){
    ListNode dummy(0);
    ListNode* cur=&dummy;
    while(list1 && list2){
        if (list1->val<list2->val){
            cur->next=list1;
            list1=list1->next;
            cur=cur->next;
        }
        else{
            cur->next=list2;
            list2=list2->next;
            cur=cur->next;
        }
    }
    cur->next = list1?list1:list2;
    return dummy.next;
}
// 1-based indexing
ListNode* removeNthFromEnd(ListNode*head, int n){
    ListNode dummy(0);
    dummy.next=head;
    ListNode pre=&dummy,nex=&dummy;
    n++;
    while(n--) nex=nex->next;
    while(nex){
        pre=pre->next;
        nex=nex->next;
    }
    nex=pre->next->next;
    delete pre->next;
    pre->next=nex;
    return dummy.next;
}

bool hasCycle(ListNode* head){
    ListNode* slow=head, fast=head;
    while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
        if (slow==fast) return true;
    }
    return false;
}


// KMP
vector<int> prefixFunc(string s){
    int n=s.size();
    vector<int> pref(n,0);
    for (int i=1;i<n;i++){
        int pi=pref[i-1];
        while(pi>0 && s[pi]!=s[i]) pi=pref[pi-1];
        pref[i]=pi+(s[i]==s[pi]);
    }
    return pref;
}

vector<int> kmpFind(string s, string pat){
    if (pat.empty()) return vector<int>();
    s+="#"+pat;
    vector<int> pref=prefixFunc(s);
    vector<int> res;
    for (int i=pat.size()+1;i<s.size();i++){
        if (pref[i]==pat.size()) res.push_back(i-2*pat.size());
    }
    return res;
}

vector<int> zfunc(string s){
    int n=s.size();
    vector<int> z(n,0);
    int l=0,r=0;
    for (int i=1;i<n;i++){
        if (i<=r) z[i]=min(r-i,z[i-l]);
        if (i+z[i]<n && s[z[i]]==s[i+z[i]]) z[i]++;
        if (i+z[i]>r){
            l=i;
            r=i+z[i];
        }
    }
    return z;
}


class LRUCache{
    int cap, list<pair<int,int>> q, unordered_map<int,list<pair<int,int>>::iterator> mpi;
    LRUCache(int n):cap(n){}
    void put(int k, int v){
        if (mpi.find(k)!=mpi.end()){
            q.erase(mpi[k]);
            mpi.erase(k);
        }
        q.push_front({k,v});
        mpi[k]=q.begin();
        if (q.size()>cap){
            mpi.erase(q.back().first);
            q.pop_back();
        }
    }
    int get(int k){
        if (mpi.find(k)!=mpi.end()){
            auto it=mpi[k];
            int v=it->second;
            q.erase(it);
            q.push_front({k,v});
            mpi[k]=q.begin();
            return v;
        }
        else return -1;
    }
}

struct Trie{
    vector<vector<int>> tree, vector<int> cnt, int nums;
    Trie(int maxnodes):tree(maxnodes,vector<int>(26,0)),cnt(maxnodes,0),nums(0){}
    void add_string(string s){
        int u=0;
        for (char c:s){
            if (tree[u][c]==0){
                tree[u][c]=++nums;
            }
            u=tree[u][c];
        }
        cnt[u]++;
    }
}

struct BitTrie{
    
}
void solve(){
}

signed main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }

    return 0;
}