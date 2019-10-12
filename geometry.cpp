//biblioteca grafica montada nas aulas
#include <iostream>
#include "geometry.h"

float AreaTri (vec2 p1, vec2 p2, vec2 p3)
{
	return ((p2.x - p1.x)*(p2.y + p1.y) + (p3.x - p2.x)*(p3.y + p2.y) + (p1.x - p3.x)*(p1.y + p3.y)) / 2;
}

vec2 operator+ (vec2 v1, vec2 v2)
{
    return {v1.x + v2.x, v1.y + v2.y};
}

vec2 operator* (float a, vec2 v1)
{
    return {a*v1.x, a*v1.y};
}

void printVet (vec2 v1)
{
    printf("(%f, %f)\n", v1.x, v1.y);
}

void barycentric (vec2 pt, vec2 *tri, float *b)
{
    int i;
    float a = AreaTri(tri[0], tri[1], tri[2]);
    vec2 p[3];

    for (i=0;i<3;i++)
        p[i] = tri[i];

    for (i=0;i<3;i++){
        p[i] = pt;
        b[i] = AreaTri(p[0],p[1],p[2])/a;
        p[i] = tri[i];
    }
}

void limitesVetor (vec2 *pts, int tam, int *xmin, int *ymin, int *xmax, int *ymax)
{
    int i;

    *xmin = pts[0].x;
    *ymin = pts[0].y;
    *xmax = pts[0].x;
    *ymax = pts[0].y;

    for(i=1; i<tam; i++){
        if (pts[i].x < *xmin)
            *xmin = pts[i].x;
        if (pts[i].y < *ymin)
            *ymin = pts[i].y;
        if (pts[i].x > *xmax)
            *xmax = pts[i].x;
        if (pts[i].y > *ymax)
            *ymax = pts[i].y;
    }
}

vec2 lerp (float t, vec2 a, vec2 b)
{
    vec2 c;

    c.x = (1-t)*a.x + t*b.x;
    c.y = (1-t)*a.y + t*b.y;

    return c;
}

vec2 decasteljau(vec2 P[4], float t){
	vec2 Q[3] = {
		(1-t)*P[0] + t*P[1],
		(1-t)*P[1] + t*P[2],
		(1-t)*P[2] + t*P[3]
	};

	vec2 R[2] = {
		(1-t)*Q[0] + t*Q[1],
		(1-t)*Q[1] + t*Q[2],
	};

	return (1-t)*R[0] + t*R[1];
}

vec2 translate(vec2 P, vec2 v){
	return P + v;
}

void translateV(vec2 P[], int tam, vec2 v, vec2 R[]){
	for(int i = 0; i < tam; i++)
		R[i] = translate(P[i], v);
}

vec2 multMP2(float M[2][2], vec2 P){
	return {
		M[0][0]*P.x + M[0][1]*P.y,
		M[1][0]*P.x + M[1][1]*P.y
	};
}

void multMV2(float M[2][2], vec2 P[], int N, vec2 R[]){
	for(int i = 0; i < N; i++)
		R[i] = multMP2(M, P[i]);
}

void multMM2(float M1[2][2], float M2[2][2], float M[2][2]){
    M[0][0] = M1[0][0]*M2[0][0] + M1[0][1]*M2[1][0];
    M[0][1] = M1[0][0]*M2[0][1] + M1[0][1]*M2[1][1];
    M[1][0] = M1[1][0]*M2[0][0] + M1[1][1]*M2[1][0];
    M[1][1] = M1[1][0]*M2[0][1] + M1[1][1]*M2[1][1];
}

complexo toComplex(vec2 P){
	return {P.x, P.y};
}

vec2 toVec2(complexo c){
	return {c.real(), c.imag()};
}

vec2 operator*(vec2 P, complexo a){
	complexo p = toComplex(P);
return toVec2(p*a);
}

float dot (vec2 u, vec2 v)
{
    return {u.x*v.x + u.y*v.y};
}

vec3 operator+(vec3 u, vec3 v){
	return {u.x + v.x, u.y + v.y, u.z + v.z};
}

vec3 operator*(float a, vec3 v){
	return {a*v.x, a*v.y, a*v.z};
}

vec3 operator- (vec3 u, vec3 v)
{
    return {u.x-v.x, u.y-v.y, u.z-v.z};
}

float dot (vec3 u, vec3 v)
{
    return {u.x*v.x + u.y*v.y + u.z*v.z};
}

float norm (vec3 u)
{
    return sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
}

vec3 normalize (vec3 u)
{
    float n = norm(u);
    return (1/n)*u;
}

vec3 cross (vec3 a, vec3 b)
{
  float i, j, k;
  i = a.y * b.z - b.y * a.z;
  j = b.x *a.z - a.x * b.z;
  k = a.x * b.y - b.x * a.y;
  vec3 res = {i, j, k};

  return res;
}

vec4 operator+(vec4 u, vec4 v){
	return {u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w};
}

vec4 operator*(float a, vec4 v){
	return {a*v.x, a*v.y, a*v.z, a*v.w};
}

vec3 vec4to3(vec4 u){
	return {u.x/u.w, u.y/u.w, u.z/u.w};
}

mat4 operator*(mat4 M1, mat4 M2)
{
    float soma;

    mat4 R;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++){
            soma=0;
            for(int k=0; k<4; k++) soma += M1.M[i][k]*M2.M[k][j];
            R.M[i][j]=soma;
        }
    return R;
}

mat4 multMM4(mat4 M1, mat4 M2, int n)
{
    float soma;

    mat4 R;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            soma=0;
            for(int k=0; k<n; k++) soma += M1.M[i][k]*M2.M[k][j];
            R.M[i][j]=soma;
        }
    return R;
}

mat4 translate(float x, float y, float z)
{
    return {{
            {1, 0, 0, x},
            {0, 1, 0, y},
            {0, 0, 1, z},
            {0, 0, 0, 1},
           }};
}

mat4 scale (float x, float y, float z)
{
    return {{
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    }};
}

mat4 rotate_z (float t)
{
    return {{
        {cos(t), -sin(t), 0, 0},
        {sin(t), cos(t), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0 ,1},
    }};
}

mat4 rotate_y (float t)
{
    return {{
        {cos(t), 0, sin(t), 0},
        {0, 1, 0, 0},
        {-sin(t), 0, cos(t), 0},
        {0, 0, 0 ,1},
    }};
}

mat4 rotate_x (float t)
{
    return {{
        {1, 0, 0, 0},
        {0, cos(t), -sin(t), 0},
        {0, sin(t), cos(t), 0},
        {0, 0, 0 ,1},
    }};
}

vec4 operator* (mat4 M, vec4 v)
{
    return {
        M.M[0][0]*v.x + M.M[0][1]*v.y + M.M[0][2]*v.z + M.M[0][3]*v.w,
        M.M[1][0]*v.x + M.M[1][1]*v.y + M.M[1][2]*v.z + M.M[1][3]*v.w,
        M.M[2][0]*v.x + M.M[2][1]*v.y + M.M[2][2]*v.z + M.M[2][3]*v.w,
        M.M[3][0]*v.x + M.M[3][1]*v.y + M.M[3][2]*v.z + M.M[3][3]*v.w,
   };
}

void multMV4 (mat4 M, vec4 *P, int tam, vec4 *R)
{
    for (int i=0; i<tam; i++){
        R[i] = M*P[i];
    }
}

mat4 orthogonal (float l, float r, float b, float t, float n, float f)
{
    return {{
            {(float)(2/(r-l)), 0, 0, (float)(-(r+l)/(r-l))},
            {0, (float)(2/(t-b)), 0, (float)(-(t+b)/(t-b))},
            {0, 0, (float)(2/(n-f)), (float)(-(n+f)/(n-f))},
            {0, 0, 0, 1}
            }};
}

mat4 frustum (float l, float r, float b, float t, float n, float f)
{
    return {{
        {(float)(-2*n/(r-l)), 0, (r+l)/(r-l), 0},
        {0, (float)(-2*n/(t-b)), (t+b)/(t-b), 0},
        {0, 0, (float)(f+n/(f-n)), (float)(2*n*f/(n-f))},
        {0, 0, -1, 0}
        }};
}

mat4 lookAt (vec3 O, vec3 C, vec3 Up)
{
    Up = normalize(Up);
    vec3 f = normalize(C - O);
    vec3 s = normalize(cross(f, Up));
    vec3 u = cross(s, f);

    mat4 A = {{
        {s.x, s.y, s.z, 0 },
        {u.x, u.y, u.z, 0},
        {-1*f.x, -1*f.y, -1*f.z, 0},
        {0, 0, 0, 1}
    }};
    mat4 B = {{
        {1, 0, 0, -1*O.x},
        {0, 1, 0, -1*O.y},
        {0, 0, 1, -1*O.z},
        {0, 0, 0, 1}
    }};

    return A*B;
}

mat4 perspective (float theta, float a, float n, float f)
{
    float t = n*tan(((theta/180)*M_PI)/2);
    float r = t*a;
    return frustum(-1*r, r, -1*t, t, -n, -f);
}

/*vec2 intersection (vec2 p, vec2 q, vec2 a, vec2 n)
{
    float t = dot(a-p, n)/dot(q-p, n);

    vec2 r = (1-t)*p + t*q;

    return r;

}*/

vec4 CylToCart(float z, float t, float ang)
{
    return {t*sin((double) ang), t*cos((double) ang), z, 1};
}

vec4 waves (float u, float v)
{
    return {u, v, sin(u*v/4), 1};
}

vec4 sphere (float u, float v)
{
    return {cos(u)*sin(v), sin(u)*sin(v), cos(v), 1};
}

vec4 fun (float u, float v)
{
    return {2*sin(u), 3*cos(u), v, 1};
}

