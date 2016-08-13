#include <iostream>
#include <vector>

using namespace std;

typedef long long int ll;
const ll MOD = 1e9+7;

// n^m%MOD を求める。O( log(m) )
ll modpow(ll n, int m){
	ll ret=1;
	for(int i=1; i<=m; i<<=1, (n*=n)%=MOD){
		if( m&i ) (ret *= n) %= MOD;
	}
	return ret;
}

// 逆元を求める
ll modinv(ll n){
	return modpow( n, MOD-2 );
}

// 階乗を求める。O(1)  準備O( n*log(n) )
// fact[n]     : nの階乗
// fact.inv[n] : nの階乗の逆元
class FACTORIAL{
public:
	vector<ll> fact, inv;
	FACTORIAL(int MAX_NUM): fact(MAX_NUM), inv(MAX_NUM) {
		fact[0] = inv[0] = 1;
		for(ll i=1; i<MAX_NUM; i++){
			fact[i] = (fact[i-1] * i) % MOD;
			inv[i] = modinv( fact[i] );
		}
	}
	const ll& operator [ ] ( const int i ) const {
		return fact[i];
	}
} fact(1000006); // nの最大値を指定


// 組み合わせ(Combinationを求める) O(1)
ll cmb(unsigned int n, unsigned int r){
	if( n < r ) return 0;
	return fact[n] * fact.inv[r] % MOD * fact.inv[n-r] % MOD;
}


// 実装が速い版 O(n^2) メモリ制限にも注意
/*
ll cmb_memo[10005][10005]={};
ll Cmb_(int n, int r){
	if( cmb_memo[n][r] ) return cmb_memo[n][r];
	if( r == 0 || r == n ) return 1;
	return cmb_memo[n][r] = (Cmb_(n-1,r) + Cmb_(n-1,r-1)) % MOD;
}
*/


int main(){
	// 検証 abc034_c
	int n, r;
	while( std::cin >> n >> r, n|r ){
		n--; r--;
		std::cout << cmb(n+r, r) << std::endl;
		return 0;
	}
	return 0;
}
