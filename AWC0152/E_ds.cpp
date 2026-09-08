#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500;
bitset<MAXN> move_[MAXN];
int cnt[MAXN][MAXN];
char win[MAXN][MAXN];
char h[MAXN][MAXN];
vector<int> inNodes[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> out(N), in(N);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        out[u].push_back(v);
        in[v].push_back(u);
        move_[u].set(v);
    }

    for (int i = 0; i < N; ++i) {
        move_[i].set(i);          // 停留
        inNodes[i] = in[i];
        inNodes[i].push_back(i);  // 包含自身
    }

    // 初始化 h[a][y]：a 是否本来就属于 move[y]
    for (int a = 0; a < N; ++a) {
        for (int y = 0; y < N; ++y) {
            h[a][y] = move_[y][a];
        }
    }

    vector<int> que;
    que.reserve(N * N);

    // 初始 cnt 和 win
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            if (x == y) continue;
            int c = (move_[x] & ~move_[y]).count();
            cnt[x][y] = c;
            if (c == 0) {
                win[x][y] = 1;
                que.push_back(x * N + y);
            }
        }
    }

    // 工作队列传播
    for (size_t head = 0; head < que.size(); ++head) {
        int code = que[head];
        int a = code / N;
        int b = code % N;

        for (int y : inNodes[b]) {
            if (h[a][y]) continue;
            h[a][y] = 1;

            for (int x : inNodes[a]) {
                if (x == y) continue;
                if (!win[x][y]) {
                    cnt[x][y]--;
                    if (cnt[x][y] == 0) {
                        win[x][y] = 1;
                        que.push_back(x * N + y);
                    }
                }
            }
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int S, R;
        cin >> S >> R;
        --S; --R;
        cout << (win[S][R] ? "NO" : "YES") << '\n';
    }

    return 0;
}