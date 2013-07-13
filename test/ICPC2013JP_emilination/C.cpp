#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
char ss[10010];
char *s;

int solve(){
	vector<int> table;
	int d = 0;
	
	while( (*s) != ']' ) {
		if( (*s) == '[' ) {
			s++;
			table.push_back( solve() );
		}else {
			d = (atoi(s)+1) / 2;
			while( (*s) != ']' ) s++;
		}
	}
	s++;
	if( table.size() > 0 ) {
		sort( table.begin(), table.end() );
		
		for(int i = 0; i < (table.size()+1) / 2; i++) {
			d += table[i];
		}
	}
	
	return d;
}

int main(void) {
	int N;
	int d;
	
	scanf("%d", &N);
	
	while( N-- > 0) {
		fill(ss, ss+10010, '\0');
		scanf("%s", ss);
		s = ss;
		s++;
		d = solve();
		printf("%d\n", d);
	}
	
	return 0;
}
