// ICPC 2016 domestic F
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

#define rep(i,n) for(int i=0; i<(n); i++)

#define X first;
#define Y second;

using namespace std;
typedef pair<int,int> pii;
typedef vector< vector<int> > vv;


// 根付き木のハッシュ値を計算する。
// tree[i] = {j1, j2, ..} :  頂点iの子は頂点j1,j2,..である
// n :  根のインデックス
map<vector<int>,int> hshs;
int treeHash(vv tree, int n = 0){
	vector<int> ht;
	for(auto t: tree[n]) ht.push_back( treeHash(tree, t) );
	sort( ht.begin(), ht.end() );
	return ( hshs.count(ht) ? hshs[ht] : hshs[ht]=hshs.size() );
}


int H, W;
char mp[105][105];

// makeTree 内包関係を表す木をつくる
vector<int> vxw{1,0,-1,0}, vyw{0,1,0,-1};
vector<int> vxb{1,0,-1,0, 1,1,-1,-1}, vyb{0,1,0,-1, 1,-1,1,-1};
int makeTree(vv &tree, int x, int y, char color){
	int curIndex = tree.size();
	tree.push_back( vector<int>() );
	stack<pii> st, next;
	st.push( pii(x,y) );
	while( !st.empty() ){
		int x = st.top().X;
		int y = st.top().Y;
		st.pop();
		if( mp[y][x] == 'x' ) continue;
		mp[y][x] = 'x';
		vector<int> vx = (color=='.' ? vxw : vxb);
		vector<int> vy = (color=='.' ? vyw : vyb);
		rep(k, vx.size()){
			int nx = x + vx[k];
			int ny = y + vy[k];
			if( nx < 0 || ny < 0 || nx > W+2 || ny > H+2 ) continue;
			if( mp[ny][nx] == 'x' ) continue;
			if( mp[ny][nx] == color ){
				st.push( pii(nx,ny) );
			}else{
				next.push( pii(nx,ny) );
			}
		}
	}
	while( !next.empty() ){
		int x = next.top().X;
		int y = next.top().Y;
		next.pop();
		if( mp[y][x] == 'x' ) continue;
		int id = makeTree( tree, x, y, (color=='.' ? '#' : '.') );
		tree[curIndex].push_back( id );
	}
	return curIndex;
}

int solve(){
	fill( (char*)mp, (char*)mp[105], '.' );
	cin >> H >> W;
	if( !(H|W) ) return -1;
	rep(y,H) rep(x,W) cin >> mp[y+1][x+1];
	vv tree;
	makeTree(tree, 0, 0, '.');
	for(auto &v: tree){
		cout << (&v-&tree[0]) << ": ";
		for(auto t: v) cout << t << " ";
		cout << endl;
	}
	return treeHash( tree, 0 );
}

int main(){
	while(1){
		int hash1 = solve();
		if( hash1 == -1 ) break;
		int hash2 = solve();
		cout << (hash1==hash2 ? "yes" : "no") << endl;
	}
	return 0;
}
