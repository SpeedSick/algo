#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define fo(i, n) for(int i = 1; i <= n; ++i)
#define tm sdfsdf
#define mt sdfsdfd

typedef long long ll;
typedef long double ld;

const int N = 500200;
const int mod = 1e9 + 7;

int n, a[N];
int lp[N];

inline void sieve() {
    lp[1] = 1;
    for(int i = 2; i < N; ++i)
        if(!lp[i]) {
            for(ll j = i * 1ll * i; j < N; j += i) lp[j] = i;
            lp[i] = i;
        }
}

inline void print(int test, int res) {
    cout << "Case " << test << ": " << res << '\n';
}

vector<int> g[N];
int p[N];
int ans;
int tmr, mt[N], tm[N], used[N];
map<int, int> hw;
vector<int> L, R;

inline void add(int val) {
    int x = val, parity = 0;
    vector<int> v;
    while(x > 1) { v.pb(val / lp[x]), x /= lp[x], parity ^= 1; }
    sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin());
    for(int i = 0, to; i < v.size(); ++i) {
        to = v[i];
        if(!hw.count(to)) continue;
        int x = hw[val], y = hw[to];
        if(!parity) swap(x, y);
        g[x].pb(y);
    }
}

inline bool dfs(int v) {
    if(used[v] == tmr) return false;
    used[v] = tmr;
    for(int i = 0, to; i < g[v].size(); ++i) {
        to = g[v][i];
        if(mt[to] == -1 || dfs(mt[to])) {mt[to] = v, tm[v] = to; return true;}
    }
    return false;
}

inline void solve(int test) {
    cin >> n;
    hw.clear(); L.clear(); R.clear();
    fo(i, n) cin >> a[i], hw[a[i]] = i, g[i].clear();
    fo(i, n) add(a[i]), mt[i] = tm[i] = -1, used[i] = 0;
    tmr = 0, ans = n;
    for(int run = 1; run; ) {
        run = 0, ++tmr;
        for(int i = 1; i <= n; ++i)
            if(!p[i] && tm[i] == -1 && dfs(i)) run = 1, --ans;
    }
    print(test, ans);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    sieve();
    fo(it, t) solve(it);
    return 0;
}
