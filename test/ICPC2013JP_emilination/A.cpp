#include<iostream>
#include<cstdio>
#include<map>

using namespace std;

map<int,int> sq[55000];
map<int,int>::iterator it;
int sqv[163];

int main(){
	int i,j;
	
	for(i=0;i<=160;i++){
		sqv[i]=i*i;
	}
	
	int w,h;
	for(h=1;h<=160;h++){
		for(w=h+1;w<=160;w++){
			sq[ sqv[h]+sqv[w] ].insert( make_pair(h,w) );
		}
	}
	
	
	while(1){
		scanf("%d %d",&h,&w);
		if(w==0 && h==0)break;
		
		int sum=sqv[h]+sqv[w];
		it=sq[sum].find(h);
		it++;
		if(it==sq[sum].end()){
			do{
				sum++;
			}while(!sq[sum].size());
			it=sq[sum].begin();
		}
		printf("%d %d\n",(*it).first,(*it).second);
		
	}
	
	return 0;
}
