// ARC026 C問題
// この問題は、値の更新は小さくなる更新しかしない。大きくなる更新は未確認(おそらくできる)。

#include <iostream>
#include <set>
#include <tuple>
#include <vector>
#include <algorithm>

#define rep(i,n) for(int i=0; i<(n); i++)
#define rrep(i,n) for(int i=(n)-1; i>=0; i--)

using namespace std;

typedef long long int ll;

const ll INF=10e12;

template <typename T>
class RMQ {
	T query(int l, int r, int a, int b, int k){
		if( l <= a && b <= r ){
			return seg[k];
		}else if( l < b && a < r ){
			int m = (b+a)/2;
			T vl = query(l,r, a, m, k*2);
			T vr = query(l,r, m, b, k*2+1);
			return min(vl, vr);	// merge
		}
		return INF;	// default value
	}
public:
	vector<T> seg;	// セグメントツリー (親:k/2  子:k*2,k*2+1)
	int N;
	RMQ(int size){
		N = 1;
		while( N < size ) N<<=1;
		seg.assign(N*2, INF);		// default value
	}
	void update(int pos, T v){
		for(int k=N+pos; k>0; k/=2){
			seg[k] = v;
			v = min(seg[k], seg[k^1]);	// merge
		}
	}
	// [l,r)
	T query(int l, int r){
		if(l>r) swap(l,r);
		return query(l, r, 0, N, 1);
	}
	T get(int pos){		// =query(pos, pos+1)
		return seg[N+pos];
	}
};

typedef tuple<int,int,int> TP;
int main(){
	int N, L;
	vector<TP> st;

	cin >> N >> L;
	L++;
	rep(i,N){
		int l, r, c;
		cin>>l>>r>>c;
		st.push_back( TP(l,r,c) );
	}
	sort(st.begin(), st.end());

	RMQ<ll> rmq(L);

	rmq.update(0, 0);

	for(auto t: st){
		int l = get<0>(t);
		int r = get<1>(t);
		int c = get<2>(t);
		ll nex = rmq.query(l, r+1) + c;
		nex = min(nex, rmq.get(r));
		rmq.update(r, nex);
	}

	cout << rmq.get(L-1) << endl;

	return 0;
}
