#include <bits/stdc++.h>
using namespace std;

static const long long NEG = -(1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long K;
    cin >> N >> K;

    const int M = 2 * N;

    vector<vector<long long>> genre(M + 1);

    long long total = 0;

    for (int i = 0; i < M; i++) {
        int b;
        long long a;
        cin >> b >> a;

        genre[b].push_back(a);
        total += a;
    }

    if (total < K) {
        cout << -1 << '\n';
        return 0;
    }

    vector<vector<long long>> prefList;

    for (auto &v : genre) {
        if (v.empty()) continue;

        sort(v.begin(), v.end(), greater<long long>());

        int sz = (int)v.size();

        vector<long long> pref(sz + 1, 0);

        for (int i = 0; i < sz; i++) {
            pref[i + 1] = pref[i] + v[i];
        }

        prefList.push_back(move(pref));
    }

    auto check = [&](int X) -> bool {

        static long long dp[301][301];
        static long long ndp[301][301];

        for (int i = 0; i <= M; i++) {
            for (int j = 0; j <= M; j++) {
                dp[i][j] = NEG;
            }
        }

        dp[0][0] = 0;

        for (auto &pref : prefList) {

            int sz = (int)pref.size() - 1;

            for (int i = 0; i <= M; i++) {
                for (int j = 0; j <= M; j++) {
                    ndp[i][j] = NEG;
                }
            }

            for (int t = 0; t <= M; t++) {
                for (int mx = 0; mx <= M; mx++) {

                    if (dp[t][mx] == NEG) continue;

                    for (int k = 0; k <= sz; k++) {

                        if (t + k > M) break;

                        int nmx = max(mx, k);

                        ndp[t + k][nmx] =
                            max(
                                ndp[t + k][nmx],
                                dp[t][mx] + pref[k]
                            );
                    }
                }
            }

            memcpy(dp, ndp, sizeof(dp));
        }

        for (int t = 1; t <= M; t++) {
            for (int mx = 0; mx <= t; mx++) {

                if (dp[t][mx] < K) continue;

                if (1LL * mx <= 1LL * X * (t - mx + 1)) {
                    return true;
                }
            }
        }

        return false;
    };

    int L = 1;
    int R = M;
    int ans = M;

    while (L <= R) {
        int mid = (L + R) >> 1;

        if (check(mid)) {
            ans = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}