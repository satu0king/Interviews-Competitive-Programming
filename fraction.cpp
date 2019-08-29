#include<bits/stdc++.h>
using namespace std;

int _gcd(int a, int b) {
    if(b==0)return a;
    return _gcd(b, a%b);
}
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    return _gcd(a, b);
}

struct Fraction{
    int n;
    int d;
    Fraction(int _n, int _d): n(_n), d(_d) {
        if(d!=0) {
            int g = gcd(n, d);
            n/= g;
            d/= g;
        }
    }
    bool operator<(Fraction const &other) const {
        return n * other.d < other.n * d;
    }
    
    bool operator>(Fraction const &other) const {
        return other < *this;
    }

    bool operator==(Fraction const &other) const {
        return other.d == d && other.n == n;
    }

    Fraction add(Fraction other) {
        return Fraction(n * other.d + other.n * d, other.d * d);
    }

    Fraction subtract(Fraction other) {
        return Fraction(n * other.d - other.n * d, other.d * d);
    }

    Fraction multiply(Fraction other) {
        return Fraction(n * other.n , other.d * d);
    }

    Fraction divide(Fraction other) {
        return multiply(Fraction(other.d, other.n));
    }

    void print() {
        cout << n<< " / "<<d<<endl;
    }
};

int main() {
    Fraction f1(2,3);
    Fraction f2(3,4);
    Fraction f3(3,4);

    Fraction f4 = f3.add(f2);
    Fraction f5 = Fraction(0, 0);
    f4.print();
    f5.print();
    
}