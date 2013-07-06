一行に複数の入力:char*->int*版
#include<iostream>
#include<map>
#include<cstring>

using namespace std;

map<char* ,int> m;
map<char*,int>::iterator it;

int main(){
  int num[10],len,l,r,i;
  char str[1000];

  fgets(str,1000,stdin);
  i=l=r=0;
  len=strlen(str);
  while(r<len){
    for(l=r;r<len;r++)
      if(str[r]==' ')break;
    str[r]='\0';
    num[i]=atoi(&str[l]);
    i++;
    r++;
  }

  for(i--;i>=0;i--)//確認
    cout<<num[i]<<endl;
  return 0;
}

一行に複数の入力 vector<string>を返す

vector<string> getStrs(){
  char str[1000];
  int r,l,len;
  vector<string> strs;
  fgets(str,1000,stdin);
  l=r=0;
  len=strlen(str);
  while(r<len){
    for(l=r;r<len;r++)
      if(str[r]==' '||str[r]=='\n')break;
    str[r]='\0';
    strs.push_back(string(&str[l]));
    while(r<len){
      r++;
      if(str[r]!=' ' && str[r]!='\n')break;
    }
  }
  return strs;
}

int main(){
  vector<string> v=getStrs();
  for(int i=0;i<v.size();i++)
    cout<<v[i]<<endl;
  return 0;
}

  
一行に複数の入力vector<int>を返す


vector<int> getStrs(){
  char str[1000];
  int r,l,len;
  vector<int> nums;
  fgets(str,1000,stdin);
  l=r=0;
  len=strlen(str);
  while(r<len){
    for(l=r;r<len;r++)
      if(str[r]==' '||str[r]=='\n')break;
    str[r]='\0';
    nums.push_back(atoi(&str[l]));
    while(r<len){
      r++;
      if(str[r]!=' ' && str[r]!='\n')break;
    }
  }
  return nums;
}

int main(){
  vector<int> v=getStrs();
  for(int i=0;i<v.size();i++)
    cout<<v[i]<<endl;
  return 0;
}

