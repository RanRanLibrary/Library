#include<iostream>
#include<cstdio>

using namespace std;

long long _pow(int n,int m){    //n^m
    if(m==0) return 1;
    long long tmp=_pow(n,m/2);
    return tmp*tmp*(m%2?n:1);
}

long long pow(int n,int m,int q=1e9+7){    //n^m%q
	if(m==0) return 1;
	long long tmp = pow(n,m/2,q);
	return ((tmp*tmp)%q)*(m%2?n:1)%q;
}

int main(){
    long long n,m,q;
    while(scanf("%lld %lld %lld",&n,&m,&q)!=EOF){
        if(q){
            cout<<pow(n,m,q)<<endl;
        }else{
            cout<<_pow(n,m)<<endl;
        }
    }
   
    return 0;
}
