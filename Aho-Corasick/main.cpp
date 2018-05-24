#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define fo(i, n) for(int i = 1; i <= n; ++i)

typedef long long ll;
typedef long double ld;

const int N = 200200;
const int mod = 1e9 + 7;

struct node {
    int nxt[26];
    int link;
    int term;
} t[N];
int sz, q[N], was[N][26];


inline void init() {
    memset(t, 0, sizeof t);
    sz = 0;
    t[0].link = -1;
}

inline void add(string &s) {
    int v = 0, n = int(s.length());
    for(int i = 0; i < n; ++i) {
        if(!t[v].nxt[s[i] - 'a']) {
            t[v].nxt[s[i] - 'a'] = ++sz;
        }
        int to = t[v].nxt[s[i] - 'a'];
        v = to;
    }
    t[v].term = 1;
}

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
        for(int i = 0; i < 26; ++i)
            if(t[v].nxt[i]) {
                int to = t[v].nxt[i];
                t[to].link = get(t[v].link, i);
                q[qt++] = to;
            }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    return 0;
}
