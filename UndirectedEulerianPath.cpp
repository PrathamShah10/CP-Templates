/**
 *    author: Pratham_Shah10
 *    date: 19.03.2023
**/
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
#define endl "\n"
using namespace std;

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<": "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

ll binexpo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll min(ll a, ll b) {if (a > b) return b; return a;}
ll max(ll a, ll b) {if (a > b) return a; return b;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll lcm(ll a, ll b) {return ((a * b) / (gcd(a, b)));}


// undirected EuclerianPath:
// For such a path to exists if no. of outgoing edges from all nodes is even
// (in this case we can start from any node which has non-zero outgoing edges)
// but if no. of outgoing edges from all nodes is even except 2 nodes having
// odd no. of outgoing edges, then also the path exists provided that we start
// the traversal from any of these two nodes only

// traversal:
// we need to visit all edges exactly once.
// so we make adj list with corrosponding edge number to make it visited during
// traversal. done array represents how many edges(outgoing) of the current node
// have been traversed.

const int N = 2e5 + 2;
bool vis[N];
int done[N];
vector<pair<int, int>>adj[N];
vector<int>ans;
void dfs(int u) {
    while (done[u] < (int)adj[u].size()) {
        auto e = adj[u][done[u]++];
        if (vis[e.second]) continue;
        vis[e.second] = 1;
        dfs(e.first);
    }
    ans.push_back(u);
}
void solve() {
    int t = 1;
    // cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back({y, i});
            adj[y].push_back({x, i});
        }
        int odd = 0;
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() % 2 != 0) odd++;
        }
        if (odd != 0 && odd != 2) { //if start and end must be same then odd should be 0 only
            cout << "IMPOSSIBLE\n";
            continue;
        }
        dfs(1); // use root here acc to the above comments
        reverse(ans.begin(), ans.end());
        if ((int)ans.size() != m + 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        for (auto it : ans) {
            cout << it << " ";
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
}