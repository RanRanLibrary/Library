#include<iostream>
#include<cstdio>


using namespace std;

long long gcd(long long n,long long m){
  if(m==0)return n;
  return gcd(m,n%m);
}

int main(){
  long long n,m;
  cin>>n>>m;
  cout<<gcd(n,m)<<endl;
  return 0;
}
