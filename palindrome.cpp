
typedef long long int ll;


struct RollingHash{
	vector<ll> pwr, hsh;
	ll A, M;
	int n;

    RollingHash(){}
    
	RollingHash(string s, ll _A = 31, ll _M = 1e9 + 7){
		n = s.size();
		pwr.resize(n+1); hsh.resize(n+1);

		A = _A, M = _M;

		pwr[0] = 1;
		for(int i = 1; i <= n; i++) pwr[i] = pwr[i-1] * A % M;

		hsh[0] = s[0] % M + 1;
		for(int i = 1; i < n; i++){
			hsh[i] = (hsh[i - 1] * A % M) + s[i] + 1; if(hsh[i] >= M) hsh[i] -= M;
		}
	}

	ll getHash(int x, int y){
		assert(x >= 0 and x < n and y >= 0 and y <= n);
		return (hsh[y] + M - ((x-1 >= 0)? hsh[x-1] * pwr[y-x+1] % M : 0)) % M;
	}
};

struct PalindromeChecker {
	RollingHash hash;
	RollingHash revHash;
    int n;

	PalindromeChecker(string s): hash(s), n(s.size()) {
        reverse(s.begin(), s.end());
        revHash = RollingHash(s);
    }

    bool isPalindrome(int i, int j) {
        return hash.getHash(i, j) == revHash.getHash(n-j-1, n-i-1);
    }

};
