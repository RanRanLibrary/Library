#include <cstdio>
#include <algorithm> //swap()使うのに必要

typedef long long int LL;

LL gcd(LL n,LL m){
	if(n<m) std::swap(n,m);
	
	if(m==0)return n;
	return gcd(m,n%m);
}


//分数。分母に0は入れちゃダメです
class fraction{
	public:
		LL ue, st;	//分子,分母

		fraction(){ ue=1; st=1; };
		fraction(LL u, LL s){ set(u, s); };
		fraction(int u, int s){ set((LL)u, (LL)s); };
		
		void set(LL u, LL s){
			LL tmp = gcd(u, s);
			ue = u/tmp;
			st = s/tmp;
		};

		fraction operator+( const fraction &f ){
			fraction tmp( ue*f.st + f.ue*st, st * f.st );
			return tmp;
		};
		
		fraction operator-( const fraction &f ){
			fraction tmp( ue*f.st - f.ue*st, st * f.st);
			return tmp;
		};

		fraction operator*( const fraction &f ){
			fraction tmp( ue * f.ue, st * f.st );
			return tmp;
		};

		fraction operator/( const fraction &f ){
			fraction tmp( ue * f.st, st * f.ue);
			return tmp;
		};
		
		fraction &operator=( const fraction &f ){
			ue = f.ue;
			st = f.st;
			return *this;
		};
		
		double real(){ return (double)ue / (double)st; };
};



int main(){
	int u1,s1, u2,s2;

	scanf("%d %d", &u1, &s1 );
	scanf("%d %d", &u2, &s2 );

	fraction f1(u1, s1), f2(u2, s2), tmp(1,1);
	
	tmp = f1 + f2;
	printf("%lld/%lld + %lld/%lld = %lld/%lld  = %f \n", f1.ue,f1.st,f2.ue,f2.st, tmp.ue, tmp.st, tmp.real() );
	
	tmp = f1 - f2;
	printf("%d/%d - %d/%d = %lld/%lld  = %f \n", u1,s1,u2,s2, tmp.ue, tmp.st, tmp.real() );
	
	tmp = f1 * f2;
	printf("%d/%d * %d/%d = %lld/%lld  = %f \n", u1,s1,u2,s2, tmp.ue, tmp.st, tmp.real() );
	
	tmp = f1 / f2;
	printf("%d/%d / %d/%d = %lld/%lld  = %f \n", u1,s1,u2,s2, tmp.ue, tmp.st, tmp.real() );
}
