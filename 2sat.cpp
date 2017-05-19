// 2sat.cpp
#include <vector>
#include <iostream>

#define rep(i,n) for(int i=0; i<(n); i++)
#define rrep(i,n) for(int i=(n)-1; i>=0; i--)

using namespace std;

typedef vector<int> vi;

// scc.cppのコピー
// 強連結成分分解 (Strongly Connected Component)
struct SCCGraph: public vector<vi> {

	vector<int> order;    // 属する強連結成分の番号(トポロジカル順序になっている) まだ調べてない頂点は-1
	vector<int> vs;       // 帰りがけ順

	using vector::vector;	// 継承コンストラクタ
	SCCGraph(const vector<vi> &v): vector::vector(v) {}	// コピーコンストラクタを使用可能にする

	// a -> b の辺を追加する。push_back()でも同じ
	void add_edge(int a, int b){
		(*this)[a].push_back(b);
	}

	// scc()で使う
	void dfs(int n, int k, vector<vi> &v, vector<vi> &rv){
		order[n] = k;
		for(auto t: v[n]){
			rv[t].push_back(n);	// 逆辺のグラフを作成
			if( order[t] < 0 ) dfs(t, k, v, rv);
		}
		vs.push_back(n);
	}

	// 強連結成分分解を行う return:強連結成分の数
	int scc(){
		int N = size(), k = 0;
		vector<vi> rG(N), tmp(N);   // 辺を逆にしたグラフ用
		vs.clear();
		order.assign(N, -1);
		rep(n,N) if( order[n] < 0 ) dfs(n, n, (*this), rG);
		order.assign(N, -1);
		rrep(i,vs.size()) if( order[ vs[i] ] < 0 ) dfs(vs[i], k++, rG, tmp);
		return k;
	}

	// 属する強連結成分が同じかどうか判定
	bool find(int x, int y){
		return order[x] == order[y];
	}

};
// 関数としてsccを使う。戻り値は、各ノードが所属する強連結成分の番号
vector<int> scc(const vector<vi> &v){
	SCCGraph g(v);
	g.scc();
	return g.order;
}


// 2-SAT
struct TwoSAT {
	SCCGraph graph;
	int N;
	vector<bool> val;	// 結果

	TwoSAT(int n): graph( (n+1)*2 ), val(n+1) {
		N = n;
	}

	void clear(){
		for(auto &&t: graph) t.clear();
	}

	// 辺( a -> b )を追加する。負の値は論理変数の否定(~a)を表す。
	// また、a の否定として a+N も使える。
	// a(>0) に対して、-a: 否定, a+N: 否定, -(a+N): 対偶=a
	void add_edge(int a, int b){
		if( a < 0 ) a = (3*N - a - 1) % (2*N) + 1;
		if( b < 0 ) b = (3*N - b - 1) % (2*N) + 1;
		graph.add_edge(a, b);
	}

	// 論理式( a V b ) を追加する。a,bは、論理変数の番号(0以外の整数)。否定は負の値で表す。
	void add_or(int a, int b){
		add_edge(-a, b);
		add_edge(-b, a);
	}

	// 判定を行う
	bool solve(){
		graph.scc();
		bool ret = true;
		for(int i=1; i <= N; i++){
			if( graph.order[i] == graph.order[N+i] ) ret = false;
			val[i] = (graph.order[i] > graph.order[N+i]);
		}
		return ret;
	}

	// 変数の値を取得する。
	bool value(int a){
		if( a < 0 ) return !val[-a];
		return val[a];
	}
};


// test
// yukicoder No.274 The Wall (http://yukicoder.me/problems/no/274)
int main(){
	int N, M;
	int L[2005], R[2005];
	int rL[2005], rR[2005];
	TwoSAT sat(2005);

	cin >> N >> M;
	rep(i,N){
		cin >> L[i] >> R[i];
		// 180度回転
		rR[i] = M - L[i] - 1;
		rL[i] = M - R[i] - 1;
	}
	auto fn = [&](int Li, int Lj, int Ri, int Rj, int a, int b){
		if( !(Rj < Li || Ri < Lj) ){
			// 重なる可能性があるものはadd
			sat.add_or( -a, -b );
		}
	};
	rep(i,N) rep(j,i){
		fn(  L[i],  L[j],  R[i],  R[j],  (i+1),  (j+1) );
		fn( rL[i],  L[j], rR[i],  R[j], -(i+1),  (j+1) );
		fn(  L[i], rL[j],  R[i], rR[j],  (i+1), -(j+1) );
		fn( rL[i], rL[j], rR[i], rR[j], -(i+1), -(j+1) );
	}

	cout << (sat.solve() ? "YES" : "NO") << endl;
	//rep(i,N) cout << sat.value(i+1) << endl;

	return 0;
}

