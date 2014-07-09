#include <cstdio>
#include <cmath>

// ベクトルを扱う構造体
struct Vec{
	double x, y;
	Vec(double X=0.0, double Y=0.0){
		x = X;
		y = Y;
	} 
	Vec operator+( const Vec &in ){
		Vec tmp( x + in.x , y + in.y );
		return tmp;
	}
	Vec operator-( const Vec &in ){
		Vec tmp( x - in.x , y - in.y );
		return tmp;
	}
	Vec operator*( const double &in ){
		Vec tmp( x * in , y * in );
		return tmp;
	}
	//内積
	double dot( const Vec &in ){
		return x * in.x + y * in.y;
	}
	//外積
	double cross( const Vec &in ){
		return x * in.y - y * in.x;
	}
	//ベクトルの長さ
	double length(){
		return sqrt( x*x + y*y );
	}
};

//交差しているか求める(どの3点も同直線上にない)
//a1-a2とb1-b2からなる直線が交差するか判定。
//a1-a2上にb1がある場合等は(false)が返る。
bool checkCross(Vec a1, Vec a2, Vec b1, Vec b2){
	Vec va = a2 - a1, vb = b2 - b1;
	Vec v1 = b1 - a1, v2 = b2 - a2;

	if( ( va.cross( v1 ) * va.cross( v2 ) ) < 0.0 &&
		( vb.cross( v1 ) * vb.cross( v2 ) ) < 0.0 )
		return true;
	
	return false;
}


//2円の交点を求める。2円が交わっていなければfalseを返す。
//円a(中心a,半径ra)と円b(中心b,半径rb)の交点p1,p2を求める。
bool circlecross(Vec a, double ra, Vec b, double rb, Vec *p1, Vec *p2){

	double c = (a - b).length();

	//交わっているか判定
	if( c > ra + rb || ra > c + rb || rb > c + ra )
		return false;

	double r = (ra*ra - rb*rb + c*c ) / ( 2.0 * c*c );
	double d = sqrt( ra*ra - c*c*r*r );
	
	Vec tmp( d*(a.y - b.y)/c, d*(b.x - a.x)/c);
	Vec cen = a * (1.0-r) + b * r;
	
	*p1 = cen + tmp;
	*p2 = cen - tmp;

	return true;
}

//三角形はどんな順でもOK。辺上はFALSEを返す。
//(a1,a2,a3)がつくる三角形内にtがあるかどうかを判定する
bool checkInTRIANGLE(Vec a1, Vec a2, Vec a3, Vec t){
	double 	s = (a2-a1).cross(t-a1);
	if( 	s * (a3-a2).cross(t-a2) <= 0.0 ||
			s * (a1-a3).cross(t-a3) <= 0.0 )
		return false;
	
	return true;
}

//三角形はどんな順でもOK。辺上はFALSEを返す。(三角形が成り立ってないときにミスるの防止)
bool checkInTRIANGLE(int pos[3][2], int target[2]){
	
	for(int i=0; i<3; i++){
		int x = pos[(i+1)%3][0] - pos[i][0],
			y = pos[(i+1)%3][1] - pos[i][1],
			ox = pos[(i+2)%3][0] - pos[i][0],
			oy = pos[(i+2)%3][1] - pos[i][1],
			tx = target[0] - pos[i][0],
			ty = target[1] - pos[i][1];
		if( (x*ty - y*tx) * (x*oy - y*ox) <= 0 )
			return false;
	}

	return true;
}

//動作確認(checkInTRIANGEのみ)
int main(){
	int pos[3][2], target[2];
	Vec p[3], t;
	for(int i=0; i<3; i++)
//		scanf("%d %d", pos[i], pos[i]+1);
		scanf("%lf %lf", &p[i].x, &p[i].y);
	printf("ターゲット> ");
	scanf("%lf %lf", &t.x, &t.y);

	printf("結果：　%s\n", checkInTRIANGLE(p[0], p[1], p[2], t)?"TRUE":"FALSE");
	
	return 0;
}
