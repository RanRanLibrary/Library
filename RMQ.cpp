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
	T query(int l, int r, int i, int b, int t){
		if( l <= b && t <= r ){
			return seg[i];
		}else if( l < t && b < r ){
			T u = query(l,r, i*2,   b, (t+b)/2 );
			T v = query(l,r, i*2+1, (t+b)/2, t );
			return min(u, v);
		}
		return INF;
	}
public:
	vector<T> seg;	// セグメントツリー (親:i/2  子:i*2,i*2+1)
	int top=1;
	RMQ(int size){
		while( top < size ) top<<=1;
		seg.assign(top*2, INF);
	}
	void update(int pos, T val){
		for(int i=top+pos; i>0; i>>=1){
			seg[i] = val;
			val = min(seg[i], seg[i^1]);
		}
	}
	// [l,r)
	T query(int l, int r){
		if(l>r) swap(l,r);
		return query(l, r, 1, 0, top);
	}
	T get(int pos){		// =query(pos, pos+1)
		return seg[top+pos];
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
