#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define fo(i, n) for(int i = 1; i <= n; ++i)
typedef long long ll;
 
const int N = 200200;
const int mod = 1e9 + 7;
typedef long double ld;
const ld eps = 1e-15L;
 
 
vector<int> g[N], e[N];
int n, u, v, m, c, tin[N], tout[N], tmr;
int up[N][21];
ll h[N];
ll le[N], ri[N];
ld ans[N];
ll sz[N], root[N];
ll at[N];
 
struct line {
    ld k, b;
    line() {}
    line(ld K, ld B) {k = K, b = B;}
    const bool operator < (const line &a) const {
        if(abs(k - a.k) < eps) return b > a.b;
        return k > a.k;
    }
};
 
inline void calc_sz(int v, int p = 0) {
    sz[v] = 1;
    for(int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i], cost = e[v][i];
        if (to != p) h[to] = h[v] +  cost, calc_sz(to, v), sz[v] += sz[to];
    }
    for(int i = 0; i < g[v].size(); ++i)
        if(sz[g[v][i]] > sz[g[v][0]]) swap(g[v][i], g[v][0]);
}
 
inline void dfs(int v, int p, int hld_root) {
    up[v][0] = p, tin[v] = ++tmr, root[v] = hld_root;
    at[tin[v]] = v;
    for(int i = 1; i <= 20; ++i) up[v][i] = up[up[v][i - 1]][i - 1];
    int c = 0;
    for(int to : g[v]) {
        if(to == p) continue;
        dfs(to, v, (c == 0 ? hld_root : to));
        c++;
    }
    tout[v] = tmr;
}
 
inline bool upper(int a, int b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; }
 
inline int get_lca(int a, int b) {
    if(upper(a, b)) return a;
    if(upper(b, a)) return b;
    for(int i = 20; i >= 0; --i) if(!upper(up[a][i], b)) a = up[a][i];
    return up[a][0];
}
 
vector<line> t[4 * N];
 
inline void upd(int v, int tl, int tr, int l, int r, ld k, ld b) {
    if(l > r) return;
    if(tl == l && tr == r) {
        t[v].pb(line(k, b));
        return;
    }
    int tm = tl + tr >> 1;
    upd(v + v, tl, tm, l, min(r, tm), k, b);
    upd(v + v + 1, tm + 1, tr, max(tm + 1, l), r, k, b);
}
 
inline void solve(int u, int v, ld timein, ld velocity) {
    velocity = 1.0L / velocity;
    int lca = get_lca(u, v);
    ld dist = h[v] + h[u] - 2 * h[lca], timeout = timein + dist * velocity;
    // timein + (h[v] - h[x]) * velocity
    // timein + h[v] * velocity - h[x] * velocity
    ld k = -velocity, b = timein + h[u] * velocity;
    while (true) {
        if (root[u] == root[lca]) {
            upd(1, 1, n, tin[lca], tin[u], k, b);
            break;
        }
        int ro = root[u];
        upd(1, 1, n, tin[ro], tin[u], k, b);
        u = up[ro][0];
    }
    // timeout - velocity * (h[v] - h[x])
    // timeout - velocity * h[v] + h[x] * velocity
    k = velocity, b = timeout - velocity * h[v];
    while(true) {
        if(root[v] == root[lca]) {
            upd(1, 1, n, tin[lca], tin[v], k, b);
            break;
        }
        int ro = root[v];
        upd(1, 1, n, tin[ro], tin[v], k, b);
        v = up[ro][0];
    }
}
 
inline bool better(line a, line b, line c) {
    return (0.0L  + a.b - c.b) * (b.k - a.k) - eps < (0.0L + a.b - b.b) * (c.k - a.k);
}
 
vector<line> lines[4 * N];
 
inline void add(int id, ld k, ld b) {
    int sz = lines[id].size();
    while(sz > 1 && better(lines[id][sz - 2], lines[id][sz - 1], line(k, b)))
        sz--, lines[id].pop_back();
    lines[id].emplace_back(line(k, b));
}
 
inline void build_hull(int v) {
    sort(t[v].begin(), t[v].end());
    for(auto &x : t[v]) add(v, x.k, x.b);
}
vector<pair<ll, ll> > cur;
int pos[4 * N];
 
inline ld get_val(line a, ld x) {
    return a.k * x + a.b;
}
 
inline void upd_pos(int v, ld x) {
    if(pos[v] > int(lines[v].size()) - 1)
        pos[v] = int(lines[v].size()) - 1;
    while(pos[v] + 1 < lines[v].size() && get_val(lines[v][pos[v] + 1], x) - eps <= get_val(lines[v][pos[v]], x))
        pos[v]++;
}
 
inline ld Get(int v, ld x) {
    if(lines[v].empty() == true) return 2e18;
    upd_pos(v, x);
    return get_val(lines[v][pos[v]], x);
 
}
inline void build(int v, int tl, int tr) {
    build_hull(v);
  /*  cerr << "! " << v << ' '<<tl<<' '<<tr << endl;
    for(int i = tl; i <= tr; ++i)
        cerr<<at[i] << ' ';
    cerr<<endl;
    for(auto &x : lines[v]) cerr<<x.k << ' '<<x.b << endl;
    */cur.clear();
    for(int i = tl; i <= tr; ++i) cur.pb({h[at[i]], at[i]});
    sort(cur.begin(), cur.end());
    for(auto &x: cur)  {
        ans[x.second] = min(ans[x.second], Get(v, x.first));
        /*for(auto &y : t[v]) {
            ans[x.second] = min(ans[x.second], get_val(y, x.first));
        }*/
    }
    if(tl == tr) return;
    int tm = tl + tr >> 1;
    build(v + v, tl, tm);
    build(v + v + 1, tm + 1, tr);
}
 
inline void solve() {
    cin >> n;
    fo(i, n) g[i].clear(),e[i].clear(), tin[i] = tout[i] = 0, tmr = 0, ans[i] = 2e18;
    fo(i,4 * n) t[i].clear(), lines[i].clear(), pos[i] = 0;
    fo(i, n - 1) {
        cin >> u >> v >> c;
        g[u].pb(v);
        e[u].pb(c);
        g[v].pb(u);
        e[v].pb(c);
    }
    calc_sz(1);
    dfs(1, 0, 1);
 
    cin >> m;
    for(int i = 1; i <= m; ++i) {
        ld timein, velocity;
        cin >> u >> v >> timein >> velocity;
        solve(u, v, timein, velocity);
    }
 
    build(1, 1, n);
 
    cout.precision(10);
    fo(i, n) {
        if(ans[i] + eps >= 2e18L) cout << -1 << '\n';
        else cout << fixed << ans[i] << '\n';
    }
}
 
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tout[0] = mod;
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
} 
