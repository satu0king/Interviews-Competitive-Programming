ll mult(ll a, ll b, ll mod)
{
    ll res = 0;
    a %= mod;
    while (b)
    {
        if (b & 1)
            res = (res + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return res;
}


    
int power(int x, int t){
    int ans = 1;
    while(t > 0) {
        if(t & 1) ans = 1LL * ans * x % MOD;
        x = 1LL * x * x % MOD;
        t >>= 1;
    }
    return ans;
}
inline int sub(int a, int b){
    a %= MOD;
    b %= MOD;
    a = ((a - b) % MOD + MOD) % MOD;
    return a;
}

inline int add(int a, int b){
    a %= MOD;
    b %= MOD;
    a = (a + b) % MOD;
    return a;
}

inline int mul(int a, int b){
    a %= MOD;
    b %= MOD;
    a = (a * b) % MOD;
    return a;
}

inline int inv(int a){
    a = a % MOD;
    a = power(a, MOD - 2);
    return a;
}
