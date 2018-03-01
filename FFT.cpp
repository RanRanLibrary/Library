#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

#define rep(i,n) for(int i=0; i<(n); i++)

using namespace std;
typedef long long ll;


// complex<double> を使ったFFT
namespace FFT{
	typedef complex<double> Complex;

	// DFTを行う。 fのサイズは2^nであること。invは指定せずに使う。
	vector<Complex> fft(vector<Complex> f, double inv = 1){
		int n = f.size();
		if( n == 1 ) return f;

		vector<Complex> g[2];
		rep(i,n) g[i%2].push_back( f[i] );
		rep(i,2) g[i] = fft( g[i], inv );

		Complex z = polar( 1.0, inv * 2.0*M_PI/n );
		Complex cur = 1.0;
		rep(i,n){
			f[i] = g[0][i % (n/2)] + cur * g[1][i % (n/2)];
			cur *= z;
		}

		return f;
	}

	// DFTの逆変換
	vector<Complex> inv_fft(vector<Complex> f){
		auto ret = fft(f, -1);
		for(auto&& t: ret) t /= f.size();
		return ret;
	}
}


// 整数環FFT (FMT)
namespace MOD_FFT{
	typedef complex<double> Complex;

	//const ll MOD = 469762049;
	//const ll MOD = 167772161;
	const ll MOD = 1224736769;

	// 原始根
	const ll ROOT = 3;

	ll modpow(ll a, ll b){
		ll ret = 1;
		if( b < 0 ) b += MOD-1;
		for(; b > 0; a = (a*a)%MOD, b /= 2){
			if( b&1 ) ret = (ret*a) % MOD;
		}
		return ret;
	}

	// DFTを行う。 fのサイズは2^nであること。invは指定せずに使う。
	vector<ll> fft(vector<ll> f, ll inv = 1){
		ll n = f.size();
		if( n == 1 ) return f;

		vector<ll> g[2];
		rep(i,n) g[i%2].push_back( f[i] );
		rep(i,2) g[i] = fft( g[i], inv );

		ll z = modpow(ROOT, inv*(MOD-1)/n);
		ll cur = 1;
		rep(i,n){
			f[i] = (g[0][i % (n/2)] + cur * g[1][i % (n/2)]) % MOD;
			cur = (cur * z) % MOD;
		}

		return f;
	}

	// DFTの逆変換
	vector<ll> inv_fft(vector<ll> f){
		auto ret = fft(f, -1);
		for(auto&& t: ret) t = ( t * modpow(f.size(), MOD-2) ) % MOD;
		return ret;
	}

	// おまけ。MODの原始根を計算する(99で打ち切り)
	ll getROOT(ll MOD){
		ll ret = 2;
		for(bool f = true; f && ret < 100; ret++){
			f = false;
			ll sum = (ret*ret)%MOD;
			for(int i=2; i<MOD-1; i++, sum = (ret*sum)%MOD) if( sum == ret ){
				f = true;
				break;
			}
		}
		return ret-1;
	};
}


// 検証: atc001 C

using namespace FFT;
//using namespace MOD_FFT;
int main(){
	ios_base::sync_with_stdio(false);

	int N;
	const int n = (1<<18);
	vector<Complex> A(n), B(n), ret(n);
	//vector<ll> A(n), B(n), ret(n);

	cin >> N;
	rep(i,N) cin >> A[i+1] >> B[i+1];

	auto g = fft(A);
	auto h = fft(B);

	rep(i,n){
		ret[i] = g[i] * h[i];
		//ret[i] = (g[i] * h[i]) % MOD;
	}

	auto ans = inv_fft(ret);

	for(int i=1; i <= 2*N; i++){
		cout << (int)(ans[i].real() + 0.5) << endl;
		//cout << ans[i] << endl;
	}

	return 0;
}
