# Blind Typing Placement Forge - 60-Minute Weekly System

## Rules

**Typing-file convention:** Generic algorithm/template cards intentionally have no problem IDs. Problem-specific cards carry only a short problem description and, when useful, a direct problem link. Do not treat these links/descriptions as reading material.
1. Blank editor; no autocomplete/LSP.
2. Type the Daily Core every day, then only use the cards under the current day.
3. Week A / Week B alternate; the Hard transfer replaces the normal 15-minute transfer block.
4. Compile after each card or pair of cards; fix errors from memory, not by copying.

## Every day - 8 minutes: Daily Core
### 1. Math: qexp / gcd / ext_gcd / inv_mod
```cpp
long long qexp(long long a, long long b, long long m = MOD) {
    long long res = 1; a %= m;
    while (b) { if (b & 1) res = (long long)((__int128_t)res * a % m); a = (long long)((__int128_t)a * a % m); b >>= 1; }
    return res;
}
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (!b) { x = 1; y = 0; return a; }
    long long x1, y1, d = ext_gcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b); return d;
}
long long inv_mod(long long a, long long m) { 
    long long x, y; long long g = ext_gcd(a, m, x, y); 
    if (g != 1) return -1;
    return (m + x % m) % m; 
}
```

### 2. Bits: core bit operations
```cpp
#define getbit(x,i) (((x)>>(i))&1LL)            // Extract bit at index i exactly as 0 or 1
#define setbit(x,i) ((x)|(1LL<<(i)))            // Set at index i to 1
#define clearbit(x,i) ((x)&(~(1LL<<(i))))       // Set at index i to 0
#define togglebit(x,i) ((x)^(1LL<<(i)))         // Toggle between 0 and 1
#define lowbit(x) ((x)&(-(x)))                  // Isolate lowest set bit
#define strip_lowbit(x) ((x)-((x)&(-(x))))      // Clear lowest set bit
#define is_pow2(x) ((x)&&(((x)&((x)-1LL))==0))  // Check if exact power of 2
#define is_allones(x) ((x)&&(((x)&((x)+1LL))==0)) // Check if binary representation is all 1s
#define all_ones(n) ((1LL<<(n))-1LL)            // Generate n-bit mask of all 1s

// Built-ins: __builtin_popcountll(x), __builtin_ctzll(x) [trailing 0s], __builtin_clzll(x) [leading 0s]

// Count 1s in binary representations of all numbers from 1 to N in O(log N)
long long count1s_ton(long long n) { 
    long long c = 0; 
    for(int i=61; i>=0; i--) {
        if(n & (1LL<<i)) { 
            c += (i ? (1LL<<(i-1))*i : 0) + (n-(1LL<<i)+1); 
            n -= (1LL<<i); 
        } 
    } 
    return c; 
}
```

# Monday - Arrays / Binary Search / Prefix / Compression
**0-8:** Daily Core. **8-38:** day cards. **38-53:** Hard transfer. **53-60:** retype misses + edge case.
**Week A:** Two Sum -> 3Sum -> lower/upper bounds -> binary-search-on-answer.
**Week B:** Kadane -> rotated search -> merge intervals -> prefix/difference + compression.
### 1. Two Sum
**Problem:** Find two array elements whose values add to the target.
```cpp
// Hash complements; for duplicates, the stored index may be reused only after checking the current element.
vector<int> two_sum(const vector<int>& a, int target) {
    unordered_map<int,int> pos;
    for (int i = 0; i < (int)a.size(); ++i) {
        auto it = pos.find(target - a[i]);
        if (it != pos.end()) return {it->second, i};
        pos[a[i]] = i;
    }
    return {};
}
```

### 2. 3Sum
**Problem:** Find all unique triples whose values sum to zero.
```cpp
// Sorting removes duplicate triples cleanly and reduces the inner search to O(n).
vector<vector<int>> three_sum(vector<int> a) {
    sort(a.begin(), a.end());
    vector<vector<int>> ans;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i && a[i] == a[i-1]) continue;
        int l = i + 1, r = (int)a.size() - 1;
        while (l < r) {
            long long s = 1LL * a[i] + a[l] + a[r];
            if (s < 0) ++l;
            else if (s > 0) --r;
            else {
                ans.push_back({a[i], a[l], a[r]});
                int x = a[l], y = a[r];
                while (l < r && a[l] == x) ++l;
                while (l < r && a[r] == y) --r;
            }
        }
    }
    return ans;
}
```

### 3. First/last occurrence and lower/upper bound
```cpp
// These helpers return iterator positions; they work on sorted arrays and handle duplicates.
int lower_bound_idx(const vector<int>& a, int x) {
    int l = 0, r = a.size();
    while (l < r) { int m = l + (r-l)/2; if (a[m] < x) l = m + 1; else r = m; }
    return l;
}
int upper_bound_idx(const vector<int>& a, int x) {
    int l = 0, r = a.size();
    while (l < r) { int m = l + (r-l)/2; if (a[m] <= x) l = m + 1; else r = m; }
    return l;
}
```

### 4. Aggressive cows / maximize minimum distance
**Problem:** Place cows in stalls so the minimum pairwise distance is maximized.
```cpp
// Greedy placement is optimal for a fixed distance; binary search finds the largest feasible distance.
bool can_place(const vector<int>& x, int k, int d) {
    int cnt = 1, last = x[0];
    for (int i = 1; i < (int)x.size(); ++i) if (x[i] - last >= d) last = x[i], ++cnt;
    return cnt >= k;
}
int aggressive_cows(vector<int> x, int k) {
    sort(x.begin(), x.end());
    int l = 0, r = x.back() - x.front(), ans = 0;
    while (l <= r) {
        int m = l + (r-l)/2;
        if (can_place(x, k, m)) ans = m, l = m + 1;
        else r = m - 1;
    }
    return ans;
}
```

### 5. Maximum subarray / Kadane
**Problem:** Find the maximum sum of a contiguous subarray.
```cpp
// Start with a[0], not zero, so an array of all negatives returns its true maximum.
long long kadane(const vector<long long>& a) {
    if (a.empty()) return 0;
    long long cur = a[0], best = a[0];
    for (int i = 1; i < (int)a.size(); ++i) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}
```

### 6. Search in rotated sorted array
**Problem:** Search for a target in a sorted array rotated at an unknown pivot.
```cpp
// Distinguish the sorted half and test whether the target lies inside it.
int search_rotated(const vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == target) return m;
        if (a[l] <= a[m]) {
            if (a[l] <= target && target < a[m]) r = m - 1;
            else l = m + 1;
        } else {
            if (a[m] < target && target <= a[r]) l = m + 1;
            else r = m - 1;
        }
    }
    return -1;
}
```

### 7. Merge intervals
**Problem:** Merge all overlapping intervals into disjoint ranges.
```cpp
// Sorting by start guarantees every overlapping interval appears next to the current merged interval.
vector<vector<int>> merge_intervals(vector<vector<int>> a) {
    if (a.empty()) return {};
    sort(a.begin(), a.end());
    vector<vector<int>> ans{a[0]};
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i][0] <= ans.back()[1]) ans.back()[1] = max(ans.back()[1], a[i][1]);
        else ans.push_back(a[i]);
    }
    return ans;
}
```

### 8. Prefix Sum / Prefix XOR / Difference Array / 2D Prefix
```cpp
// Prefix arrays turn repeated range arithmetic into O(1) queries; difference arrays turn range updates into O(1) marks.
vector<long long> prefix(const vector<long long>& a) {
    int n = a.size(); vector<long long> p(n + 1);
    for (int i = 0; i < n; ++i) p[i + 1] = p[i] + a[i];
    return p;
}
vector<long long> prefix_xor(const vector<long long>& a) {
    int n = a.size(); vector<long long> p(n + 1);
    for (int i = 0; i < n; ++i) p[i + 1] = p[i] ^ a[i];
    return p;
}
vector<long long> build_diff(int n, const vector<array<int,3>>& ops) {
    vector<long long> d(n + 1);
    for (auto [l, r, x] : ops) d[l] += x, d[r + 1] -= x;
    for (int i = 1; i < n; ++i) d[i] += d[i - 1];
    d.resize(n); return d;
}
long long rect_sum(const vector<vector<long long>>& p, int r1, int c1, int r2, int c2) {
    return p[r2 + 1][c2 + 1] - p[r1][c2 + 1] - p[r2 + 1][c1] + p[r1][c1];
}
```

### 9. Coordinate Compression
```cpp
// Compress only when ordering/rank matters; preserve the original values separately if they are needed later.
vector<long long> xs = a;
sort(xs.begin(), xs.end());
xs.erase(unique(xs.begin(), xs.end()), xs.end());
int id = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
```

### 10. Hard transfer - 3165 - Maximum Sum of Subsequence With Non-adjacent Elements
**Problem:** Given an array with point updates, return the maximum sum of a subsequence with no adjacent selections.
**Link:** https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/description/?envType=problem-list-v2&envId=0xtaf9f6
```cpp
// Node state encodes whether the segment's left/right endpoints are selected; merge rejects adjacent selections across the boundary.
struct NonAdjSeg {
    struct Node { long long s[2][2]{}; };
    int n; vector<Node> st;
    NonAdjSeg(const vector<int>& a) : n(a.size()), st(4 * n) { build(1, 0, n - 1, a); }
    Node merge(const Node& A, const Node& B) {
        Node C;
        for (int l = 0; l < 2; ++l) for (int r = 0; r < 2; ++r) C.s[l][r] = LLONG_MIN / 4;
        for (int l = 0; l < 2; ++l) for (int x = 0; x < 2; ++x)
            for (int y = 0; y < 2; ++y) for (int r = 0; r < 2; ++r)
                if (!(x && y)) C.s[l][r] = max(C.s[l][r], A.s[l][x] + B.s[y][r]);
        return C;
    }
    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) { st[v].s[0][0] = st[v].s[0][1] = st[v].s[1][0] = 0; st[v].s[1][1] = max(0, a[l]); return; }
        int m = (l + r) / 2; build(v * 2, l, m, a); build(v * 2 + 1, m + 1, r, a); st[v] = merge(st[v * 2], st[v * 2 + 1]);
    }
    void update(int v, int l, int r, int p, int x) {
        if (l == r) { st[v] = Node{}; st[v].s[1][1] = max(0, x); return; }
        int m = (l + r) / 2; if (p <= m) update(v * 2, l, m, p, x); else update(v * 2 + 1, m + 1, r, p, x); st[v] = merge(st[v * 2], st[v * 2 + 1]);
    }
    void update(int p, int x) { update(1, 0, n - 1, p, x); }
    long long answer() const { return st[1].s[1][1]; }
};
```

### 11. Hard transfer - 3139 - Minimum Cost to Equalize Array
**Problem:** Find the minimum cost to make all array values equal using single-element and paired operations.
**Link:** https://leetcode.com/problems/minimum-cost-to-equalize-array/description/?envType=problem-list-v2&envId=0xtaf9f6
**Typing note:** This is a transfer/re-solve card; use the problem as a timed benchmark rather than memorizing an implementation here.
# Tuesday - Sliding Window / Stack / Heap
**0-8:** Daily Core. **8-38:** day cards. **38-53:** Hard transfer. **53-60:** retype misses + edge case.
**Week A:** longest unique -> minimum window -> sliding-window maximum -> next greater.
**Week B:** Top-K -> min stack -> largest rectangle -> two heaps.
### 1. Longest substring without repeating characters
**Problem:** Find the longest substring containing no repeated character.
```cpp
// Move the left boundary past the previous occurrence so every active character stays unique.
int longest_unique(const string& s) {
    vector<int> last(256,-1); int l=0,ans=0;
    for(int r=0;r<(int)s.size();++r){
        l=max(l,last[(unsigned char)s[r]]+1); last[(unsigned char)s[r]]=r;
        ans=max(ans,r-l+1);
    }
    return ans;
}
```

### 2. Minimum window substring
**Problem:** Find the shortest substring containing all characters of a target multiset.
```cpp
// Expand until all required counts are satisfied, then shrink greedily from the left.
string min_window(const string& s,const string& t){
    vector<int> need(256), have(256); for(char c:t) ++need[(unsigned char)c];
    int missing=t.size(), l=0,best=INT_MAX,beg=0;
    for(int r=0;r<(int)s.size();++r){
        unsigned char c=s[r]; if(need[c]&&have[c]++<need[c]) --missing;
        while(!missing){
            if(r-l+1<best) best=r-l+1,beg=l;
            unsigned char d=s[l++]; if(need[d]&&have[d]--<=need[d]) ++missing;
        }
    }
    return best==INT_MAX?string():s.substr(beg,best);
}
```

### 3. Sliding window maximum
**Problem:** Return the maximum value in every fixed-size sliding window.
```cpp
// Expire left indices first, then remove smaller values from the back so the front is always the maximum.
vector<int> sliding_max(const vector<int>& a, int k) {
    deque<int> dq; vector<int> ans;
    for (int i=0;i<(int)a.size();++i) {
        while (!dq.empty() && dq.front() <= i-k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k-1) ans.push_back(a[dq.front()]);
    }
    return ans;
}
```

### 4. Next greater element
**Problem:** For each element, find the first greater value to its right.
```cpp
// Pop while the current value is larger; every popped index gets its first greater element.
vector<int> next_greater(const vector<int>& a) {
    vector<int> ans(a.size(),-1); vector<int> st;
    for(int i=0;i<(int)a.size();++i){
        while(!st.empty() && a[st.back()]<a[i]) ans[st.back()]=a[i],st.pop_back();
        st.push_back(i);
    }
    return ans;
}
```

### 5. Top K frequent elements
**Problem:** Return the k values with the highest frequencies.
```cpp
// Keep only k candidates in the heap; the smallest frequency is the one discarded first.
vector<int> top_k_frequent(const vector<int>& a, int k) {
    unordered_map<int,int> f;
    for (int x:a) ++f[x];
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for (auto [x,c]:f) {
        pq.push({c,x});
        if ((int)pq.size()>k) pq.pop();
    }
    vector<int> ans;
    while(!pq.empty()) ans.push_back(pq.top().second), pq.pop();
    return ans;
}
```

### 6. Min stack
```cpp
// Empty-stack behavior is left to the caller; use LLONG_MAX as an identity only when appropriate.
struct MinStack {
    vector<pair<int,int>> st;
    void push(int x){ int mn=st.empty()?x:min(x,st.back().second); st.push_back({x,mn}); }
    void pop(){ st.pop_back(); }
    int top() const { return st.back().first; }
    int getMin() const { return st.back().second; }
};
```

### 7. Largest Rectangle in Histogram
**Problem:** Find the largest rectangle that can be formed under histogram bars.
```cpp
// Maintain increasing heights; when a smaller bar arrives, every popped bar has now found its right boundary.
long long largestRectangleArea(const vector<int>& h) {
    int n = h.size(); long long ans = 0; vector<int> st;
    for (int i = 0; i <= n; ++i) {
        int cur = (i == n ? 0 : h[i]);
        while (!st.empty() && h[st.back()] > cur) {
            int ht = h[st.back()]; st.pop_back();
            int left = st.empty() ? -1 : st.back();
            ans = max(ans, 1LL * ht * (i - left - 1));
        }
        st.push_back(i);
    }
    return ans;
}
```

### 8. Two Heaps / Running Median
**Problem:** Maintain the median while numbers arrive online.
```cpp
// Keep left as a max-heap and right as a min-heap; rebalance so their sizes differ by at most one.
struct MedianDS {
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;
    void add(int x) {
        if (lo.empty() || x <= lo.top()) lo.push(x); else hi.push(x);
        if (lo.size() > hi.size() + 1) hi.push(lo.top()), lo.pop();
        if (hi.size() > lo.size()) lo.push(hi.top()), hi.pop();
    }
    double median() const { return lo.size() == hi.size() ? (lo.top() + hi.top()) / 2.0 : lo.top(); }
};
```

### 9. Hard transfer - 3357 - Minimize the Maximum Adjacent Element Difference
**Problem:** Replace unknown values so the maximum adjacent difference is as small as possible.
**Link:** https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/description/?envType=problem-list-v2&envId=0xtaf9f6
```cpp
// Binary-search the answer; for a candidate m, only the values adjacent to -1-runs matter, and the two replacement values are mn+m and mx-m.
class Solution {
    bool check(const vector<int>& a, int m, int x, int y) {
        int gap = 0, prev = 0;
        for (int v : a) {
            if (v == -1) { ++gap; continue; }
            if (prev > 0 && gap) {
                if (gap == 1) {
                    if (min(max(abs(prev-x), abs(v-x)), max(abs(prev-y), abs(v-y))) > m) return false;
                } else {
                    int a1 = max(abs(prev-x), abs(v-x));
                    int a2 = max(abs(prev-y), abs(v-y));
                    int a3 = max({abs(prev-x), abs(x-y), abs(v-y)});
                    int a4 = max({abs(prev-y), abs(x-y), abs(v-x)});
                    if (min({a1,a2,a3,a4}) > m) return false;
                }
            }
            prev = v; gap = 0;
        }
        auto first = [&](int st, int step) { int i = st; while (0 <= i && i < (int)a.size() && a[i] == -1) i += step; return (0 <= i && i < (int)a.size()) ? a[i] : -1; };
        if (a.front() == -1) { int v = first(0, 1); if (v != -1 && min(abs(v-x), abs(v-y)) > m) return false; }
        if (a.back() == -1) { int v = first((int)a.size()-1, -1); if (v != -1 && min(abs(v-x), abs(v-y)) > m) return false; }
        return true;
    }
public:
    int minDifference(vector<int>& nums) {
        int base = 0, mn = 1e9, mx = 0;
        for (int i = 1; i < (int)nums.size(); ++i) {
            if ((nums[i-1] == -1) != (nums[i] == -1)) { int v = max(nums[i-1], nums[i]); mn = min(mn, v); mx = max(mx, v); }
            else if (nums[i] != -1) base = max(base, abs(nums[i] - nums[i-1]));
        }
        int l = base, r = (mx - mn + 1) / 2;
        while (l < r) { int m = (l + r) / 2; if (check(nums, m, mn + m, mx - m)) r = m; else l = m + 1; }
        return l;
    }
};
```

### 10. Hard transfer - 3266 - Final Array State II
**Problem:** Repeatedly multiply the current minimum element, then return the final array after a huge number of operations.
**Link:** https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/description/?envType=problem-list-v2&envId=0xtaf9f6
**Typing note:** This is a transfer/re-solve card; use the problem as a timed benchmark rather than memorizing an implementation here.
# Wednesday - Linked List / Strings / Cache
**0-8:** Daily Core. **8-38:** day cards. **38-53:** Hard transfer. **53-60:** retype misses + edge case.
**Week A:** linked-list core -> KMP -> Z -> LRU.
**Week B:** linked-list core -> Trie -> group anagrams -> KMP/Z refresh.
### 1. Linked List Core
**Problem:** Core pointer operations covering reversal and merging of linked lists.
```cpp
// Dummy nodes remove head special-cases; slow/fast gives the middle and cycle patterns with O(1) extra space.
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *cur = head;
    while (cur) { ListNode* nxt = cur->next; cur->next = prev; prev = cur; cur = nxt; }
    return prev;
}
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0), *cur = &dummy;
    while (a && b) { if (a->val <= b->val) cur->next = a, a = a->next; else cur->next = b, b = b->next; cur = cur->next; }
    cur->next = a ? a : b; return dummy.next;
}
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head), *slow = &dummy, *fast = &dummy;
    while (n--) fast = fast->next;
    while (fast->next) slow = slow->next, fast = fast->next;
    ListNode* del = slow->next; slow->next = del->next; delete del; return dummy.next;
}
bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; if (slow == fast) return true; }
    return false;
}
```

### 2. KMP prefix function / pattern matching
```cpp
// pi[i] is the longest proper prefix of s[0..i] that is also a suffix; pi drives mismatch jumps.
vector<int> prefix_function(const string& s){
    vector<int> pi(s.size());
    for(int i=1;i<(int)s.size();++i){
        int j=pi[i-1];
        while(j&&s[i]!=s[j]) j=pi[j-1];
        if(s[i]==s[j]) ++j;
        pi[i]=j;
    }
    return pi;
}
vector<int> kmp_find(const string& text,const string& pat){
    if(pat.empty()) return {};
    string s=pat+"#"+text; auto pi=prefix_function(s); vector<int> ans;
    for(int i=(int)pat.size()+1;i<(int)s.size();++i) if(pi[i]==(int)pat.size()) ans.push_back(i-2*pat.size());
    return ans;
}
```

### 3. Z algorithm
```cpp
// Maintain the rightmost Z-box and reuse mirrored information while inside the box.
vector<int> z_function(const string& s){
    int n=s.size(); vector<int> z(n);
    for(int i=1,l=0,r=0;i<n;++i){
        if(i<=r) z[i]=min(r-i+1,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]]) ++z[i];
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    return z;
}
```

### 4. LRU Cache
**Problem:** Support get/put in O(1) while evicting the least-recently-used entry.
```cpp
// Front is most recent and back is least recent; map stores node iterators for direct removal.
class LRUCache {
    int cap; list<pair<int,int>> q; unordered_map<int,list<pair<int,int>>::iterator> mp;
    void touch(list<pair<int,int>>::iterator it) { auto p=*it; q.erase(it); q.push_front(p); mp[p.first]=q.begin(); }
public:
    LRUCache(int c):cap(c){}
    int get(int k) {
        auto it=mp.find(k); if(it==mp.end()) return -1;
        int v=it->second->second; touch(it->second); return v;
    }
    void put(int k,int v) {
        if(mp.count(k)){ q.erase(mp[k]); mp.erase(k); }
        q.push_front({k,v}); mp[k]=q.begin();
        if((int)q.size()>cap){ mp.erase(q.back().first); q.pop_back(); }
    }
};
```

### 5. Trie
```cpp
// Standard String Trie
struct Trie {
    vector<vector<int>> trie; vector<int> cnt; int num = 0;
    Trie(int max_nodes) : trie(max_nodes, vector<int>(26, 0)), cnt(max_nodes, 0) {}
    void insert(string s) { 
        int u = 0; 
        for (char c : s) { if (!trie[u][c - 'a']) trie[u][c - 'a'] = ++num; u = trie[u][c - 'a']; } 
        cnt[u]++; 
    }
};

// Bitwise 0-1 Trie (Maximum XOR queries)
struct BitTrie {
    vector<vector<int>> trie; int num;
    BitTrie(int max_el) : trie(max_el * 32, vector<int>(2, 0)), num(1) {}
    void insert(int x) {
        int u = 1;
        for (int i = 30; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (!trie[u][bit]) trie[u][bit] = ++num;
            u = trie[u][bit];
        }
    }
    int get_max_xor(int x) {
        int u = 1, ans = 0;
        for (int i = 30; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (trie[u][bit ^ 1]) { ans |= (1 << i); u = trie[u][bit ^ 1]; } 
            else if (trie[u][bit]) { u = trie[u][bit]; } 
            else break;
        } return ans;
    }
};
```

### 6. Group anagrams
**Problem:** Group strings that contain the same multiset of characters.
```cpp
// Sorting the letters gives identical keys for anagrams; replace with frequency keys when n is large.
vector<vector<string>> group_anagrams(const vector<string>& s){
    unordered_map<string,vector<string>> mp;
    for(auto x:s){ string k=x; sort(k.begin(),k.end()); mp[k].push_back(x); }
    vector<vector<string>> ans; for(auto &p:mp) ans.push_back(move(p.second)); return ans;
}
```

### 7. Hard transfer - 420 - Strong Password Checker
**Problem:** Find the minimum edits needed to make a password satisfy length, character-class, and repetition rules.
**Link:** https://leetcode.com/problems/strong-password-checker/description/?envType=problem-list-v2&envId=0xtaf9f6
```cpp
class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.size(), missing = 3;
        bool lo = 0, up = 0, dig = 0;
        for (char c : password) lo |= islower(c), up |= isupper(c), dig |= isdigit(c);
        missing -= lo + up + dig;
        int replaces = 0, one = 0, two = 0;
        for (int i = 2; i < n;) {
            if (password[i] == password[i-1] && password[i] == password[i-2]) {
                int len = 2;
                while (i < n && password[i] == password[i-1]) ++len, ++i;
                replaces += len / 3;
                if (len % 3 == 0) ++one;
                if (len % 3 == 1) ++two;
            } else ++i;
        }
        if (n < 6) return max(6 - n, missing);
        if (n <= 20) return max(replaces, missing);
        int del = n - 20;
        replaces -= min(one, del);
        replaces -= min(max(del - one, 0), 2 * two) / 2;
        replaces -= max(del - one - 2 * two, 0) / 3;
        return del + max(replaces, missing);
    }
};
```

### 8. Hard transfer - 3303 - First Almost Equal Substring
**Problem:** Find the first substring that differs from a pattern in at most one position.
**Link:** https://leetcode.com/problems/find-the-occurrence-of-first-almost-equal-substring/description/?envType=problem-list-v2&envId=0xtaf9f6
**Typing note:** This is a transfer/re-solve card; use the problem as a timed benchmark rather than memorizing an implementation here.
# Thursday - Graphs / Trees
**0-8:** Daily Core. **8-38:** day cards. **38-53:** Hard transfer. **53-60:** retype misses + edge case.
**Week A:** BFS/DFS -> grid BFS/DFS -> Dijkstra -> Kahn.
**Week B:** DSU -> LCA -> Kruskal -> tree diameter/BST.
### 1. BFS / DFS graph traversal
```cpp
// BFS gives minimum edge count in an unweighted graph; DFS is the usual component traversal.
vector<int> bfs_dist(int s,const vector<vector<int>>& g){
    vector<int> d(g.size(),-1);queue<int>q;q.push(s);d[s]=0;
    while(!q.empty()){int u=q.front();q.pop();for(int v:g[u])if(d[v]<0)d[v]=d[u]+1,q.push(v);}
    return d;
}
```

### 2. Grid DFS/BFS Scaffold
```cpp
// Four-direction traversal is the reusable core for islands, flood fill, rotten oranges, shortest grids, and increasing-path variants.
vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
void grid_dfs(int r, int c, const vector<vector<int>>& g, vector<vector<char>>& vis) {
    int m = g.size(), n = g[0].size(); vis[r][c] = 1;
    for (auto [dr, dc] : dirs) { int nr = r + dr, nc = c + dc; if (0 <= nr && nr < m && 0 <= nc && nc < n && !vis[nr][nc]) grid_dfs(nr, nc, g, vis); }
}
```

### 3. Dijkstra shortest path
```cpp
// The stale-pair check is mandatory with a standard priority_queue because decrease-key is not implemented.
vector<long long> dijkstra(int s,const vector<vector<pair<int,int>>>& g){
    int n=g.size();vector<long long>d(n,4e18);priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>>pq;
    d[s]=0;pq.push({0,s});
    while(!pq.empty()){auto [du,u]=pq.top();pq.pop();if(du!=d[u])continue;for(auto [v,w]:g[u])if(d[v]>du+w)d[v]=du+w,pq.push({d[v],v});}
    return d;
}
```

### 4. Topological sort (Kahn)
```cpp
// A DAG has exactly n vertices removed; fewer means a cycle prevented full ordering.
vector<int> topo_sort(const vector<vector<int>>& g){
    int n=g.size();vector<int>in(n);for(int u=0;u<n;++u)for(int v:g[u])++in[v];
    queue<int>q;for(int i=0;i<n;++i)if(!in[i])q.push(i);vector<int>ans;
    while(!q.empty()){int u=q.front();q.pop();ans.push_back(u);for(int v:g[u])if(!--in[v])q.push(v);}
    if((int)ans.size()!=n)return {};return ans;
}
```

### 5. Disjoint Set Union
```cpp
struct DSU {
    vector<int> p, sz; int comps;
    DSU(int n) : comps(n), p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int u) { return u == p[u] ? u : p[u] = find(p[u]); }
    bool merge(int u, int v) {
        u = find(u), v = find(v); if (u == v) return false;
        if (sz[u] > sz[v]) swap(u, v);
        p[u] = v; sz[v] += sz[u]; comps--; return true;
    }
};
```

### 6. LCA via binary lifting
```cpp
// Here the vertices are stored in 1-based indexing (so `0` can be used as parent for root)
struct LCA {
    int n, l; vector<vector<int>> up, adj; vector<int> dep;
    LCA(int n) : n(n), l(ceil(log2(n))), up(n + 1, vector<int>(l + 1)), dep(n + 1), adj(n + 1) {}
    void dfs(int u, int p = 0, int d = 0) {
        up[u][0] = p; dep[u] = d; 
        for (int i = 1; i <= l; i++) up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u]) if (v != p) dfs(v, u, d + 1);
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = l; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v]) u = up[u][i];
        if (u == v) return u;
        for (int i = l; i >= 0; i--) if (up[u][i] != up[v][i]) u = up[u][i], v = up[v][i];
        return up[u][0];
    }
};
```

### 7. Kruskal MST
```cpp
// The first n-1 edges that connect different components form the MST when the graph is connected.
struct Edge{int u,v;long long w;};
long long kruskal(int n,vector<Edge> e){
    sort(e.begin(),e.end(),[](auto&a,auto&b){return a.w<b.w;});DSU d(n);long long ans=0;int used=0;
    for(auto x:e)if(d.unite(x.u,x.v)){ans+=x.w;if(++used==n-1)break;}
    return used==n-1?ans:LLONG_MAX;
}
```

### 8. Tree diameter
**Problem:** Find the longest path between any two nodes of a tree.
```cpp
// Diameter endpoints are farthest from one another in a tree; weighted variants replace BFS distance with DFS/Dijkstra.
pair<int,int> farthest(int s,const vector<vector<int>>&g){
    queue<int>q;q.push(s);vector<int>d(g.size(),-1);d[s]=0;int best=s;
    while(!q.empty()){int u=q.front();q.pop();for(int v:g[u])if(d[v]<0)d[v]=d[u]+1,q.push(v),best=d[v]>d[best]?v:best;}
    return {best,d[best]};
}
int tree_diameter(const vector<vector<int>>&g){auto a=farthest(0,g).first;return farthest(a,g).second;}
```

### 9. BST search/insert/delete
**Problem:** Search, insert, and delete values while preserving BST ordering.
```cpp
// Replace a deleted node with its inorder successor when both children exist.
TreeNode* bst_insert(TreeNode* r,int x){if(!r)return new TreeNode(x);if(x<r->val)r->left=bst_insert(r->left,x);else if(x>r->val)r->right=bst_insert(r->right,x);return r;}
TreeNode* bst_search(TreeNode*r,int x){while(r&&r->val!=x)r=x<r->val?r->left:r->right;return r;}
TreeNode* bst_delete(TreeNode*r,int x){
    if(!r)return r;if(x<r->val)r->left=bst_delete(r->left,x);else if(x>r->val)r->right=bst_delete(r->right,x);else{
        if(!r->left){auto q=r->right;delete r;return q;}if(!r->right){auto q=r->left;delete r;return q;}
        auto q=r->right;while(q->left)q=q->left;r->val=q->val;r->right=bst_delete(r->right,q->val);
    }return r;
}
```

### 10. Hard transfer - 2612 - Minimum Reverse Operations
**Problem:** From one starting index, find the minimum reversals needed to reach every position while respecting banned positions.
**Link:** https://leetcode.com/problems/minimum-reverse-operations/description/?envType=problem-list-v2&envId=0xtaf9f6
```cpp
// Reachable targets from i form one parity interval; erase each discovered index immediately so total work stays near O(n log n).
class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> ans(n, -1), ban(n, 0); set<int> unseen[2];
        for (int x : banned) ban[x] = 1;
        for (int i = 0; i < n; ++i) if (!ban[i] && i != p) unseen[i & 1].insert(i);
        queue<int> q; q.push(p); ans[p] = 0;
        while (!q.empty()) {
            int i = q.front(); q.pop();
            int lo = max(i - k + 1, k - i - 1);
            int hi = min(i + k - 1, 2 * n - k - i - 1);
            auto& s = unseen[lo & 1];
            auto it = s.lower_bound(lo);
            while (it != s.end() && *it <= hi) {
                int j = *it; it = s.erase(it); ans[j] = ans[i] + 1; q.push(j);
            }
        }
        return ans;
    }
};
```

### 11. Hard transfer - 3609 - Minimum Moves to Reach Target in Grid
**Problem:** Find the minimum moves to reach a target grid point under the problem's coordinate transformation rule.
**Link:** https://leetcode.com/problems/minimum-moves-to-reach-target-in-grid/description/?envType=problem-list-v2&envId=0xtaf9f6
**Typing note:** This is a transfer/re-solve card; use the problem as a timed benchmark rather than memorizing an implementation here.
# Friday - DP / Backtracking
**0-8:** Daily Core. **8-38:** day cards. **38-53:** Hard transfer. **53-60:** retype misses + edge case.
**Week A:** 0/1 knapsack -> subset sum -> LIS -> House Robber.
**Week B:** LCS -> edit distance -> Word Break -> Decode Ways/grid DP.
### 1. 0/1 Knapsack
**Problem:** Choose each item at most once to maximize value under a capacity limit.
```cpp
// Reverse capacity iteration prevents using the same item multiple times in one transition.
int knapsack01(const vector<int>& w,const vector<int>& val,int W){
    vector<int>dp(W+1);for(int i=0;i<(int)w.size();++i)for(int c=W;c>=w[i];--c)dp[c]=max(dp[c],dp[c-w[i]]+val[i]);return dp[W];
}
```

### 2. Subset sum / partition
**Problem:** Determine whether array elements can form a required sum or equal partition.
```cpp
// For 0/1 subset choice, update sums downward so one item is not counted twice.
bool subset_sum(const vector<int>& a,int S){
    vector<char>dp(S+1);dp[0]=1;for(int x:a)for(int s=S;s>=x;--s)dp[s]|=dp[s-x];return dp[S];
}
```

### 3. Longest Increasing Subsequence
**Problem:** Find the longest strictly increasing subsequence.
```cpp
// tails[len-1] is the smallest possible tail value of a subsequence of length len.
int lis(const vector<int>& a){
    vector<int>t;for(int x:a){auto it=lower_bound(t.begin(),t.end(),x);if(it==t.end())t.push_back(x);else *it=x;}return t.size();
}
```

### 4. House Robber
**Problem:** Maximize value when adjacent houses cannot both be chosen.
```cpp
// prev2 and prev track the best answer through the previous two positions.
long long house_robber(const vector<long long>&a){
    long long prev2=0,prev1=0;for(long long x:a){long long cur=max(prev1,prev2+x);prev2=prev1;prev1=cur;}return prev1;
}
```

### 5. Longest Common Subsequence
**Problem:** Find the longest subsequence shared by two strings.
```cpp
// dp[j] is the best LCS length for the processed prefix of the first string and the first j characters of the second.
int lcs(const string&a,const string&b){
    vector<int>dp(b.size()+1);
    for(char x:a){int diag=0;for(int j=1;j<=(int)b.size();++j){int old=dp[j];if(x==b[j-1])dp[j]=diag+1;else dp[j]=max(dp[j],dp[j-1]);diag=old;}}
    return dp.back();
}
```

### 6. Edit distance
**Problem:** Find the minimum insert/delete/replace operations to convert one string to another.
```cpp
// prev/cur rows are enough because each transition uses only left, up, and diagonal cells.
int edit_distance(const string&a,const string&b){
    vector<int>dp(b.size()+1);iota(dp.begin(),dp.end(),0);
    for(int i=1;i<=(int)a.size();++i){int diag=dp[0];dp[0]=i;for(int j=1;j<=(int)b.size();++j){int up=dp[j];dp[j]=a[i-1]==b[j-1]?diag+1:1+min({diag,dp[j-1],dp[j]});diag=up;}}
    return dp.back();
}
```

### 7. Word Break
**Problem:** Determine whether a string can be segmented into dictionary words.
```cpp
// dp[i] means s[0..i) can be segmented; check every earlier cut that is reachable.
bool word_break(const string&s,const unordered_set<string>&dict){
    int n=s.size();vector<char>dp(n+1);dp[0]=1;for(int i=1;i<=n;++i)for(int j=0;j<i;++j)if(dp[j]&&dict.count(s.substr(j,i-j)))dp[i]=1;return dp[n];
}
```

### 8. Decode Ways
**Problem:** Count the ways to decode a digit string into letters.
```cpp
// Zero can only appear as part of a valid 10..26 pair; it cannot start a one-digit decoding.
int decode_ways(const string&s){
    int n=s.size();if(!n||s[0]=='0')return 0;long long p2=1,p1=1;
    for(int i=1;i<n;++i){long long cur=0;if(s[i]!='0')cur+=p1;int x=10*(s[i-1]-'0')+s[i]-'0';if(x>=10&&x<=26)cur+=p2;p2=p1;p1=cur;}return p1;
}
```

### 9. Unique paths / minimum path sum
```cpp
// For unique paths, each cell is top + left; for min path sum, replace addition with min transition.
long long unique_paths(int m,int n){
    vector<long long>dp(n);dp[0]=1;for(int i=0;i<m;++i)for(int j=1;j<n;++j)dp[j]+=dp[j-1];return dp[n-1];
}
long long min_path_sum(vector<vector<int>>g){
    int m=g.size(),n=g[0].size();for(int i=0;i<m;++i)for(int j=0;j<n;++j){if(i||j){int up=i?g[i-1][j]:INT_MAX/2,left=j?g[i][j-1]:INT_MAX/2;g[i][j]+=min(up,left);}}return g[m-1][n-1];
}
```

### 10. N-Queens
**Problem:** Place n queens on an n x n board so that no two attack each other.
```cpp
// col, diag1, and diag2 masks encode exactly the unavailable positions for the next row.
long long nqueens(int n){
    long long full=(1LL<<n)-1;
    function<long long(long long,long long,long long)>dfs=[&](long long c,long long d1,long long d2)->long long{
        if(c==full)return 1;long long ans=0,avail=full&~(c|d1|d2);
        while(avail){long long b=avail&-avail;avail-=b;ans+=dfs(c|b,(d1|b)<<1,(d2|b)>>1);}return ans;
    };
    return dfs(0,0,0);
}
```

### 11. Hard transfer - 2945 - Find Maximum Non-decreasing Array Length
**Problem:** Split the array into the maximum number of contiguous parts whose sums are non-decreasing.
**Link:** https://leetcode.com/problems/find-maximum-non-decreasing-array-length/description/?envType=problem-list-v2&envId=0xtaf9f6
```cpp
// The state is the number of parts made so far plus the start of the last merged block; prefix sums make the next feasible cut a lower_bound.
class Solution {
public:
    int findMaximumLength(vector<int>& nums) {
        int n = nums.size(); vector<long long> pref(n + 1), bestLeft(n + 2), dp(n + 1);
        for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + nums[i];
        for (int i = 1; i <= n; ++i) {
            bestLeft[i] = max(bestLeft[i], bestLeft[i - 1]);
            long long need = 2 * pref[i] - pref[bestLeft[i]];
            int r = lower_bound(pref.begin(), pref.end(), need) - pref.begin();
            dp[i] = dp[bestLeft[i]] + 1;
            bestLeft[r] = i;
        }
        return dp[n];
    }
};
```
# Saturday - Fenwick / Segment Tree
**0-8:** Daily Core. **8-38:** Week A/B range cards. **38-53:** GCD/DP Segment Tree Hard transfer. **53-60:** retype misses + edge case.
**Week A:** Fenwick -> coordinate compression -> generic Segment Tree -> lazy add+sum -> max-subarray tree.
**Week B:** generic monoid -> generic lazy -> add+min/max/sum -> min+frequency.
### 1. Fenwick Tree
```cpp
struct BIT {
    int n; vector<long long> ft;
    BIT(int n) : n(n), ft(n + 1, 0) {}
    void upd(int x, long long v) { for (; x <= n; x += x & -x) ft[x] += v; }
    long long sum(int x) { long long res = 0; for (; x; x -= x & -x) res += ft[x]; return res; }
    long long qry(int l, int r) { return sum(r) - sum(l - 1); }
};
```

### 2. Coordinate Compression
```cpp
// Compress only when ordering/rank matters; preserve the original values separately if they are needed later.
vector<long long> xs = a;
sort(xs.begin(), xs.end());
xs.erase(unique(xs.begin(), xs.end()), xs.end());
int id = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
```

### 3. Generic associative Segment Tree
```cpp
// Only associativity is required; commutativity is optional, and the identity is used for disjoint query parts.
// Only associativity is required; commutativity is optional, and the identity is used for disjoint query parts.
template<class T,class F>
struct SegTree {
    int n; T id; F op; vector<T> st;
    SegTree(const vector<T>& a,T id,F op):n(a.size()),id(id),op(op),st(2*n,id){
        for(int i=0;i<n;++i)st[n+i]=a[i];
        for(int i=n-1;i;--i)st[i]=op(st[i<<1],st[i<<1|1]);
    }
    void setPoint(int p,T x){
        st[p+=n]=x;
        for(p>>=1;p;p>>=1)st[p]=op(st[p<<1],st[p<<1|1]);
    }
    T query(int l,int r){
        T L=id,R=id;
        for(l+=n,r+=n;l<r;l>>=1,r>>=1){
            if(l&1)L=op(L,st[l++]);
            if(r&1)R=op(st[--r],R);
        }
        return op(L,R);
    }
};
```

### 4. Generic Lazy Segment Tree
```cpp
// Associative merge is required; lazy tags must form a composable action on nodes, with order preserved for noncommutative updates.
template<class Node,class Tag,class Merge,class Apply,class Compose>
struct LazySegTree {
    int n; Node idNode; Tag idTag; Merge merge; Apply apply; Compose compose;
    vector<Node> st; vector<Tag> lazy; vector<char> has;
    LazySegTree(const vector<Node>&a,Node idNode,Tag idTag,Merge merge,Apply apply,Compose compose):n(a.size()),idNode(idNode),idTag(idTag),merge(merge),apply(apply),compose(compose),st(4*n,idNode),lazy(4*n,idTag),has(4*n){
        build(1,0,n-1,a);
    }
    void build(int v,int l,int r,const vector<Node>&a){
        if(l==r){st[v]=a[l];return;}
        int m=(l+r)/2;build(v*2,l,m,a);build(v*2+1,m+1,r,a);st[v]=merge(st[v*2],st[v*2+1]);
    }
    void applyTag(int v,const Tag&t,int len){apply(st[v],t,len);if(has[v])lazy[v]=compose(t,lazy[v]);else lazy[v]=t,has[v]=1;}
    void push(int v,int l,int r){if(!has[v]||l==r)return;int m=(l+r)/2;applyTag(v*2,lazy[v],m-l+1);applyTag(v*2+1,lazy[v],r-m);lazy[v]=idTag;has[v]=0;}
    void update(int ql,int qr,const Tag&t,int v=1,int l=0,int r=-1){
        if(r<0)r=n-1;if(qr<l||r<ql)return;if(ql<=l&&r<=qr){applyTag(v,t,r-l+1);return;}
        push(v,l,r);int m=(l+r)/2;update(ql,qr,t,v*2,l,m);update(ql,qr,t,v*2+1,m+1,r);st[v]=merge(st[v*2],st[v*2+1]);
    }
    Node query(int ql,int qr,int v=1,int l=0,int r=-1){
        if(r<0)r=n-1;if(qr<l||r<ql)return idNode;if(ql<=l&&r<=qr)return st[v];
        push(v,l,r);int m=(l+r)/2;return merge(query(ql,qr,v*2,l,m),query(ql,qr,v*2+1,m+1,r));
    }
};
```

### 5. Lazy Segment Tree: range add + range sum
```cpp
// For a node covering len elements, adding x increases its sum by x*len and its lazy tag by x.
struct LazySum {
    int n; vector<long long> st,lz;
    LazySum(int n):n(n),st(4*n),lz(4*n){}
    void apply(int v,int l,int r,long long x){st[v]+=x*(r-l+1);lz[v]+=x;}
    void push(int v,int l,int r){if(!lz[v]||l==r)return;int m=(l+r)/2;apply(v*2,l,m,lz[v]);apply(v*2+1,m+1,r,lz[v]);lz[v]=0;}
    void add(int ql,int qr,long long x,int v=1,int l=0,int r=-1){
        if(r<0)r=n-1;if(qr<l||r<ql)return;
        if(ql<=l&&r<=qr){apply(v,l,r,x);return;}
        push(v,l,r);int m=(l+r)/2;add(ql,qr,x,v*2,l,m);add(ql,qr,x,v*2+1,m+1,r);st[v]=st[v*2]+st[v*2+1];
    }
    long long query(int ql,int qr,int v=1,int l=0,int r=-1){
        if(r<0)r=n-1;if(qr<l||r<ql)return 0;
        if(ql<=l&&r<=qr)return st[v];
        push(v,l,r);int m=(l+r)/2;return query(ql,qr,v*2,l,m)+query(ql,qr,v*2+1,m+1,r);
    }
};
```

### 6. Lazy Segment Tree: range add + min/max/sum
```cpp
// A range add shifts sum, minimum, and maximum by predictable amounts, so one lazy tag is sufficient.
struct AddMinMax {
    struct Node{long long sum,mn,mx;int len;};
    int n; vector<Node> st; vector<long long> lz;
    AddMinMax(const vector<long long>& a):n(a.size()),st(4*n),lz(4*n){build(1,0,n-1,a);}
    void build(int v,int l,int r,const vector<long long>& a){
        if(l==r){st[v]={a[l],a[l],a[l],1};return;}int m=(l+r)/2;build(v*2,l,m,a);build(v*2+1,m+1,r,a);pull(v);
    }
    void pull(int v){st[v].sum=st[v*2].sum+st[v*2+1].sum;st[v].mn=min(st[v*2].mn,st[v*2+1].mn);st[v].mx=max(st[v*2].mx,st[v*2+1].mx);st[v].len=st[v*2].len+st[v*2+1].len;}
    void apply(int v,long long x){st[v].sum+=x*st[v].len;st[v].mn+=x;st[v].mx+=x;lz[v]+=x;}
    void push(int v){if(lz[v]){apply(v*2,lz[v]);apply(v*2+1,lz[v]);lz[v]=0;}}
    void add(int ql,int qr,long long x,int v=1,int l=0,int r=-1){
        if(r<0)r=n-1;if(qr<l||r<ql)return;if(ql<=l&&r<=qr){apply(v,x);return;}push(v);int m=(l+r)/2;add(ql,qr,x,v*2,l,m);add(ql,qr,x,v*2+1,m+1,r);pull(v);
    }
    Node query(int ql,int qr,int v=1,int l=0,int r=-1){
        if(r<0)r=n-1;if(qr<l||r<ql)return {0,LLONG_MAX,LLONG_MIN,0};
        if(ql<=l&&r<=qr)return st[v];push(v);int m=(l+r)/2;auto a=query(ql,qr,v*2,l,m),b=query(ql,qr,v*2+1,m+1,r);if(!a.len)return b;if(!b.len)return a;return {a.sum+b.sum,min(a.mn,b.mn),max(a.mx,b.mx),a.len+b.len};
    }
};
```

### 7. Segment Tree: maximum subarray sum
```cpp
// Four aggregate fields are exactly the information needed to combine two adjacent segments.
struct MaxSubSeg {
    struct N{long long sum,pref,suff,best;};
    int n; vector<N> st;
    N mergeN(N a,N b){return {a.sum+b.sum,max(a.pref,a.sum+b.pref),max(b.suff,b.sum+a.suff),max({a.best,b.best,a.suff+b.pref})};}
    MaxSubSeg(const vector<long long>& a):n(a.size()),st(4*n){build(1,0,n-1,a);}
    void build(int v,int l,int r,const vector<long long>& a){if(l==r){st[v]={a[l],a[l],a[l],a[l]};return;}int m=(l+r)/2;build(v*2,l,m,a);build(v*2+1,m+1,r,a);st[v]=mergeN(st[v*2],st[v*2+1]);}
    void setPoint(int p,long long x,int v=1,int l=0,int r=-1){if(r<0)r=n-1;if(l==r){st[v]={x,x,x,x};return;}int m=(l+r)/2;if(p<=m)setPoint(p,x,v*2,l,m);else setPoint(p,x,v*2+1,m+1,r);st[v]=mergeN(st[v*2],st[v*2+1]);}
};
```

### 8. Segment Tree: minimum value + frequency
```cpp
// On equal minima, add frequencies; on unequal minima, keep only the smaller side.
struct MinCountSeg {
    using N=pair<int,int>;
    int n; vector<N> st;
    static N op(N a,N b){if(a.first<b.first)return a;if(b.first<a.first)return b;return {a.first,a.second+b.second};}
    MinCountSeg(const vector<int>& a):n(a.size()),st(2*n){for(int i=0;i<n;++i)st[n+i]={a[i],1};for(int i=n-1;i;--i)st[i]=op(st[i<<1],st[i<<1|1]);}
    N query(int l,int r){N L={INT_MAX,0},R={INT_MAX,0};for(l+=n,r+=n;l<r;l>>=1,r>>=1){if(l&1)L=op(L,st[l++]);if(r&1)R=op(st[--r],R);}return op(L,R);}
};
```

### 9. Hard transfer - 3901 - Good Subsequence Queries: GCD Segment Tree variant
**Problem:** Support updates and queries for a GCD-based subsequence condition.
**Link:** https://leetcode.com/problems/good-subsequence-queries/description/?envType=problem-list-v2&envId=0xtaf9f6
```cpp
// GCD is associative with identity 0, so it fits the generic Segment Tree directly; use 0 for values that cannot participate.
struct GcdSeg {
    int n; vector<long long> st;
    GcdSeg(const vector<long long>& a) : n(a.size()), st(4 * n + 5) { build(1, 0, n - 1, a); }
    void build(int v, int l, int r, const vector<long long>& a) { if (l == r) { st[v] = a[l]; return; } int m=(l+r)/2; build(v*2,l,m,a); build(v*2+1,m+1,r,a); st[v]=gcd(st[v*2],st[v*2+1]); }
    void update(int v, int l, int r, int p, long long x) { if (l == r) { st[v] = x; return; } int m=(l+r)/2; if(p<=m) update(v*2,l,m,p,x); else update(v*2+1,m+1,r,p,x); st[v]=gcd(st[v*2],st[v*2+1]); }
    void update(int p, long long x) { update(1,0,n-1,p,x); }
    long long query(int v, int l, int r, int ql, int qr) { if(qr<l || r<ql) return 0; if(ql<=l && r<=qr) return st[v]; int m=(l+r)/2; return gcd(query(v*2,l,m,ql,qr), query(v*2+1,m+1,r,ql,qr)); }
    long long query(int l, int r) { return l > r ? 0 : query(1,0,n-1,l,r); }
};
```

### 10. Hard transfer - 3920 - Maximize Fixed Points After Deletions
**Problem:** Delete elements to maximize how many remaining positions become fixed points.
**Link:** https://leetcode.com/problems/maximize-fixed-points-after-deletions/?envType=problem-list-v2&envId=0xtaf9f6
```cpp
// Group equal values first so states from the same value do not chain; d=i-value is the monotone coordinate used by the Segment Tree.
struct FixedPointSeg {
    int l, r, ma; FixedPointSeg *left, *right;
    FixedPointSeg(int le, int ri) : l(le), r(ri), ma(0), left(nullptr), right(nullptr) {
        if (l != r) { int m = l + (r - l) / 2; left = new FixedPointSeg(l, m); right = new FixedPointSeg(m + 1, r); }
    }
    void update(int n, int x) {
        if (l <= n && n <= r) { ma = max(ma, x); if (left) left->update(n, x); if (right) right->update(n, x); }
    }
    int query(int ql, int qr) {
        if (ql <= l && r <= qr) return ma;
        if (l > qr || r < ql) return 0;
        return max(left->query(ql, qr), right->query(ql, qr));
    }
};

class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());
        vector<vector<int>> groups(mx + 1);
        for (int i = 0; i < (int)nums.size(); ++i) if (nums[i] <= i) groups[nums[i]].push_back(i - nums[i]);
        FixedPointSeg seg(0, (int)nums.size());
        int ans = 0;
        for (int v = 0; v <= mx; ++v) {
            vector<pair<int,int>> batch;
            for (int d : groups[v]) { int cur = seg.query(0, d) + 1; batch.push_back({d, cur}); ans = max(ans, cur); }
            for (auto [d, cur] : batch) seg.update(d, cur);
        }
        return ans;
    }
};
```
# Sunday - C++ Pointer / OOP / Quant Simulation
**0-8:** Daily Core. **8-28:** detailed C++ systems lab. **28-48:** timed benchmark. **48-55:** STL/quant drill. **55-60:** failure retype.
**Week A:** full Pointer + OOP Systems Lab. **Week B:** full Order Book drill + pointer/tree excerpts.
### 1. C++ Pointer + OOP Systems Lab
```cpp
#include <bits/stdc++.h>
using namespace std;

class Instrument {
protected:
    long long id, px;
public:
    Instrument(long long id, long long px) : id(id), px(px) {}
    virtual ~Instrument() = default;
    long long getId() const { return id; }
    virtual long long value(long long qty) const = 0;
    virtual string kind() const = 0;
};

class FutureOrder : public Instrument {
public:
    FutureOrder(long long id, long long px) : Instrument(id, px) {}
    long long value(long long qty) const override { return px * qty; }
    string kind() const override { return "FUT"; }
};

class OptionOrder : public Instrument {
    long long strike;
public:
    OptionOrder(long long id, long long px, long long strike) : Instrument(id, px), strike(strike) {}
    long long value(long long qty) const override { return max(0LL, px - strike) * qty; }
    string kind() const override { return "OPT"; }
};

struct TreeNode {
    long long key;
    TreeNode* parent = nullptr;
    unique_ptr<TreeNode> left, right;
    explicit TreeNode(long long key) : key(key) {}
};

class SearchTree {
    unique_ptr<TreeNode> root;

    TreeNode* insert(unique_ptr<TreeNode>& node, TreeNode* parent, long long x) {
        if (!node) { node = make_unique<TreeNode>(x); node->parent = parent; return node.get(); }
        if (x < node->key) return insert(node->left, node.get(), x);
        if (x > node->key) return insert(node->right, node.get(), x);
        return node.get();
    }

    const TreeNode* find(const unique_ptr<TreeNode>& node, long long x) const {
        if (!node || node->key == x) return node.get();
        return x < node->key ? find(node->left, x) : find(node->right, x);
    }

    void inorder(const unique_ptr<TreeNode>& node, vector<long long>& out) const {
        if (!node) return;
        inorder(node->left, out); out.push_back(node->key); inorder(node->right, out);
    }

public:
    TreeNode* insert(long long x) { return insert(root, nullptr, x); }
    const TreeNode* find(long long x) const { return find(root, x); }
    vector<long long> sorted() const { vector<long long> out; inorder(root, out); return out; }
};

template<class T, class Compare = less<T>>
class TopK {
    priority_queue<T, vector<T>, Compare> pq;
    size_t k;
public:
    explicit TopK(size_t k) : k(k) {}
    void add(const T& x) {
        if (k == 0) return;
        pq.push(x);
        if (pq.size() > k) pq.pop();
    }
    const T& worst() const { return pq.top(); }
};

class Portfolio {
    vector<unique_ptr<Instrument>> instruments;
    unordered_map<long long, Instrument*> byId;
public:
    void add(unique_ptr<Instrument> p) {
        long long id = p->getId();
        Instrument* raw = p.get();
        byId[id] = raw;
        instruments.push_back(move(p));
    }
    long long exposure(long long qty) const {
        long long ans = 0;
        for (const auto& p : instruments) ans += p->value(qty);
        return ans;
    }
    Instrument* get(long long id) const {
        auto it = byId.find(id);
        return it == byId.end() ? nullptr : it->second;
    }
};

int main() {
    Portfolio p;
    p.add(make_unique<FutureOrder>(1, 100));
    p.add(make_unique<OptionOrder>(2, 125, 110));

    SearchTree t;
    t.insert(8); t.insert(3); t.insert(10); t.insert(1); t.insert(6);
    auto order = t.sorted();

    return p.exposure(10) + (order.size() == 5 ? 0 : 1);
}
```

### 2. Quant-style order-book / STL drill
```cpp
struct Quote {
    long long id, px, qty;
};

class MiniOrderBook {
    map<long long, deque<Quote>, greater<long long>> bids;
    map<long long, deque<Quote>> asks;

public:
    void addBid(Quote q) { bids[q.px].push_back(q); }
    void addAsk(Quote q) { asks[q.px].push_back(q); }
    const Quote* bestBid() const {
        if (bids.empty() || bids.begin()->second.empty()) return nullptr;
        return &bids.begin()->second.front();
    }
    const Quote* bestAsk() const {
        if (asks.empty() || asks.begin()->second.empty()) return nullptr;
        return &asks.begin()->second.front();
    }
    void cancelBid(long long px) {
        auto it = bids.find(px);
        if (it != bids.end() && !it->second.empty()) it->second.pop_front();
        if (it != bids.end() && it->second.empty()) bids.erase(it);
    }
};
```

### 3. Optional low-level drill - every 3-4 Sundays
```cpp
template<class T, size_t N>
class ObjectPool {
    alignas(T) unsigned char storage[N][sizeof(T)];
    bool used[N]{};
public:
    template<class... Args> T* create(Args&&... args) {
        for (size_t i = 0; i < N; ++i) if (!used[i]) {
            used[i] = true;
            return new (storage[i]) T(forward<Args>(args)...);
        }
        return nullptr;
    }
    void destroy(T* p) {
        if (!p) return;
        p->~T();
        size_t i = (reinterpret_cast<unsigned char*>(p) - &storage[0][0]) / sizeof(T);
        if (i < N) used[i] = false;
    }
};
```

**Timed benchmark pool:** 3139, 3213, 3256, 3260, 3266, 3303, 3609, 4007. Give yourself the same 18-27 minute limit; no code lookup first.
**Quant/developer focus:** object lifetime, ownership, pointers/references, `const`, `virtual/override`, templates, move semantics, custom ordering, STL, tree nodes, RAII.

