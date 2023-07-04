// https://leetcode.com/problems/falling-squares
struct segment_tree {
    segment_tree(long n) {
        int size = 1;
        while(size < n) {
            size *= 2;
        }
        this->n = size;
    }

    // [x, y)
    int rmq(long x, long y) {
        return rmq(x, y, 0, n);
    }

    // [x, y)
    void add(long x, long y, long val) {
        return add(x, y, val, 0, n);
    }

    private:

    unordered_map<long, int> tree;
    unordered_map<long, int> lazy;
    long n;

    int rmq(long x, long y, long l, long r, long id = 1) {
        if (!tree.count(id)) return 0;

        if (x >= r || y <= l) return 0; // fully out of range
        if (x <= l && r <= y) return tree[id]; // fully in range

        propagate(id);

        int m = (l + r) / 2;
        return combine(rmq(x, y, l, m, left(id)),  rmq(x, y, m, r, right(id)));
    }

    void add_lazy(long id, long val) {
        tree[id] += val;
        lazy[id] += val;
    }

    void propagate(long id) {
        long id_l = left(id);
        long id_r = right(id);
        if (tree.count(id) && !tree.count(id_l)) {
            // create child nodes and copy info forward
            tree[id_l] = tree[id];
            tree[id_r] = tree[id];
        }
        else if (lazy[id]) {
            add_lazy(id_l, lazy[id]);
            add_lazy(id_r, lazy[id]);
        }
        lazy[id] = 0;
    }

    void add(long x, long y, long val, long l, long r, long id = 1) {
        if (x >= r || y <= l) return; // fully out of range
        if (x <= l && r <= y) { // fully in range
         
            add_lazy(id, val);
            return; 
        }

        propagate(id);
        long m = (l + r) / 2;
        add(x, y, val, l, m, left(id));
        add(x, y, val, m, r, right(id));
        tree[id] = combine(tree[left(id)], tree[right(id)]);
    }

    long left(long id) {
        return 2 * id;
    }

    long right(long id) {
        return 2 * id + 1;
    }

    long combine(long a, long b) {
        return max(a, b);
    }
};
