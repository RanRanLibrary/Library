#include <cstdio>

//三角形はどんな順でもOK。辺上はFALSEを返す。(三角形が成り立ってないときにミスるの防止)
bool checkTRIANGLE(int pos[3][2], int target[2]){
	
	for(int i=0; i<3; i++){
		int x = pos[(i+1)%3][0] - pos[i][0],
			y = pos[(i+1)%3][1] - pos[i][1],
			ox = pos[(i+2)%3][0] - pos[i][0],
			oy = pos[(i+2)%3][1] - pos[i][1],
			tx = target[0] - pos[i][0],
			ty = target[1] - pos[i][1];
		if( (x*ty - y*tx) * (x*oy - y*ox) <= 0 )
			return false;
	}

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
