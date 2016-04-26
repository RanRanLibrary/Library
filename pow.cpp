#include<iostream>
#include<cstdio>

using namespace std;

typedef long long int ll;
const ll MOD = 1e9+7;

ll _pow(int n,int m){    //n^m
    if(m==0) return 1;
    ll tmp=_pow(n,m/2);
    return tmp*tmp*(m%2?n:1);
}

ll pow(int n,unsigned int m,int q=1e9+7){    //n^m%q
	if(m==0) return 1;
	ll tmp = pow(n,m/2,q);
	return ((tmp*tmp)%q)*(m%2?n:1)%q;
}

// n^m%MOD を求める。O( log(m) )
// mに負の数を指定すると逆元を求める
ll modpow(ll n, int m){
	ll ret=1;
	if( m < 0 ) m = MOD-1 + m;
	for(int i=1; i<=m; i<<=1){
		if( m&i ) ret = ret * n % MOD;
		n = n*n % MOD;
	}
	return ret;
}

int main(){
    ll n,m,q;
    while(scanf("%lld %lld %lld",&n,&m,&q)!=EOF){
        if(q){
            cout << pow(n,m,q) << endl;
        }else{
            cout << modpow(n,m) << endl;
        }
    }
   
    return 0;
}
