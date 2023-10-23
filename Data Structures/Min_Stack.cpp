// Queue modification to behave like Minimum Stack

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

deque<pair<int, int>> q;
int cnt_added = 0;
int cnt_removed = 0;
int n;

int find_min()
{
    int minimum = q.front().first;
    return minimum;
}

void add_element(int new_element)
{
    while (!q.empty() && q.back().first > new_element)
        q.pop_back();
    q.push_back({new_element, cnt_added});
    cnt_added++;
}

void remove_element()
{
    if (!q.empty() && q.front().second == cnt_removed) 
        q.pop_front();
    cnt_removed++;
}

void solve() {
    cin >> n;
    vector<int> arr(n);
    for (int i = 1; i <= n; i++) 
    {
        cin >> arr[i];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}