#include <cstdio>
#include <cstring>
#include <map>
#include <queue>

using namespace std;

int main(){
	int M, T, P, R, m, t, p, j;
	int count[51], pena[51][11];
	int timesum[51];
	multimap<int, int>::iterator it;

	while( scanf("%d %d %d %d", &M, &T, &P, &R), M || T || P || R ){
		memset(count, 0, sizeof(count));
		memset(pena, 0, sizeof(pena));
		memset(timesum, 0, sizeof(timesum));
		multimap<int, int> time[11];

		for(int i=0; i < R; i++){
			scanf("%d %d %d %d", &m, &t, &p, &j);
			
			if( j == 0 ){
				count[t]++;
				timesum[t] += pena[t][p] + m;
				time[count[t]].insert(make_pair( timesum[t], t ));
			}else{
				pena[t][p] += 20;
			}
		}
		
		priority_queue<int> que;
		int tim=-1;
		for(int i=10; i > 0; i-- ){
			for(it = time[i].begin(); it != time[i].end(); it++ ){
				if( count[ (*it).second ] == i ){
					if(tim == it->first){
						que.push( it->second );
						//printf("=");
					}else if(tim != -1){
						while( !que.empty() ){
							int tempq=que.top();
							que.pop();
							printf("%d", tempq );
							if(!que.empty()) printf("=");
						}
						printf(",");
						//printf("%d", it->second);
						que.push( it->second );
					}else{
						que.push( it->second );
					}
					tim = it->first;
				}
			}
			if( tim > 0 ) tim = 0;
		}
			while( !que.empty() ){
							int tempq=que.top();
							que.pop();
							printf("%d", tempq );
							if(!que.empty()) printf("=");
						}
		for(int i=T; i>0; i--){
			if( count[i] == 0 ){
				if( tim == -1)
					printf("%d", i);
				else
					printf("%c%d", ( (tim)?'=':','), i);
				tim = 1;
			}
		}
		printf("\n");
	}
	return 0;
}
