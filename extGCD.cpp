#include<iostream>
#include<cstdio>


using namespace std;

long long gcd1(long long n,long long m,long long &x,long long &y){  //n<mにしろ

  if(m==0){
  	x=0;
  	y=1;
  	return n;
  }
  
  long long temp,re=gcd1(m,n%m,x,y);
  temp=x;
  x=-(n/m)*x+y;
  y=temp;
  cout<<n<<","<<m<<",\t"<<n/m<<","<<x<<endl;
  return re;
}

long long gcd(long long n,long long m,long long &x,long long &y){
	if(n<m)return gcd1(m,n,x,y);
	else return gcd1(n,m,y,x);
}
	


int main(){
  long long n,m,x,y,re;
  cin>>n>>m;
  re=gcd(n,m,x,y);		//nx+my=gcd(n,m)
  printf("%lld*%lld+(%lld*%lld)=%lld\n",n,x,m,y,re);
  return 0;
}
	
