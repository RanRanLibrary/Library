#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;
int holes[1005][1005],table[1005][1005];
bool prime[1000008];


int main(){
	int m,n,g,x,y,sx,sy,i,j;
	int dx[]={1,0,-1,0},dy[]={0,-1,0,1},d;
	
	memset(prime,1,sizeof(prime));
	prime[0]=prime[1]=0;
	for(i=2;i<=1000003;i++){
		if(prime[i])for(j=i*2;j<=1000003;j+=i){
			prime[j]=0;
		}
	}
	
	while(1){
		scanf("%d %d",&m,&n);
		if(m==0&&n==0)break;
		
		memset(holes,0,sizeof(holes));
		memset(table,-1,sizeof(table));
		g=(int)ceil(sqrt(m));
		y=x=g/2+1;	//縁を0でうめる
		d=3;
		holes[y][x]=1;
		for(i=2;i<=m;i++){
			if(holes[y+dy[(d+1)%4]][x+dx[(d+1)%4]]==0){
				d=(d+1)%4;
			}
			x+=dx[d];
			y+=dy[d];
			
			holes[y][x]=i;
			if(i==n){
				sx=x;
				sy=y;
			}
		}
		
	/*	for(i=0;i<=g+1;i++){
			for(j=0;j<=g+1;j++)
				printf("%3d ",holes[i][j]);
			printf("\n");
		}
		*/
		int maxNum=0,maxCnt=0;
		table[sy][sx]=0;
		for(y=sy;y<=g;y++){
			for(x=1;x<=g;x++){
				if(table[y][x]==-1)continue;
				if(prime[holes[y][x]])table[y][x]++;
				if(maxCnt<table[y][x] && holes[y][x]>0){
					maxCnt=table[y][x];
					maxNum=holes[y][x];
				}else if(maxCnt==table[y][x]){
					if(maxNum<holes[y][x])
						if(prime[holes[y][x]])
						maxNum=holes[y][x];
				}
				
				for(i=-1;i<=1;i++){
					if(table[y+1][x+i]<table[y][x]){
						table[y+1][x+i]=table[y][x];
					}
				}
			}
		}
		
		/*cout<<endl;
		for(i=0;i<=g+1;i++){
			for(j=0;j<=g+1;j++)
				printf("%3d ",table[i][j],holes[i][j]);
			printf("\n");
		}*/
		
		printf("%d %d\n",maxCnt,maxNum);
				
		
	}
	
	return 0;
}
