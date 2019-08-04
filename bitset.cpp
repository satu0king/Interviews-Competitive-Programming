#include <bits/stdc++.h>
using namespace std;

class BitSet;

class BitSetReference {
  friend class BitSet;
  BitSetReference() ;                               // no public constructor
  unsigned int *word; 
  int ind;
public:
  operator bool() const ;                     // convert to bool
  BitSetReference(BitSet* bitset, int n);
  BitSetReference& operator= (bool x) ;             // assign bool
  BitSetReference& operator= (const BitSetReference& x) ; // assign bit
};

class BitSet {
    friend class BitSetReference;
    vector<unsigned int> a;
    size_t w;
    int n;
    size_t _size;
public:
    BitSet(): n(0), w(sizeof(unsigned int)), _size(0) {}

    BitSet(int n, bool v = 0): n(n), w(sizeof(int)) {
        _size = n/w;
        if(n%w) _size++;
        a.resize(_size, v ? ~1 : 0);
    }

    void push(bool b) {
        n++;
        _size = n/w;
        if(n%w) _size++;
        if(_size!=a.size())
            a.resize(_size);
        (*this)[n-1] = b;
    }

    void pop() {
        if(!n)return;
        n--;
        _size = n/w;
        if(n%w) _size++;
        if(_size!=a.size())
            a.resize(_size);
    }

    BitSetReference back() {
        return (*this)[n-1];
    }

    size_t size() {
        return _size;
    }

    BitSetReference operator[] (int n) {
        return BitSetReference(this, n);
    }

};

BitSetReference::BitSetReference(BitSet* bitset, int n) {
    word = &(bitset->a[(n/bitset->w)]);
    ind = n%(bitset->w);
}

BitSetReference& BitSetReference::operator= (bool x) {

    if(x)
        *word |= (1<<ind);
    else
        *word &= ~(1<<ind);
    
    return *this;
}

BitSetReference& BitSetReference::operator= (const BitSetReference& x) {
    *this = bool(x);
    return *this;
}

BitSetReference::operator bool() const  {
    return (*word & (1<<ind)) != 0;
}



int main() {
    BitSet b1(10);
    cout<< b1[0]<<endl;
    b1[0] = 1;
    cout<< b1[0]<<endl;
    b1.push(b1[0]);
    cout<< b1[10]<<endl;
    cout<< b1.back()<<endl;
    b1.pop();
    cout<< b1.back()<<endl;
    
}