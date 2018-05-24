#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define fo(i, n) for(int i = 1; i <= n; ++i)

typedef long long ll;
typedef long double ld;

const int N = 200200;
const int mod = 20090717;

int n, m, k;
string s[11];

struct node {
    int nxt[26];
    int link, mask;
} t[102];

int sz;

inline void init() {
    memset(t, 0, sizeof t);
    sz = 0;
    t[0].link = -1;
}

inline void add(string &s, int id) {
    int v = 0, n = int(s.length());
    for(int i = 0; i < n; ++i) {
        if(!t[v].nxt[s[i] - 'a']) {
            t[v].nxt[s[i] - 'a'] = ++sz;
        }
        int to = t[v].nxt[s[i] - 'a'];
        v = to;
    }
    t[v].mask |= (1 << id);
}
int q[N];
int was[500][26];

inline int get(int v, int ch) {
    if(v == -1) return 0;
    if(was[v][ch] != -1) return was[v][ch];
    if(t[v].nxt[ch]) return was[v][ch] = t[v].nxt[ch];
    return was[v][ch] = get(t[v].link, ch);
}

inline void build() {
    int qs = 0, qt = 0;
    q[qt++] = 0;
    while(qs < qt) {
        int v = q[qs++];
        t[v].mask |= t[t[v].link].mask;
        for(int i = 0; i < 26; ++i)
            if(t[v].nxt[i]) {
                int to = t[v].nxt[i];
                t[to].link = get(t[v].link, i);
                q[qt++] = to;
            }
    }
}

inline void addmod(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}

int dp[2][110][(1 << 10)];


inline void solve() {
    for(int i = 0; i < m; ++i) cin >> s[i];
    init();
    for(int i = 0; i < m; ++i) add(s[i], i);
    for(int i = 0; i <= sz; ++i)
        for(int j = 0; j < 26; ++j)
            was[i][j] = -1;
    build();
    for(int i = 0; i <= sz; ++i) for(int j = 0; j < (1 << m); ++j) dp[0][i][j] = dp[1][i][j] = 0;
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for (int v = 0; v <= sz; ++v) {
            for (int mask = 0; mask < (1 << m); ++mask) {
                if(!dp[0][v][mask]) continue;
                for (int ch = 0; ch < 26; ++ch) {
                    int nv = get(v, ch);
                    addmod(dp[1][nv][mask | t[nv].mask], dp[0][v][mask]);
                }
            }
        }
        for (int v = 0; v <= sz; ++v)
            for (int mask = 0; mask < (1 << m); ++mask)
                dp[0][v][mask] = dp[1][v][mask], dp[1][v][mask] = 0;
    }

    int ans = 0;
    for(int mask = 0; mask < (1 << m); ++mask) for(int v = 0; v <= sz; ++v) if(k <= __builtin_popcount(mask)) addmod(ans, dp[0][v][mask]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while(cin >> n >> m >> k) {
        if(n + m + k == 0) break;
        solve();
    }
    return 0;
}
