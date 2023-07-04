// https://leetcode.com/problems/falling-squares

struct segment_tree {
    vector<int> tree;
    vector<int> lazy;
    int n;

    segment_tree(int n) {
        int size = 1;
        while(size < n) {
            size *= 2;
        }
        n = size;
        tree.resize(2 * size);
        lazy.assign(size, -1);
        this->n = n;
    }

    // [x, y)
    int query(int x, int y) {
        return query(x, y, 1, 0, n);
    }

    // point update
    void update(int x, int val) {
        update(x, val, 1, 0, n);
    }

    // range update [x, y)
    void update(int x, int y, int val) {
        update(x, y, val, 1, 0, n);
    }

    private:
    // point update
    void update(int x, int val, int id, int l, int r) {
        if (l + 1 == r) {
            tree[id] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (x < mid) update(x, val, left(id), l, mid);
        else update(x, val, right(id), mid, r);

        tree[id] = combine(tree[left(id)], tree[right(id)]);
    }

    void update_lazy(int id, int val) {
        tree[id] = val;
        if (id < n)
            lazy[id] = val;
    }

    void update(int x, int y, int val, int id, int l, int r) {
        // fully exclusive
        if (y <= l || r <= x) return;
        
        // fully inclusive
        if (x <= l && r <= y) {
            update_lazy(id, val);
            return;
        }

        propagate(id);

        int m = (l + r) / 2;
        update(x, y, val, left(id), l, m);
        update(x, y, val, right(id), m, r);

        tree[id] = combine(tree[left(id)], tree[right(id)]);
    }

    void propagate(int id) {
        if (id < n && ~lazy[id]) {
            update_lazy(left(id), lazy[id]);
            update_lazy(right(id), lazy[id]);
            lazy[id] = -1;
        }
    }

    int left(int id) {
        return id * 2;
    }
    int right(int id) {
        return id * 2 + 1;
    }

    int query( int x, int y, int id, int l, int r) {
        if (x <= l && r <= y) return tree[id];
        if (y <= l || r <= x) return 0;

        propagate(id);

        int mid = (l + r) / 2;

        return combine(query(x, y, left(id), l, mid), query(x, y, right(id), mid, r));
    }

    int combine(int a, int b) {
        return max(a, b);
    }
};
