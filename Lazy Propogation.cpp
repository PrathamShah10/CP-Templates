class lazySeg {
private:
    vector<int>seg, lazy;
public:
    lazySeg(int n) {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1, 0);
    }
    void build(int ind, int low, int high, vector<int>& arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
    int query(int ind, int low, int high, int l, int r) {
        // l r is given range for query
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];
            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
        //no overlap l r low high || low high l r
        if (low > r || l > high) {
            return 0;
        }
        //complete overlap l low high r
        if (low >= l && high <= r) {
            return seg[ind];
        }
        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }
    void update(int ind, int low, int high, int l, int r, int value) {
        // l r is given range for update
        //check if a lazy update is pending
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];
            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
        // l r is the given range for update
        // no overlap -> l r low high || low high l r
        if (low > r || l > high) {
            return;
        }
        //complete overlap -> l low high r
        if (low >= l && high <= r) {
            seg[ind] += (high - low + 1) * value;
            if (low != high) {
                lazy[2 * ind + 1] += value;
                lazy[2 * ind + 2] += value;
            }
            return;
        }
        //partial overlap
        int mid = (low + high) >> 1;
        update(2 * ind + 1, low, mid, l, r, value);
        update(2 * ind + 2, mid + 1, high, l, r, value);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};
