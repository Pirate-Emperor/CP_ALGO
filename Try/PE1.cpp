#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Structure to maintain the state of the complement set A
struct E_A_State {
    vector<int> elems;
    int and_sum;
    vector<int> bit_counts;
};

// Initialize the complement set state
E_A_State init_E_A(const vector<int>& A, int k) {
    E_A_State state;
    state.elems = A;
    if (A.empty()) {
        state.and_sum = (1 << k) - 1;
        state.bit_counts.assign(k, 0);
        return state;
    }
    state.and_sum = A[0];
    state.bit_counts.assign(k, 0);
    for (int a : state.elems) {
        state.and_sum &= a;
        for (int b = 0; b < k; b++) {
            if ((a >> b) & 1) {
                state.bit_counts[b]++;
            }
        }
    }
    return state;
}

// Compute the next complement set state when a 0-bit of n is processed
E_A_State next_E_A_state(const E_A_State& curr, int x, int k) {
    E_A_State state;
    for (int a : curr.elems) {
        if (!((a >> x) & 1)) {
            state.elems.push_back(a);
        }
    }
    if (state.elems.empty()) {
        state.and_sum = (1 << k) - 1;
        state.bit_counts.assign(k, 0);
        return state;
    }
    state.and_sum = state.elems[0];
    state.bit_counts.assign(k, 0);
    for (int a : state.elems) {
        state.and_sum &= a;
        for (int b = 0; b < k; b++) {
            if ((a >> b) & 1) {
                state.bit_counts[b]++;
            }
        }
    }
    return state;
}

// DP function to count valid layer permutations
long long solve(int mask, int mask_1, const E_A_State& curr, int k, int n, 
                const vector<int>& weights, const vector<int>& C, map<pair<int, int>, long long>& memo) {
    int step = __builtin_popcount(mask);
    if (step == k) {
        return 1;
    }
    pair<int, int> state_key = {mask, mask_1};
    if (memo.count(state_key)) {
        return memo[state_key];
    }
    
    int i = k - 1 - step;
    long long ans = 0;
    bool bit_n = (n >> i) & 1;
    
    for (int x = 0; x < k; x++) {
        if (!(mask & (1 << x))) {
            if (weights[x] == C[i]) {
                if (bit_n) {
                    // If i-th bit of n is 1, all elements in curr must have bit x == 1
                    if ((curr.and_sum >> x) & 1) {
                        ans += solve(mask | (1 << x), mask_1 | (1 << x), curr, k, n, weights, C, memo);
                    }
                } else {
                    // If i-th bit of n is 0, exactly 2^i elements must have bit x == 1
                    if (curr.bit_counts[x] == (1 << i)) {
                        E_A_State next_state = next_E_A_state(curr, x, k);
                        ans += solve(mask | (1 << x), mask_1, next_state, k, n, weights, C, memo);
                    }
                }
            }
        }
    }
    return memo[state_key] = ans;
}

void solve_test_case() {
    int n;
    if (!(cin >> n)) return;
    int k = 0;
    while ((1 << k) <= n) {
        k++;
    }
    
    vector<string> S(k);
    for (int i = 0; i < k; i++) {
        cin >> S[i];
    }
    
    // Check for duplicate strings in the input
    vector<string> sorted_S = S;
    sort(sorted_S.begin(), sorted_S.end());
    bool duplicate = false;
    for (int i = 1; i < k; i++) {
        if (sorted_S[i] == sorted_S[i-1]) duplicate = true;
    }
    if (duplicate) {
        cout << 0 << "\n";
        return;
    }
    
    // Construct initial column integers
    vector<int> M(n, 0);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < k; i++) {
            if (S[i][j] == '1') {
                M[j] |= (1 << i);
            }
        }
    }
    
    // Columns must be distinct and non-zero
    vector<int> sorted_M = M;
    sort(sorted_M.begin(), sorted_M.end());
    bool ok = true;
    for (int j = 0; j < n; j++) {
        if (sorted_M[j] == 0) ok = false;
        if (j > 0 && sorted_M[j] == sorted_M[j-1]) ok = false;
    }
    if (!ok) {
        cout << 0 << "\n";
        return;
    }
    
    // Compute the target set bit frequencies
    vector<int> C(k, 0);
    for (int j = 1; j <= n; j++) {
        for (int i = 0; i < k; i++) {
            if ((j >> i) & 1) {
                C[i]++;
            }
        }
    }
    
    // Compute input layer bit frequencies (weights)
    vector<int> weights(k, 0);
    for (int i = 0; i < k; i++) {
        int w = 0;
        for (char c : S[i]) if (c == '1') w++;
        weights[i] = w;
    }
    
    // Multisets of weights must match
    vector<int> sorted_weights = weights;
    vector<int> sorted_C = C;
    sort(sorted_weights.begin(), sorted_weights.end());
    sort(sorted_C.begin(), sorted_C.end());
    if (sorted_weights != sorted_C) {
        cout << 0 << "\n";
        return;
    }
    
    // Build the complement set A
    vector<bool> in_M(1 << k, false);
    for (int x : M) {
        if (x < (1 << k)) in_M[x] = true;
    }
    vector<int> A;
    for (int x = 1; x < (1 << k); x++) {
        if (!in_M[x]) {
            A.push_back(x);
        }
    }
    
    E_A_State init_state = init_E_A(A, k);
    map<pair<int, int>, long long> memo;
    
    long long ans = solve(0, 0, init_state, k, n, weights, C, memo);
    cout << ans << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve_test_case();
        }
    }
    return 0;
}