// RangeIF

//配列のある範囲すべてでifで条件判定する。
//i : 変数(a~(b-1)まで動く)
//a, b : iを動かす範囲
//c : 判定式(式中にiを用いる)
//e : 実行するコード
//RIFを使う場合は、iはすでに宣言されている必要がある。そしてマクロを展開すると2文になる点に注意する必要がある。
//RIFEの方が楽だが、IFのようにRIFE(){...}とは書けない。
#define RIF(i, a, b, c) for(i=(a);i<(b);i++)if(c)break;if(i!=(b))
#define RIFE(i, a, b, c, e) {int i=(a);for(;i<(b);i++)if(c)break;if(i<(b)){e;}}


int main(){
	int N = 10, lim = 1000;
	int v[100][N];
	
	for(int k=0; k<100; k++){
		
		// RIFの場合
		int f;
		RIF(f, 0, N, lim < v[k][f]){ 
			continue;
		}

		// RIFEの場合
		RIFE(i, 0, N, lim < v[k][i], continue);

		//何か処理をする。
	}
	return 0;
}


