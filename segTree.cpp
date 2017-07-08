#include <iostream>
#include <vector>

using namespace std;
typedef long long int ll;

const int INF = 1e9;
//const ll INF = 1e17;

// 各ノードの情報
template <typename T>
struct node {
	T v, lazy;
	node(){
		v = INF;
		lazy = 0;
	}
	// ノードの値の更新
	void merge(T vl, T vr){
		v = min(vl, vr);
	}
	// ノードの値の更新(lazy適用)
	T add(int l, int r, T _v=0){
		T sum = lazy + _v;
		v += sum;
		lazy = 0;
		return sum;
	}
	// 遅延分の変更(加算)
	void addLazy(T v){
		lazy += v;
	}
};

template <typename T, typename NODE=node<T> >
class SegTree{
	// 遅延分の適応と伝播(現在のノードの値を確定させてLazyを伝搬させる)
	void propLazy(int a, int b, int k, T v=0){
		T lazy = data[k].add(a, b, v);
		if( k < N ){
			data[k*2+0].addLazy(lazy);
			data[k*2+1].addLazy(lazy);
		}
	}
	// セグメントツリーをたどる
	T prop(int l, int r, T v, int a, int b, int k=1){
		// 今いるノードの値を確定させる
		propLazy(a, b, k);
		// たどる
		NODE nd;	// 結果保存用(範囲外の場合は初期値が返る)
		if( l <= a && b <= r ){
			// 完全に範囲内の場合
			propLazy(a, b, k, v);
			return data[k].v;
		}else if( l < b && a < r ){
			// 中途半端に含まれる場合
			int m = (a+b) / 2;
			T vl = prop(l,r,v, a, m, k*2);
			T vr = prop(l,r,v, m, b, k*2+1);
			data[k].merge( data[k*2].v, data[k*2+1].v );
			nd.merge( vl, vr );
		}
		return nd.v;
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
	// セグメントツリーの更新(指定した場所の値をvに変更)
	void update(int l, T v){
		prop(l, l+1, v-get(l), 0, N);
	}
	// セグメントツリーの更新(範囲に加算)
	T add(int l, int r, T v){
		return prop(l,r,v,0,N);
	}
	// 値を取得 [l,r)
	T get(int l, int r){
		return prop(l,r,0,0,N);
	}
	// 値を取得 [l,l+1)
	T get(int l){
		return prop(l,l+1,0,0,N);
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
SegTree<ll,node<ll> > sg(100005);
int main(){
	rep(i,100005) sg.update(i,(1ll<<31)-1);
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
SegTree<ll,node<ll> > sg(100005);
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
SegTree<int,node<int> > sg(8);
int main(){
	rep(i,8) sg.update(i,0);
	int q, x, y, v;
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
