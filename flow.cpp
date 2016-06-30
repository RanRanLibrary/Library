// AOJ GRL_6_A
#include <iostream>
#include <vector>
#include <algorithm>

#define rep(i,n) for(int i=0; i<(n); i++)

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vc;

const int INF = 0x3fffffff;

// 最大流を求める(Ford-Fulkerson)
class Flow{
	public:
		int N;
		vector<vc> F, C, edge;	// F:残余グラフ C:初期容量

		// コンストラクタ n:頂点数
		Flow(int n): F(n,vc(n)), C(n,vc(n)), N(n), edge(n) {}

		// 辺を追加する
		void addEdge(int f, int t, int c){
			F[f][t] = C[f][t] = c;
			edge[f].push_back(t);
			edge[t].push_back(f);
		}

		// 増加パスをDFSで探す
		int flow(int n, int c, int T, vector<bool> &bf){
			if( n == T ) return c;
			bf[n] = true;
			for(int i: edge[n]) if( F[n][i] > 0 && !bf[i] ){
				int f = flow(i, min(c, F[n][i]), T, bf);
				F[n][i] -= f;
				F[i][n] += f;
				if( f > 0 ) return f;
			}
			return 0;
		}
		// 最大流を求める
		int maxFlow(int S, int T){
			int ret = 0;
			vector<bool> bf(N);
			for(int add; add = flow(0, INF, T, bf); bf.assign(N,0)) ret += add;
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
