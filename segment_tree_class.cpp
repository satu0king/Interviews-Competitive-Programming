#include <bits/stdc++.h>
using namespace std;

// Range Max Query
struct SegmentTree {
  vector<int> tree;
  vector<int> lazy;
  int n;
  SegmentTree(int n) : n(n) {
    int size = 1;
    while (size <= n)
      size *= 2;
    size *= 2;
    tree.resize(size);
    lazy.resize(size);
  }

  int combine(int l, int r) { return max(l, r); }

  void pushDown(int id) {
    if (!lazy[id])
      return;
    lazy[2 * id] += lazy[id];
    lazy[2 * id + 1] += lazy[id];
    tree[2 * id] += lazy[id];
    tree[2 * id + 1] += lazy[id];
    lazy[id] = 0;
  }

  int get(int id, int tl, int tr, int l, int r) {
    if (l > r)
      return INT_MIN;
    if (tl == l && tr == r)
      return tree[id];
    pushDown(id);
    int treeMid = (tl + tr) / 2;
    int lValue = get(id * 2, tl, treeMid, l, min(treeMid, r));
    int rValue = get(id * 2, tr, treeMid, max(l, treeMid + 1), r);
    return combine(lValue, rValue);
  }

  int get(int l, int r) { return get(1, 0, n, l, r); }

  void update(int id, int tl, int tr, int l, int r, int value) {
    if (l > r)
      return;
    if (tl == l && tr == r) {
      tree[id] += value;
      lazy[id] += value;
      return;
    }
    pushDown(id);
    int treeMid = (tl + tr) / 2;
    update(id * 2, tl, treeMid, l, min(treeMid, r), value);
    update(id * 2, tr, treeMid, max(l, treeMid + 1), r, value);
  }

  void update(int l, int r, int value) { update(1, 0, n, l, r, value); }
  void update(int i, int value) { update(i, i, value); }
};