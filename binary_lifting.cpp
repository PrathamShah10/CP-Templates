vector<int> adj[200001];
int up[200001][20]; // up[i][k] denotes the (2^k)th parent of the ith node
int lvl[200001];
void binary_lifting(int src, int par) { // call binary_lifting(1,-1)
    up[src][0] = par;
    for (int i = 1; i < 20; i++) { // i < log(number of nodes)
        if (up[src][i - 1] != -1)
            up[src][i] = up[up[src][i - 1]][i - 1];
        //here i denotes 2^ith parent of node src
        //for calculating up[src][i] (2^i th parent of src node) we can:
        //write it as up[2^(i-1) parent of src][i-1] -> this denotes
        //that the answer will be 2^(i-1) + 2^(i-1) = 2^i.
        else up[src][i] = -1;
    }

    for (int child : adj[src]) {
        if (child != par)
            binary_lifting(child, src);
    }
}

int ans_query(int node, int k) {
    //this is to answer the kth parent of any node in log(k)
    if (node == -1 || k == 0) {
        return node;
    }
    for (int i = 19; i >= 0; i--) {
        if (k >= (1 << i)) {
            return ans_query(up[node][i], k - (1 << i));
        }
    }
}

void dfs(int node, int par) {
    for (auto it : adj[node]) {
        if (it != par) {
            lvl[it] = lvl[node] + 1;
            dfs(it, node);
        }
    }
}

int lca(int u, int v) {
    if (lvl[u] < lvl[v]) {
        swap(u, v);
    }
    u = ans_query(u, lvl[u] - lvl[v]);
    if (u == v) {
        return u;
    }
    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return ans_query(u, 1);
}