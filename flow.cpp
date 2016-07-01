// AOJ GRL_6_A
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define rep(i,n) for(int i=0; i<(n); i++)

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vc;

const int INF = 0x3fffffff;

// 最大流を求める(Dinic法)
class Flow{
	public:
		int N;	// 頂点数
		vector<vc> F, C, edge;	// F:残余グラフ C:初期容量 edge:隣接する頂点
		vector<bool> bf;	// 調べ終わったかどうか
		vector<int> lv;	// Sからの距離

		// コンストラクタ n:頂点数
		Flow(int n): N(n), F(n,vc(n)), C(n,vc(n)), edge(n) {}

		// f->tにコストcの辺を追加する(同じf->tに対して何度も追加することも可能)
		void addEdge(int f, int t, int c){
			addCap(f, t, c);
			edge[f].push_back(t);
			edge[t].push_back(f);
		}

		// f->tの辺の容量をc増やす(cは非負)
		void addCap(int f, int t, int c){
			F[f][t] += c;
			C[f][t] += c;
		}

		// 同じf->tペアに対してaddEdge()をたくさん実行した後に実行するとよい
		void uniqueEdge(){
			for(auto e: edge){
				sort( e.begin(), e.end() );
				e.erase( unique( e.begin(), e.end() ), e.end() );
			}
		}

		// sからの最短距離を求める。これを実行するとDFSでは最短経路の中から探索する
		int bfs(int S, int T){
			lv.assign(N, 0);
			queue<int> que;
			que.push(S);
			lv[S] = 1;
			while( !que.empty() ){
				int n = que.front(); que.pop();
				for(auto v: edge[n]) if( !lv[v] && F[n][v] ){
					lv[v] = lv[n] + 1;
					que.push(v);
				}
			}
			return lv[T];
		}

		// 増加パスをDFSで探す
		int dfs(int n, int c, int T){
			if( n == T ) return c;
			bf[n] = true;
			for(int v: edge[n]) if( F[n][v] && !bf[v] && lv[v] > lv[n] ){
				int f = dfs(v, min(c, F[n][v]), T);
				F[n][v] -= f;
				F[v][n] += f;
				if( f ) return f;
			}
			return 0;
		}

		// 最大流を求める
		int maxFlow(int S, int T){
			if( S == T ) return INF;
			int ret = 0;
			while( bfs(S,T) ) for(int add; bf.assign(N,0), add = dfs(S, INF, T);) ret += add;
			return ret;
		}

		// 辺に流れている流量を取得する
		int flow(int f, int t){ return C[f][t] - F[f][t]; }

		// 隣接する辺の流量の合計を取得する。n=S,T以外の場合は、出た値を1/2倍したものがその点の流量
		int flow(int n){
			int ret=0;
			for(int v: edge[n]) ret += abs( flow(n,v) );
			return ret;
		}

		// グラフを初期値に戻す
		void reset(){ rep(i,N) rep(j,N) F[i][j] = C[i][j]; }
};

// 実装の短いフロー(Ford-Fulkerson法)
class Flow_min{
	public:
		int N;	// 頂点数
		vector<vc> F, C, edge;	// F:残余グラフ C:初期容量 edge:隣接する頂点
		vc bf;	// 調べ終わったかどうか

		// コンストラクタ n:頂点数
		Flow_min(int n): N(n), F(n,vc(n)), C(n,vc(n)), edge(n) {}

		// f->tにコストcの辺を追加する(同じf->tに対して何度も追加することは不可)
		void addEdge(int f, int t, int c){
			F[f][t] = C[f][t] = c;
			edge[f].push_back(t);
			edge[t].push_back(f);
		}

		// f->tの辺の容量をc増やす(オプション)
		void addCap(int f, int t, int c){
			F[f][t] += c;
			C[f][t] += c;
		}

		// 増加パスをDFSで探す
		int dfs(int n, int c, int T){
			int f = c * (n==T);
			bf[n] = 1;
			for(int v: edge[n]) if( !f && F[n][v] && !bf[v] ){
				f = dfs(v, min(c, F[n][v]), T);
				F[n][v] -= f;
				F[v][n] += f;
			}
			return f;
		}

		// 目一杯流す(S,Tは異なる点)
		void maxFlow(int S, int T){
			while( bf.assign(N,0), dfs(S, INF, T) ){}
		}

		// 辺に流れている流量を取得する(オプション)
		int flow(int f, int t){ return C[f][t] - F[f][t]; }

		// 隣接する辺の流量の合計を取得する。n=S,T以外の場合は、出た値を1/2倍したものがその点の流量
		int flow(int n){
			int ret=0;
			for(int v: edge[n]) ret += abs( C[n][v] - F[n][v] );
			return ret;
		}

		// グラフを初期値に戻す
		void reset(){ rep(i,N) rep(j,N) F[i][j] = C[i][j]; }
};

int main(){
	int V, E;
	cin >> V >> E;

	Flow fl(V);
//	Flow_min fm(V);
	rep(i, E){
		int u, v, c;
		cin >> u >> v >> c;
		fl.addEdge( u, v, c );
//		fm.addEdge( u, v, c );
	}

	cout << fl.maxFlow(0, V-1) << endl;
//	fm.maxFlow(0, V-1);
//	cout << fm.flow(0) << endl;

	return 0;
}
