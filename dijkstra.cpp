#include <iostream>
#include <utility>
#include <queue>
#include <vector>

#define MAX_V 1000
#define INF 0x7FFFFFFF

using namespace std;

struct edge { int to, cost; };
typedef pair<int, int> P;

int V;
vector <edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s) {
  priority_queue <P, vector<P>, greater<P> > que;
	fill(d, d + V, INF);
	d[s] = 0;
	que.push( P(0, s) );
	
	while( !que.empty() ) {
		P p = que.top(); que.pop();
		int v = p.second;
		if(d[v] < p.first) continue;

		for(int i = 0; i < G[v].size(); i++) {
			edge e = G[v][i];
			if(d[e.to] > d[v] + e.cost) {
				d[e.to] = d[v] + e.cost;
				que.push( P(d[e.to], e.to) );
			}
		}
	}
}

int main(void) {
	dijkstra(0);
	
	return 0;
}


// 構造体を使う場合
struct ST{
	int d, i, x, y;
	// priority_queue用  constを忘れずに
	bool operator< (const ST& a) const {
		return (d > a.d);
	}
};

