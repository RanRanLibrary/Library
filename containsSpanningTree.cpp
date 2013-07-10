#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;
double minDist,dist,px[103],py[103],sum;

double findDist(int i,int j){
  double dx=px[i]-px[j],dy=py[i]-py[j];
 // cout<<"["<<dx<<","<<dy<<"]"<<endl;
  return sqrt(dx*dx+dy*dy);
}

int main(){
  int q;
  int n,i,j,k,minInd;
  bool connected[103];

  scanf("%d",&q);
  while(q--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
      scanf("%lf %lf",&px[i],&py[i]);
   //   cout<<px[i]<<","<<py[i]<<endl;
    }
    memset(connected,0,sizeof(connected));
    sum=0;
    connected[0]=1;
    for(k=1;k<n;k++){
      minInd=0;
      for(i=0;i<n;i++){
        if(!connected[i])continue;
        for(j=0;j<n;j++){
          if(connected[j])continue;
          dist=findDist(i,j);
 //         cout<<dist<<"("<<i<<","<<j<<")"<<endl;
          if(minInd){
            if(minDist>dist){
              minDist=dist;
              minInd=j;
            }
          }else{
            minInd=j;
            minDist=dist;//findDist(i,j);
          }
        }
      }
//      cout<<minDist<<"to"<<minInd<<endl;
      sum+=minDist;
      connected[minInd]=1;
    }
    printf("%.2f\n",sum);
    if(q)printf("\n");
  }
  return 0;
}
