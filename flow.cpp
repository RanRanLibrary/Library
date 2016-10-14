// AOJ GRL_6_A
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define rep(i,n) for(int i=0; i<(n); i++)

using namespace std;
typedef vector<int> vi;

const int INF = 0x3fffffff;

// template, remove_edge, limit_flow の実装がない
// 辺の容量を少なくする場合は、直接C[][]を操作してreset()を実行してください。

// 最大流を求める(Dinic法)
class Flow{
	public:
		int N;	// 頂点数
		vector<vi> F, C, edge;	// F:残余グラフ C:初期容量 edge:隣接する頂点

		vi itr, lv;	// itr:調べ終わったかどうか  lv:Sからの距離

		// コンストラクタ n:頂点数
		Flow(int n): N(n), F(n,vi(n)), C(n,vi(n)), edge(n) {}

		// f->tにコストcの辺を追加する(同じf->tに対して何度も追加することも可能)
		void addEdge(int f, int t, int c){
			F[f][t] = C[f][t] = c;
			edge[f].push_back(t);
			edge[t].push_back(f);
		}

		// sからの最短距離を求める。これを実行するとDFSでは最短経路の中から探索する
		int bfs(int S, int T){
			lv.assign(N, 0);
			queue<int> q;
			q.push(S);
			lv[S] = 1;
			while( !q.empty() ){
				int n = q.front(); q.pop();
				for(auto v: edge[n]) if( !lv[v] && F[n][v] ){
					lv[v] = lv[n] + 1;
					q.push(v);
				}
			}
			return lv[T];
		}

		// 増加パスをDFSで探す
		int dfs(int n, int c, int T){
			if( n == T ) return c;
			for(;itr[n] < edge[n].size(); ++itr[n]){
				int v = edge[n][itr[n]];
				if( F[n][v] && lv[v] > lv[n] ){
					int f = dfs(v, min(c, F[n][v]), T);
					F[n][v] -= f;
					F[v][n] += f;
					if(f) return f;
				}
			}
			return 0;
		}

		// 流す。最大流を求める(現在の状態からいくら流れたかが返ってくる)
		int maxFlow(int S, int T){
			if( S == T ) return INF;
			int ret = 0;
			while( bfs(S,T) ){
				itr.assign(N,0);
				for(int f; f=dfs(S, INF, T);) ret += f;
			}
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
		vector<vi> F, C, edge;	// F:残余グラフ C:初期容量 edge:隣接する頂点

		vi used;	// 調べ終わったかどうか

		// コンストラクタ n:頂点数
		Flow_min(int n): N(n), F(n,vi(n)), C(n,vi(n)), edge(n) {}

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
			used[n] = 1;
			for(int v: edge[n]) if( !f && F[n][v] && !used[v] ){
				f = dfs(v, min(c, F[n][v]), T);
				F[n][v] -= f;
				F[v][n] += f;
			}
			return f;
		}

		// 目一杯流す(S,Tは異なる点)
		void maxFlow(int S, int T){
			// if(S==T) return INF;
			while( used.assign(N,0), dfs(S, INF, T) ){}
			// return flow(T);
		}

		// 辺に流れている流量を取得する(オプション)
		int flow(int f, int t){ return C[f][t] - F[f][t]; }

		// 隣接する辺の流量の合計を取得する。n=S,T以外の場合は、出た値を1/2倍したものがその点の流量
		int flow(int n){
			int ret=0;
			for(int v: edge[n]) ret += abs( C[n][v] - F[n][v] );
			return ret;
		}

		// グラフを初期値に戻す(オプション)
		void reset(){ rep(i,N) rep(j,N) F[i][j] = C[i][j]; }
};

// 最小構成
/*
class Flow_min{
	public:
		int N;	// 頂点数
		vector<vi> F, C, e;	// F:残余グラフ C:初期容量 e:隣接する頂点
		vi b;	// 調べ終わったかどうか
		Flow_min(int n): N(n), F(n,vi(n)), C(n,vi(n)), e(n) {}
		void addEdge(int f, int t, int c){
			F[f][t] = C[f][t] = c;
			e[f].push_back(t);
			e[t].push_back(f);
		}
		int dfs(int n, int c, int T){
			int f = c * (n==T);
			b[n] = 1;
			for(int v: e[n]) if( !f && F[n][v] && !b[v] ){
				f = dfs(v, min(c, F[n][v]), T);
				F[n][v] -= f;
				F[v][n] += f;
			}
			return f;
		}
		void maxFlow(int S, int T){
			while( b.assign(N,0), dfs(S, INF, T) ){}
		}
		int flow(int n){
			int f=0;
			for(int v: e[n]) f += abs( C[n][v] - F[n][v] );
			return f;
		}
};
*/

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
