#include<iostream>
#include<cstdio>

using namespace std;

long long pow(int n,int m){    //n^m
    if(m==1)return n;
    long long temp=pow(n,m/2);
    return temp*temp*( n%2?2:1);
}

long long pow(int n,int m,int q){    //n^m%q
    if(m==1)return n;
    long long temp=pow(n,m/2,q)%q;
    return temp*temp*( n%2?2:1)%q;
}

int main(){
    long long n,m,q;
    while(scanf("%lld %lld %lld",&n,&m,&q)!=EOF){
        if(q){
            cout<<pow(n,m,q)<<endl;
        }else{
            cout<<pow(n,m)<<endl;
        }
    }
   
    return 0;
}
