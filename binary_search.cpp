#include <cstdio>
#include <algorithm>	//sortに必要だった

//cは配列の先頭アドレス、nは配列の個数(end-bigin)
//cは昇順にソートされていること。
//戻り値はkより大きいギリギリか同じ値のインデックス。
//kが配列の範囲内にない場合は、上方はみ出し=n 下方はみ出し=-1 を返す。
template < typename T >
int bsearch( T *c, int n , T k){
	int l = 0, r = n, p;
	
	//下方はみ出し判定
	if( *c > k ) return -1;	//下方はみだし判定とかいらん気がしてきた。
	
	while( r-l > 0 ){
		p = (l + r) / 2;
		if( *(c+p) < k ) l = p + 1;
		else r = p;
	}
	
	return r;
}


int main(){
	int n, k;
	
	printf("配列の個数：");
	scanf("%d", &n);
	
	int c[n];
	for(int i=0; i < n; i++)
		scanf("%d", c + i);
	
	printf("調べる値：");
	scanf("%d", &k);
	
	std::sort( c, c+n );
	
	int result = bsearch(c, n, k);
	printf("結果： %d\n", result );
	for(int i=0; i<n; i++){
		printf("%d", c[i]);
		if( i == result )
			printf("   <--");
		printf("\n");
	}
	
	return 0;
}
