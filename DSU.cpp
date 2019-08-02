

class DSU {
    public:
    
    int n;
    int setCount;
    vector<int> size;
    vector<int> parent;
    
    DSU(int n): n(n), setCount(n) {
        
        for(int i = 0; i < n; i++)
            parent.push_back(i);
        
        size.resize(n, 1);
    }
    
    int set(int i) {
        if(parent[i] == i)return i;
        
        return parent[i] = set(parent[i]);
    }
    
    void join(int i, int j) {
        
        int set1 = set(i);
        int set2 = set(j);
        if(set1 == set2) return;
        setCount--;
        
        if(size[set1] < size[set2])
            swap(set1, set2);
        
        size[set1] += size[set2];
        parent[set2] = set1;
    }
};
