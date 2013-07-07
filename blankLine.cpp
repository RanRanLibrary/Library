#include<cstdio>

using namespace std;

int main(){
  int i;
  char c1,c2;

  while((c1=getchar()) != EOF){
    if(c1=='\n'){
      if((c2=getchar())=='\n'){
        printf("空行\n");
      }else{
        ungetc(c2,stdin);
        printf("改行\n");
      }
    }else if(c1==' '){
      continue;
    }else{
      ungetc(c1,stdin);
      scanf("%d",&i);
      printf("%d\n",i);
    }
  }

  return 0;
}
