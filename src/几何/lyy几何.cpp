// 点 直线 多边形 圆类型

// 极角排序
// 重载 + - * / ^ sign ==

// 两点距离 两线夹角 距离平方 距离 三角形面积 点到直线投影 点绕定点旋转 向量定长 两直线交点 直线向点方向移动固定距离

// 点与圆位置关系 0 1 2
// 直线与圆的位置关系，P1,P2 为交点
// 三角形与圆面积交（三角形一点为圆心）
// 多边形与圆面积交
// 两圆面积交（半径都非负）

// 多边形向内缩小r
// 凸多边形内最大三角形 n^2

#include <bits/stdc++.h>
using namespace std;

const int N=10101;

typedef double db;
const db pi = acos(-1.0);
const db eps = 1e-8;
const db inf = 1e20;
const db gen2 = sqrt(2.0);

struct D{ db x,y; D(){} D(db _x,db _y){x=_x;y=_y;} };
struct line{ D s,t; line(){} line(D _s,D _t){s=_s;t=_t;} };
struct pol{ int n; D d[N]; line l[N]; };
struct cir{ db x,y; db r; cir(){} cir(D P,db _r){x=P.x;y=P.y;r=_r;} };

D O = {0,0}, P = {-1,0};
inline bool cmp_point(D A,D B) {   //极角排序（三象限最小，逆时针）
    if(atan2(A.y,A.x)*atan2(B.y,B.x)<0.0) return atan2(A.y,A.x) < atan2(B.y,B.x);
    return ((A-O) ^ (B-O)) > 0;
}
inline bool cmp_vec(D A,D B) {   //极角排序 （OP向量逆时针）
    if(((P-O)^(A-O))==0 && (P.x-O.x)*(A.x-O.x)>0) return 1;
    if(((P-O)^(B-O))==0 && (P.x-O.x)*(B.x-O.x)>0) return 0;
    if((((P-O)^(A-O))>0) != (((P-O)^(B-O))>0)) return ((P-O)^(A-O)) > ((P-O)^(B-O));
    return ((A-O) ^ (B-O)) > 0;
}

int sgn(db x) { if(fabs(x) < eps) return 0; if(x<0) return -1; return 1; }
bool operator == (D A,D B) { return sgn(A.x-B.x)==0 && sgn(A.y-B.y)==0; }
bool operator < (D A,D B) { return sgn(A.x-B.x)==0 ? sgn(A.y-B.y)<0 : A.x<B.x; }
D  operator - (D A,D B) { return {A.x-B.x,A.y-B.y}; }
D  operator + (D A,D B) { return {A.x+B.x,A.y+B.y}; }
db operator ^ (D A,D B) { return A.x*B.y - B.x*A.y; }
db operator * (D A,D B) { return A.x*B.x + A.y*B.y; }
D operator * (D A,db k) { return {A.x*k,A.y*k}; }
D operator / (D A,db k) { return {A.x/k,A.y/k}; }

db dist(D A,D B) { return hypot(A.x-B.x,A.y-B.y); }  //两点距离
db rad(D P,D A,D B) { return fabs( atan2( fabs((A-P)^(B-P)), (A-P)*(B-P) ) ); }
db len2(D P) { return P.x*P.x + P.y*P.y; }
db len1(D P) { return sqrt(len2(P)); }
db SS(D A,D B,D C) { return fabs((A-B)^(A-C)) / 2.0; } //三角形面积
D lineprog(D P,line L) {  //投影
	D M = L.t-L.s;
	return L.s + ( M * (M*(P-L.s) ) ) / len2(M);
}
D rotate(D A,D P,db ang) { // A绕P逆时针转ang角度
	A = A-P; db c = cos(ang), s = sin(ang);
	return {P.x + A.x*c-A.y*s, P.y + A.x*s+A.y*c};
}
D trunc(D P,db k) {  //向量定长
	db l = len1(P);
	if(!sgn(l)) return P;
	return (P/l) * k;
}
D cross(line A,line B){  //两直线交点
	db a1 = (A.t-A.s)^(B.s-A.s);
	db a2 = (A.t-A.s)^(B.t-A.s);
	return D((B.s.x*a2-B.t.x*a1)/(a2-a1),(B.s.y*a2-B.t.y*a1)/(a2-a1));
}
line move(line L,D P,db r) { //L向P方向移动距离r
	D H = lineprog(P,L);
	D vec = trunc(P-H,r);
	return {L.s+vec,L.t+vec};
}


int relat_D(D A,cir C) { //点与圆位置关系
	db d = dist(A,{C.x,C.y});
	if(sgn(d-C.r) < 0) return 2;
	if(sgn(d-C.r) > 0) return 0; // 0在外
	return 1;
}

int relat_L(line L,cir C,D &p1,D &p2) { //直线与圆的位置关系，P1,P2 为交点
	D P = {C.x,C.y};
	D A = lineprog(P,L);
	db d = dist(A,P);
	if(sgn(d-C.r)>0) return 0;
	if(sgn(d-C.r)==0) { p1=A; p2=A; return 1; }
	d = sqrt(C.r*C.r-d*d);
	p1 = A + trunc(L.t-L.s,d);
	p2 = A - trunc(L.t-L.s,d);
	return 2;
}

db TCArea(D A,D B,cir C) {  //三角形与圆面积交（三角形一点为圆心）
	D P = {C.x,C.y};
	if(sgn((P-A)^(P-B))==0) return 0.0;
	line L(A,B);
	D q[5];
	int cnt = 0;
	q[cnt++] = A;
	if(relat_L(L,C,q[1],q[2])==2) {
		if(sgn((A-q[1])*(B-q[1])) < 0) q[cnt++] = q[1];
		if(sgn((A-q[2])*(B-q[2])) < 0) q[cnt++] = q[2];
	}
	q[cnt++] = B;
	if(cnt==4 && sgn((q[0]-q[1])*(q[2]-q[1])) > 0) swap(q[1],q[2]);
	db ans = 0;
	for(int i=0; i<cnt-1; i++) {
		if(relat_D(q[i],C)==0 || relat_D(q[i+1],C)==0)
			ans += C.r*C.r*rad(P,q[i],q[i+1])/2.0;
		else
			ans += fabs((q[i]-P)^(q[i+1]-P))/2.0;
	}
	return ans;
}

db PCArea(pol P,cir C) { //多边形与圆面积交
	db ans = 0; D O = {C.x,C.y};
	for(int i=0;i<P.n;i++) {
		int j = (i+1) % P.n;
		db S = TCArea(P.d[i], P.d[j], C);
		if(sgn( (P.d[i]-O)^(P.d[j]-O) ) >= 0) ans += S;
		else ans -= S;
	}
	return ans;
}

db CCArea(cir c1,cir c2) {   //两圆面积交（半径都非负）
	db d = sqrt( (c1.x-c2.x)*(c1.x-c2.x) + (c1.y-c2.y)*(c1.y-c2.y) );
	if(d>=c1.r+c2.r) return 0;
	if(c1.r-c2.r>=d) return pi * c2.r * c2.r;
	if(c2.r-c1.r>=d) return pi * c1.r * c1.r;
	db ang1 = acos( (d*d + c1.r*c1.r - c2.r*c2.r) / (2*c1.r*d) );
	db ang2 = acos( (d*d + c2.r*c2.r - c1.r*c1.r) / (2*c2.r*d) );
	db s1 = ang1 * c1.r*c1.r;
	db s2 = ang2 * c2.r*c2.r;
	db s3 = d * c1.r * sin(ang1);
	return s1+s2-s3;
}

bool check(line A,line B,line C,db r) { //检查缩小后的边
	D p1 = B.t, p2 = C.s, p3 = A.s, p4 = A.t;
	line nB = move(B,p3,r);
	line nC = move(C,p4,r);
	line nA = move(A,p1,r);
	D p5 = cross(nA,nC);
	D p6 = cross(nA,nB);
	return sgn( (p6-p5)*(A.t-A.s) ) > 0;
}
pol shrink_pol(pol P,db r) {  //多边形向内缩小r
	pol Q; Q.n = 0;
	line A,B,C;
	for(int i=0;i<P.n;i++) {
		A = P.l[i];
		if(i!=P.n-1) B = P.l[i+1];
		else         B = Q.l[0];
		if(Q.n) C = Q.l[Q.n-1];
		else    C = P.l[P.n-1];
		if(check(A,B,C,r))
			Q.l[Q.n++] = A;
	}
	pol SQ; SQ.n = Q.n;
	for(int i=0;i<Q.n;i++) Q.d[i] = Q.l[i].s;
	for(int i=0;i<Q.n;i++) SQ.l[i] = move(Q.l[i],Q.d[(i+2)%Q.n],r);
	for(int i=0;i<Q.n;i++) SQ.d[i] = cross(SQ.l[i],SQ.l[(i-1+Q.n)%Q.n]);
	return SQ;
}

db max_T(pol P) {  //凸多边形内最大三角形 n^2
	db ans = 0;
	for(int i=0;i<P.n;i++) {
		D S1 = P.d[i];
		int j = (i+1)%P.n;
		int k1 = (i+1)%P.n;
		int k2 = (i+2)%P.n;
		while(j!=i) {
			D S2 = P.d[j];
			if(j!=(i+1)%P.n) {
				while((k1+1)%P.n!=j && SS(S1,S2,P.d[k1]) < SS(S1,S2,P.d[(k1+1)%P.n]))
					k1 = (k1+1) % P.n;
				ans = max(ans,SS(S1,S2,P.d[k1]));
			}
			if((j+1)%P.n!=i) {
				while((k2+1)%P.n!=i && SS(S1,S2,P.d[k2]) < SS(S1,S2,P.d[(k2+1)%P.n]))
					k2 = (k2+1) % P.n;
				ans = max(ans,SS(S1,S2,P.d[k2]));
			}
			j = (j+1) % P.n;
		}
	}
	return ans;
}

void outing(db as) { cout<<fixed<<setprecision(6)<<as<<endl; }
