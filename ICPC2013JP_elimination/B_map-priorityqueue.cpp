#include<cstdio>
#include<iostream>
#include<map>
#include<queue>

using namespace std;

int main(){
  int M,T,P,R,i,m,t,p,j;
  int counts[55],pena[55][11],timesum[55];
 
  map<int,priority_queue<int> >::iterator it;

  while(1){
    scanf("%d %d %d %d",&M,&T,&P,&R);
    if(M==0 && T==0 && P==0 && R==0)break;

    memset(counts,0,sizeof(counts));
    memset(pena,0,sizeof(pena));
    memset(timesum,0,sizeof(timesum));
    map<int,priority_queue<int> > time[11];

    for(i=0;i<R;i++){
      scanf("%d %d %d %d",&m,&t,&p,&j);
      if(j){
        pena[t][p]+=20;
      }else{
        counts[t]++;
        timesum[t]+=pena[t][p]+m;
        time[counts[t]][timesum[t]].push(t);
      }
    }

    priority_queue<int> temp;
    bool f=0,flg=0;
    for(i=10;i>0;i--){
   //   cout<<i<<endl;
      for(it=time[i].begin();it!=time[i].end();it++){
        if(f)printf(",");
        temp=it->second;
        flg=f=0;
        while(!temp.empty()){
          if(counts[temp.top()]==i){
            if(flg)printf("=");
            printf("%d",temp.top());
            f=flg=1;
          }
          temp.pop();
        }
      }
    }
    flg=0;
    for(i=T;i>0;i--){
      if(counts[i]==0){
        if(flg)putchar('=');
        printf("%d",i);
        flg=1;
      }
    }
    printf("\n");
  }
  return 0;
}
