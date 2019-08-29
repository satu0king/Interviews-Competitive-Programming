#include<bits/stdc++.h>
using namespace std;

class DSU {
    public:
    
    int n;
    int setCount;
    vector<int> size;
    vector<int> _parent;
    
    DSU(int n): n(n), setCount(n) {
        
        for(int i = 0; i < n; i++)
            _parent.push_back(i);
        
        size.resize(n, 1);
    }
    
    int parent(int i) {
        if(_parent[i] == i)return i;
        
        return _parent[i] = set(parent[i]);
    }
    
    void join(int i, int j) {
        
        int set1 = parent(i);
        int set2 = parent(j);
        if(set1 == set2) return;
        setCount--;
        
        if(size[set1] < size[set2])
            swap(set1, set2);
        
        size[set1] += size[set2];
        _parent[set2] = set1;
    }

    vector<set<int>> getSets() {

        vector<set<int>> results;
        map<int, set<int>> t;
        for(int i = 0; i < n; i++)
            t[parent(i)].insert(i);

        for (auto v: t)
            results.push_back(v.second);
        
        return results;
    }
};
