#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long int ll;

const int INF = 1e9+9;

// 各ノードの情報
template <typename T, T INIT>
struct node {
	T v;
	node(){
		v = INIT;
	}
	// 葉ノードの更新
	void update(T _v){
		v = _v;
	}
	// ノードの更新
	void merge(T vl, T vr){
		v = min(vl, vr);
	}
	// ノードの値を取得
	T get(){
		return v;
	}
};

template <typename T, typename NODE=node<T,INF> >
class SegTree{
public:
	vector<NODE> data;
	int N;
	SegTree(int _N){
		// _N <= (N = 2^k) を見つける
		N = 1;
		while( N < _N ) N<<=1;
		data.resize(N*2+5);
	}

	// セグメントツリーの更新
	void update(int l, T v){
		if( l >= N ) return;
		int k = l + N;	// ノード番号
		data[k].update(v);
		updateNode( k/2 );
	}
	// 葉から根へ向かって更新
	void updateNode(int k){
		if( k <= 0 ) return;	// 終了条件
		data[k].merge( data[k*2].get(), data[k*2+1].get() );
		updateNode(k/2);	// 親へ
	}

	// 値を取得 [l,r)
	T get(int l, int r=-1, int a=0, int b=-1, int k=1){
		if( r == -1 ) r = l+1;
		if( b == -1 ) b = N;
		//cout << l << " " << r << " " << a << " " << b << " " << k << endl;
		NODE nd;
		// 完全に範囲内の場合
		if( l <= a && b <= r ) return data[k].get();
		// 完全に範囲外の場合
		if( r <= a || b <= l ) return nd.get();
		// 中途半端に含まれる場合
		int m = (a+b) / 2;
		T vl = get(l,r, a, m, k*2);
		T vr = get(l,r, m, b, k*2+1);
		nd.merge( vl, vr );
		return nd.get();
	}
};



// 確認

#include <algorithm>
#define rep(i,n) for(int i=0; i<(n); i++)
#define rrep(i,n) for(int i=(n)-1; i>=0; i--)
#define all(X) (X).begin(),(X).end()

typedef pair<int,int> pii;


// AOJ DSL_2_A
/*
const ll INF2 = ((ll)1<<31) - (ll)1;
SegTree<ll,node<ll,INF2> > sg(100005);
int main(){
	int n, q;
	cin >> n >> q;
	rep(i,q){
		int c, x, y;
		cin >> c >> x >> y;
		if( c == 0 ){
			sg.update(x, y);
		}else{
			y++;
			cout << sg.get(x, y) << endl;
		}
		//rep(j,18) cout << sg.data[j].get() << " "; cout << endl;
	}
	return 0;
}
*/


// arc026_C
SegTree<ll,node<ll,(ll)1e12> > sg(100005);
int main(){
	int N, L;
	int l[100005], r[100005], c[100005];
	vector<pii> v;

	cin >> N >> L;
	rep(i,N){
		cin >> l[i] >> r[i] >> c[i];
		v.emplace_back( r[i], i );
	}
	sort( all(v) );

	sg.update(0,0);
	for(auto p: v){
		int i = p.second;
		ll tmp = min( sg.get(r[i]), sg.get(l[i], r[i]) + (ll)c[i] );
		sg.update( r[i], tmp );
	}

	cout << sg.get(L) << endl;

	return 0;
}


