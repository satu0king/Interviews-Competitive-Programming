struct bit{		// use 0 based indices!!!
	int n; vector<int> tree;
	bit(int n) : n(n) { tree.assign(n + 1, 0); }
	int query(int l, int r) { return query(r) - query(l - 1); }
	int query(int r) {
        int ans = 0;
        for(r++; r; r -= r&(-r)) ans+=tree[r];
        return ans;
	}
	void update(int i, int v) {
       for(i++; i <= n; i+= i&(-i)) tree[i]+=v;
	}
	void assign(int i, int v) {
       update(i, v - query(i, i));
	}
};
