#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)

using namespace std;


// iterator の指す値を取得する
//   set<int> st;
//   auto it = st.begin();
//   itval(st, it)           // *it と同じ
//   itval(st, it, +2)       // (it++, it++, *it) と同じ。ただし、itは変更されない
//   itval(st, it, +1, 0)    // もし、it+1 が st.end() の場合 0 を返す

template<typename T>
T itval(set<T> &st, typename set<T>::iterator it, int move = 0, const T &default_value = {}){
	if( move <  0 && it == st.begin() ) return default_value;
	if( move >= 0 && it == st.end()   ) return default_value;
	if( move < 0 ) return itval(st, --it, move+1, default_value);
	if( move > 0 ) return itval(st, ++it, move-1, default_value);
	return *it;
}



// http://codeforces.com/gym/101431/problem/C

typedef pair<int,int> pii;

int point(set<pii> &st, set<pii>::iterator it, int move=0){
	if( move <  0 && it == st.begin() ) return 0;
	if( move >= 0 && it == st.end()   ) return 0;
	if( move < 0 ) return point(st, --it, move+1);
	if( move > 0 ) return point(st, ++it, move-1);
	int ret = 0;
	ret = max(ret, itval(st, it, +1).second);
	ret = max(ret, itval(st, it, -1).second);
	return ret;
}


int main(){
	int N;
	int x[2][100005], v[100005];

	cin >> N;
	rep(i,N) cin >> x[0][i] >> x[1][i] >> v[i];

	map<int, set<pii> > mp[2];
	int diff[100005]={};
	rep(i,N) rep(k,2){
		auto &st = mp[k^1][ x[k][i] ];
		auto cur = pii(x[k^1][i], v[i]);
		int before = 0;
		if(st.size() > 1){
			auto it = st.lower_bound( cur );
			before += point(st, it);
			before += point(st, it, -1);
		}

		st.insert(cur);

		int after = 0;
		if(st.size() > 1){
			auto it = st.lower_bound( cur );
			after += point(st, it);
			after += point(st, it, +1);
			after += point(st, it, -1);
		}

		diff[i] += after - before;
	}

	int ans = 0;
	rep(i,N){
		ans += diff[i];
		cout << ans << endl;
	}

	return 0;
}
