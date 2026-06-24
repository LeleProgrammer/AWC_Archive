#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 200005;
const int INF = 1e18;

int n;
int C[N], W[N];
vector<int> g[N];
int dp[N][2];  

void dfs(int u, int p) {
    vector<int> diffs;
    int base = 0; 
    
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        base += dp[v][1];
        diffs.push_back(dp[v][0] - dp[v][1]);
    }
    
    sort(diffs.begin(), diffs.end());
    
    int sz = diffs.size();
    vector<int> pref(sz + 1, 0);
    for (int i = 0; i < sz; i++) {
        pref[i + 1] = pref[i] + diffs[i];
    }
    
    dp[u][0] = INF;
    for (int t = 0; t <= sz; t++) {
        int cost = base + pref[t] + W[u] * max(0LL, t - C[u]);
        dp[u][0] = min(dp[u][0], cost);
    }
    
    dp[u][1] = INF;
    for (int t = 0; t <= sz; t++) {
        int m_u = t + 1;
        int cost = base + pref[t] + W[u] * max(0LL, m_u - C[u]);
        dp[u][1] = min(dp[u][1], cost);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    for (int i = 1; i <= n; i++) {
        cin >> C[i] >> W[i];
    }
    
    dfs(1, 0);
    
    cout << dp[1][0] + (n - 1) << '\n';
    
    return 0;
}