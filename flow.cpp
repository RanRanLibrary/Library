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

// 最大流を求める(Dinic法。bfs()をなくすとFord-Fulkerson法)
class Flow{
	public:
		int N;	// 頂点数
		vector<vc> F, C, edge;	// F:残余グラフ C:初期容量 edge:隣接する頂点
		vector<bool> bf;	// 調べ終わったかどうか
		vector<int> lv;	// Sからの距離

		// コンストラクタ n:頂点数
		Flow(int n): F(n,vc(n)), C(n,vc(n)), N(n), edge(n) {}

		// 辺を追加する
		void addEdge(int f, int t, int c){
			F[f][t] = C[f][t] = c;
			edge[f].push_back(t);
			edge[t].push_back(f);
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
		int flow(int n, int c, int T){
			if( n == T ) return c;
			bf[n] = true;
			for(int v: edge[n]) if( F[n][v] && !bf[v] && lv[v] > lv[n] ){	// 最後の条件をなくすとbfs()は要らなくなる
				int f = flow(v, min(c, F[n][v]), T);
				F[n][v] -= f;
				F[v][n] += f;
				if( f > 0 ) return f;
			}
			return 0;
		}

		// 最大流を求める
		int maxFlow(int S, int T){
			int ret = 0;
			while( bfs(S,T) )	// bfs()なしの場合は、この行はいらない
				for(int add; bf.assign(N,0), add = flow(0, INF, T);) ret += add;
			return ret;
		}

		// グラフを初期値に戻す
		void clear(){ rep(i,N) rep(j,N) F[i][j] = C[i][j]; }
};

int main(){
	int V, E;
	cin >> V >> E;
	Flow fl(V);
	rep(i, E){
		int u, v, c;
		cin >> u >> v >> c;
		fl.addEdge( u, v, c );
	}

	cout << fl.maxFlow(0, V-1) << endl;

	return 0;
}
