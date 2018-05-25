#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define fo(i, n) for(int i = 1; i <= n; ++i)

typedef long long ll;
typedef long double ld;

const int N = 500200;
const int mod = 1e9 + 7;

int n, a[N], q, l, r;

int nxt[N];

vector<int> t[4 * N];

map<int, int> was;

void merge(int v, int a, int b) {
    t[v].resize(t[a].size() + t[b].size());
    int i = 0, j = 0;
    while(i < t[a].size() || j < t[b].size()) {
        if(i == t[a].size()) t[v][i + j] = t[b][j], j++;
        else if(j == t[b].size()) t[v][i + j] = t[a][i], i++;
        else if(t[a][i] < t[b][j]) t[v][i + j] = t[a][i], i++;
        else t[v][i + j] = t[b][j], j++;
    }
}

void build(int v, int tl, int tr) {
    if(tl == tr) {
        t[v].push_back(nxt[tl]);
        return;
    }
    int tm = (tl + tr) / 2;

    build(v + v, tl, tm);
    build(v + v + 1, tm + 1, tr);

    merge(v, v + v, v + v + 1);
}

int get(int v, int tl, int tr, int l, int r, int x) {
    if(r < tl || tr < l) return 0;
    if(l <= tl && tr <= r) {
        int pos = upper_bound(t[v].begin(), t[v].end(), x) - t[v].begin();
        if(pos < t[v].size()) return t[v].size() - pos;
        return 0;
    }
    int tm = (tl + tr) / 2;
    return get(v + v, tl, tm, l, r, x) + get(v + v + 1, tm + 1, tr, l, r, x);
}

int solve(int l, int r) {
    return get(1, 1, n, l, r, r);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    for(int i = n; i >= 1; --i) {
        if(was[a[i]]) nxt[i] = was[a[i]];
        else nxt[i] = n + 1;
        was[a[i]] = i;
    }

    build(1, 1, n);

    cin >> q;
    for(int i = 1; i <= q; ++i) {
        cin >> l >> r;
        cout << solve(l, r) << '\n';
    }
    return 0;
}
