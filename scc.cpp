#include <vector>

using namespace std;

typedef vector<int> vi;

// 強連結成分分解 (Strongly Connected Component)
// プログラミングコンテストチャレンジブック など参照
struct SCCGraph: public vector<vi> {

	vector<int> order;    // 属する強連結成分の番号(トポロジカル順序になっている)
	vector<int> vs;   // 帰りがけ順
	vector<bool> used;    // すでに調べたか

	using vector::vector;	// 継承コンストラクタ
	SCCGraph(const vector<vi> &v): vector::vector(v) {}	// コピーコンストラクタを使用可能にする

	// a -> b の辺を追加する。push_back()でも同じ
	void add_edge(int a, int b){
		(*this)[a].push_back(b);
	}

	// scc()で使う
	void dfs(int n, int k, vector<vi> &v, vector<vi> &rv){
		used[n] = true;
		order[n] = k;
		for(auto t: v[n]){
			if( !rv.empty() ) rv[t].push_back(n);	// 逆辺のグラフを作成
			if( !used[t] ) dfs(t, k, v, rv);
		}
		vs.push_back(n);
	}

	// 強連結成分分解を行う
	int scc(){
		int N = size();
		used.assign(N, false);
		order.resize(N);
		vs.clear();
		vector<vi> rG(N), tmp;   // 辺を逆にしたグラフ用
		for(int n=0; n < N; n++){
			if( !used[n] ) dfs(n, n, (*this), rG);
		}
		used.assign(N, false);
		int k = 0;		// 強連結成分の番号
		for(int i = vs.size()-1; i >= 0; i--){
			if( !used[ vs[i] ] ) dfs(vs[i], k++, rG, tmp);
		}
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



// test
// AOJ GRL_3_C (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=jp)
#include <iostream>
#define rep(i,n) for(int i=0; i<(n); i++)
int main(){
	int V, E;
	SCCGraph graph(10005);

	cin >> V >> E;
	rep(i,E){
		int s, t;
		cin >> s >> t;
		graph.add_edge( s, t );
	}

	graph.scc();
	//rep(i,V) cout << "graph: " << i << " " << graph.order[i] << endl;

	int Q;
	cin >> Q;
	rep(i,Q){
		int u, v;
		cin >> u >> v;
		cout << (int)graph.find(u, v) << endl;
	}

	return 0;
}

// scc()関数を使用する方法
/*
int main(){
	int V, E;
	vector<vi> edge(10005);

	cin >> V >> E;
	rep(i,E){
		int s, t;
		cin >> s >> t;
		edge[s].push_back( t );
	}

	auto g = scc(edge);

	int Q;
	cin >> Q;
	rep(i,Q){
		int u, v;
		cin >> u >> v;
		cout << (int)(g[u] == g[v]) << endl;
	}

	return 0;
}
*/
