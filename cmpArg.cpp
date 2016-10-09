// 偏角ソート用関数
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#define rep(i,n) for(int i=0; i<(n); i++)
#define rrep(i,n) for(int i=(n)-1; i>=0; i--)
#define all(X) (X).begin(),(X).end()

#define X first
#define Y second
#define pb push_back
#define eb emplace_back

using namespace std;
typedef long long int ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

template<class T> ostream& operator<<(ostream &os, const vector<T> &t) {
os<<"{"; rep(i,t.size()) {os<<t[i]<<",";} os<<"}"<<endl; return os;}
template<class S, class T> ostream& operator<<(ostream &os, const pair<S,T> &t) { return os<<"("<<t.first<<","<<t.second<<")";}


/***
 * 偏角ソート
 * intの範囲内の整数の点を、原点から見た角度でソートします。(半時計回りを正方向)
 * 角度の基準(arg=0)を(0,-1)方向にとっています。
 * 点(0,0)は、arg=0です。
 */

// 偏角ソート用比較関数( +:a>b 0:a=b -:a<b (-y方向を基準に反時計回りに見て))
ll cmpArg(const pll &a, const pll &b){
	int na = (a.X<0 ? 3 : 1) * (a.X==0 ? (a.Y>0?2:0) : 1);
	int nb = (b.X<0 ? 3 : 1) * (b.X==0 ? (b.Y>0?2:0) : 1);
	if( na != nb || na%2 == 0 ){
		return nb - na;
	}else{
		return b.Y*a.X - a.Y*b.X;
	}
}

bool cmpb(const pll &a, const pll &b){
	return cmpArg(a,b) > 0;
}

int main(){
	int x, y;
	vector<pii> v;
	while(cin >> x >> y){
		v.eb(x, y);
		sort( all(v), cmpb );
		cout << v << endl;
	}
	return 0;
}
