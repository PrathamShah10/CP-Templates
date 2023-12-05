// this is 0-indexed seg tree
class segtree {
    vector<int>seg;
public:
    segtree(int n) {
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, vector<int>& arr) {
        // use: build(0, 0, n - 1, arr); for building
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
        // [l r] is given range
        // ind = 0, low = 0, high = n - 1
        // no overlap
        // [low high] [l r] or  [l r] [low high]
        if (l > high || low > r) {
            return 0;
        }
        // complete overlap
        // here the seg range is completely inside [l r]
        // [l low high r]
        else if (low >= l && high <= r) {
            return seg[ind];
        }
        // partial overlap
        else {
            int mid = (low + high) >> 1;
            int left = query(2 * ind + 1, low, mid, l, r);
            int right = query(2 * ind + 2, mid + 1, high, l, r);
            return left + right;
        }
    }
    void update(int ind, int low, int high, int updateIndex, int updateValue) {
        // ind -> segment tree's index
        // ind = 0, low = 0, high = n - 1
        int mid = (low + high) >> 1;
        if (low == high) {
            seg[ind] = updateValue;
            return;
        }
        else if (updateIndex > mid) {
            update(2 * ind + 2, mid + 1, high, updateIndex, updateValue);
        }
        else {
            update(2 * ind + 1, low, mid, updateIndex, updateValue);
        }
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};

