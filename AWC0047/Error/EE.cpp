#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int len, link;
        int minPos; // endpos 集合中的最小值
        map<char, int> next;
    };
    
    vector<State> st;
    int sz, last;
    
    SuffixAutomaton(int maxLen) {
        st.resize(2 * maxLen);
        st[0].len = 0;
        st[0].link = -1;
        st[0].minPos = -1;
        sz = 1;
        last = 0;
    }
    
    void extend(char c, int pos) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        st[cur].minPos = pos;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                st[clone].minPos = st[q].minPos;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    
    // 查询长度为 len 的循环子串 [start, start+len) 是否在 S 中出现
    bool query(const string &U, long long start, long long len, int N) {
        int v = 0;
        for (int i = 0; i < len; i++) {
            char c = U[start + i];
            if (!st[v].next.count(c)) return false;
            v = st[v].next[c];
        }
        // 匹配成功，检查是否在原串范围内
        return st[v].minPos - st[v].len + 1 + len <= N;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    string S;
    cin >> N >> Q >> S;
    
    string U = S + S;
    SuffixAutomaton sam(N);
    
    // 构建 S 的 SAM
    for (int i = 0; i < N; i++) {
        sam.extend(S[i], i);
    }
    
    while (Q--) {
        long long L, R;
        cin >> L >> R;
        long long len = R - L + 1;
        
        if (len > N) {
            cout << "No\n";
            continue;
        }
        
        long long start = (L - 1) % N;
        
        // 不跨边界
        if (start + len <= N) {
            cout << "Yes\n";
            continue;
        }
        
        // 跨边界
        if (sam.query(U, start, len, N)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}