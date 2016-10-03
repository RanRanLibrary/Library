#include <iostream>
#include <vector>

using namespace std;
typedef long long int ll;

const int INF = 1e9+9;

// 各ノードの情報
template <typename T, T INIT>
struct node {
	T v, lazy;
	node(){
		v = INIT;
		lazy = 0;
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
	// ノードの更新(lazy適用)
	T add(int l, int r, T _v=0){
		T sum = lazy + _v;
		v += sum;
		lazy = 0;
		return sum;
	}
	// ノードに遅延分をセット
	void addLazy(T v){
		lazy += v;
	}
};

template <typename T, typename NODE=node<T,INF> >
class SegTree{
	// 遅延分の適応と伝播
	void propLazy(int a, int b, int k, T v=0){
		T lazy = data[k].add(a, b, v);
		if( k < N ){
			data[k*2+0].addLazy(lazy);
			data[k*2+1].addLazy(lazy);
		}
	}
	// セグメントツリーをたどる
	T prop(int l, int r, T v, int a, int b, int k=1){
		// 伝播
		propLazy(a, b, k);
		// たどる
		NODE nd;	// 結果保存用(範囲外の場合は初期値が返る)
		if( l <= a && b <= r ){
			// 完全に範囲内の場合
			propLazy(a, b, k, v);
			return data[k].get();
		}else if( l < b && a < r ){
			// 中途半端に含まれる場合
			int m = (a+b) / 2;
			T vl = prop(l,r,v, a, m, k*2);
			T vr = prop(l,r,v, m, b, k*2+1);
			data[k].merge( data[k*2].get(), data[k*2+1].get() );
			nd.merge( vl, vr );
		}
		return nd.get();
	}

public:
	vector<NODE> data;
	int N;
	SegTree(int _N){
		// _N <= (N = 2^k) を満たすNを見つける
		N = 1;
		while( N < _N ) N<<=1;
		data.resize(N*2);
	}
	// セグメントツリーの更新
	void update(int l, T v){
		prop(l, l+1, v-get(l), 0, N);
	}
	// セグメントツリーの更新(範囲に加算)
	T add(int l, int r, T v){
		return prop(l,r,v,0,N);
	}
	// 値を取得 [l,r)
	T get(int l, int r=-1){
		if( r == -1 ) r = l+1;
		return prop(l,r,0,0,N);
	}
};



// 確認

#include <algorithm>
#include <set>
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
/*
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
*/


// 手動で確認
/*
SegTree<int,node<int,99> > sg(8);
int main(){
	int q, x, y, v;
	sg.add(0,8,-99);
	while(cin>>q>>x>>y){
		if( q == 0 ){
			cin >> v;
			sg.add(x,y,v);
		}else{
			cout << "get : " << sg.get(x,y) << endl;
		}
		// セグツリーの状態を表示
		rep(i,sg.data.size()){
			if( __builtin_popcount(i) == 1 ) cout << endl;
			cout << sg.data[i].v << "(" << sg.data[i].lazy << ")\t";
		}
		cout << endl;
	}
}
*/


// ICPC 2014 Tokyo Regional G
/*
SegTree<int> sg(300005);
int N, Q;
string s;
int q[200005];
set<int> op, cl;
void flip(int i){
	if(s[i] == '('){
		s[i] = ')';
		cl.insert( i );
		if(op.find(i) != op.end() ) op.erase( op.find(i) );
		sg.add(i+1, N+2, -2);
	}else{
		s[i] = '(';
		op.insert( i );
		if(cl.find(i) != cl.end() ) cl.erase( cl.find(i) );
		sg.add(i+1, N+2, 2);
	}
}
int main(){
	cin >> N >> Q >> s;
	rep(i,Q){
		cin >> q[i];
		q[i]--;
	}

	int sum = 0;
	rep(i,N+1){
		sg.update(i, sum);
		if( s[i] == ')' ){
			cl.insert(i);
			sum--;
		}else{
			op.insert(i);
			sum++;
		}
	}

	rep(i,Q){
		int ans;
		flip(q[i]);
		if( s[q[i]] == ')' ){
			ans = *cl.begin();
		}else{
			int l=1, r=N+2;
			while( r-l > 1 ){
				int m = (l+r) / 2;
				sg.add(m, N+2, -2);
				if( sg.get(m, N+2) >= 0 ){
					r = m;
				}else{
					l = m;
				}
				sg.add(m, N+2, 2);
			}
			ans = *op.upper_bound( l-1 );
		}
		flip(ans);
		cout << (ans+1) << endl;
	}

	return 0;
}
*/
