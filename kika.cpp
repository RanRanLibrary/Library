#include <cstdio>

//三角形は時計回りにセットする。辺上はTRUE(内部に判定)を返す。
bool checkTRIANGLE(int pos[3][2], int target[2]){
	int x[3] = { pos[1][0] - pos[0][0],
			pos[2][0] - pos[1][0],
			pos[0][0] - pos[2][0] };
	int y[3] = { pos[1][1] - pos[0][1],
			pos[2][1] - pos[1][1],
			pos[0][1] - pos[2][1] };
	int tx[3] = { target[0] - pos[0][0],
			target[0] - pos[1][0],
			target[0] - pos[2][0] };
	int ty[3] = { target[1] - pos[0][1],
			target[1] - pos[1][1],
			target[1] - pos[2][1] };
	
	for(int i=0; i<3; i++)
		if( x[i]*ty[i] - y[i]*tx[i] > 0 )
			return false;

	return true;
}


//動作確認
int main(){
	int pos[3][2], target[2];
	for(int i=0; i<3; i++)
		scanf("%d %d", pos[i], pos[i]+1);
	printf("ターゲット> ");
	scanf("%d %d", target, target+1);

	printf("結果：　%s\n", checkTRIANGLE(pos, target)?"TRUE":"FALSE");
	
	return 0;
}
