#include <vector>
#include <map>

// Spaghetti Source のUnionFind(まんま)
// http://www.prefield.com/algorithm/container/union_find.html


// UnionFind木
// unite()で2つの集合を1つに統合する
// find()で2つの集合が同じ集合かどうかわかる
// root()で集合の識別番号(その集合のルートの番号)を求められる
struct UnionFind{

	std::vector<int> data;
	// dataの各要素について
	// 負の値:その集合のルートであること示す(spaghetti sourceではその絶対値は集合の要素数となっている)
	// 正の値:親ノードの番号(dataのインデックス)。root()を呼び出すたびに集合のルートを指すように書きなおされるので木はそんなに深くならない

	//初期化 size:最大要素数
	UnionFind(int size): data(size, -1){ }
	
	// 集合を併合する
	// すでに同じ集合だった場合は、falseが返る
	bool unite(int x, int y){
		x=root(x); y=root(y);
		if( x != y ){
			// yの属する集合のルートをxに変更
			data[y] = x;
		}
		return x!=y;
	}

	// 同じ集合かどうか判定
	bool find(int x, int y){
		return root(x) == root(y);
	}

	// 集合の識別番号を返す
	int root(int x){
		// 負の値を持つものがその集合のルート
		// 正の値は同じ集合に属するものを指す(辿ればいずれルートへ着く)
		return (data[x] < 0)? x : data[x]=root(data[x]);
	}
	
};

// 連番でない数字やint以外を扱う
// 次の一文を有効にすると2倍速になるがmake()を呼ぶのが必須となる
// #define get_index(a) data[(a)]
template < typename T >
struct UnionFindMap{
	std::map<T, int> data;
	UnionFind uf;

	// 初期化 size:最大要素数
	UnionFindMap(int size): uf(size){ }
	
#ifndef get_index
	// 要素識別番号
	int get_index(T x){
		// map内に無かったら追加
		if( data.find(x) == data.end() ){
			data.insert( std::make_pair<T, int>( x, data.size() ) );
		}
		return data[x];
	}
#endif

	// 集合を作る
	// べつにこの関数は呼ばなくても良い
	int make(T x){
		// map内に無かったら追加
		if( data.find(x) == data.end() ){
			data.insert( std::make_pair<T, int>( x, data.size() ) );
		}
		return data[x];
	}
	
	// 集合を併合する
	bool unite(T x, T y){
		return uf.unite( get_index(x), get_index(y) );
	}

	// 同じ集合かどうか判定
	bool find(T x, T y){
		return uf.find( get_index(x), get_index(y) );
	}

	// 集合識別番号を返す
	int root(T x){
		return uf.root( get_index(x) );
	}

};



//テスト

#include <cstdio>

using namespace std;

int maxuf=10;

int main(){
	char n, m;
	char a;
	
	UnionFindMap<char> uf(maxuf);

	printf("%d個の文字を入力\n", maxuf);
	for(int i=0; i<10; i++){
		scanf(" %c", &a);
		uf.make(a);
	}
	
	printf("合わせる2つの集合を指定\n");
	while( scanf(" %c %c", &n, &m), n||m ){
		printf("%c , %c \n", n, m);
		printf("find: %d\n", uf.find(n, m) );
		uf.unite(n, m);
		for(map<char,int>::iterator it=uf.data.begin(); it!=uf.data.end(); it++)
			printf("%2c ", (*it).first);
		printf("\n");
		for(map<char,int>::iterator it=uf.data.begin(); it!=uf.data.end(); it++)
			printf("%2d ", (*it).second);
		printf("\n");
		for(map<char,int>::iterator it=uf.data.begin(); it!=uf.data.end(); it++)
			printf("%2d ", uf.uf.data[(*it).second] );
		printf("\n");
	}

	return 0;
}
