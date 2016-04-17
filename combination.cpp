#include <iostream>
#include <algorithm>

using namespace std;

typedef long long int ll;
const ll MOD = 1e9+7;

// n < 20000, r < 20000 の範囲まで
ll memo[20005][20005]={};

ll Cmb_(ll n, ll r){
	if( memo[n][r] ) return memo[n][r];
	if( r == 0 || r == n ) return 1;
	return memo[n][r] = (Cmb_(n-1,r) + Cmb_(n-1,r-1)) % MOD;
}

ll Cmb_2(int n, int r){
	if( memo[n][r] ) return memo[n][r];
	memo[0][0] = 1;
	for(int i=0; i<n; i++){
		for(int j=0; j<=i; j++){
			(memo[i+1][j]   += memo[i][j]) %= MOD;
			(memo[i+1][j+1] += memo[i][j]) %= MOD;
		}
	}
	return memo[n][r];
}

// 最速(1桁くらいしか速くならないけど)
ll Cmb(int n, int r){
	if( 2 * r > n ) r = n-r;
	if( memo[n][r] ) return memo[n][n-r] = memo[n][r];
	if( r == 0 || r == n ) return 1;
	int nx = (n+1)/2;
	ll sum=0, tmp;
	for(int i = 0; i <= min(nx,r); i++){
		tmp  = memo[n-nx][i] ? memo[n-nx][i] : Cmb(n-nx, i);
		tmp *= memo[nx][r-i] ? memo[nx][r-i] : Cmb(nx, r-i);
		sum += tmp % MOD;
		sum %= MOD;
	}
	return memo[n][r] = sum;
}

int main(){
	int n=20000, r=10000;
	while( std::cin >> n >> r, n|r ){
		fill(memo[0], memo[20005], 0);
		std::cout << "Cmb_ \t" << Cmb_(n,r) << std::endl;
		fill(memo[0], memo[20005], 0);
		std::cout << "Cmb_2\t" << Cmb_2(n,r) << std::endl;
		fill(memo[0], memo[20005], 0);
		std::cout << "Cmb  \t" << Cmb(n,r) << std::endl;
	}
	return 0;
}
