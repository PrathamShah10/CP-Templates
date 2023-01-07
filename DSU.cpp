class DSU {
private:
    vector<int>parent, size;
public:
    DSU(int n) {
        parent.push_back(0);
        size.push_back(0);
        for (int i = 1; i <= n; i++) {
            parent.push_back(i);
            size.push_back(1);
        }
    }
    int findpar(int n) {
        if (n == parent[n]) return n;
        return parent[n] = findpar(parent[n]);
    }
    void Union(int u, int v) {
        u = findpar(u);
        v = findpar(v);
        if (u == v) return;
        if (size[u] > size[v]) {
            parent[v] = parent[u];
            size[u] += size[v];
        }
        else {
            parent[u] = parent[v];
            size[v] += size[u];
        }
    }
};
