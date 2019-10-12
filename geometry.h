#ifndef GEOMETRY
#define GEOMETRY

#include <complex>

typedef std::complex<float> complexo;

//representa pontos ou vetores
struct vec2 {
	float x, y;
	int posicao = -1; //usado somente para o algoritmo de cohen sutherland
};

struct vec3{
	float x, y, z;
	int posicao = 0;
};

struct vec4{
	float x, y, z, w;
	int posicao = 0;
};

struct mat4{
	float M[4][4];
};

//retorna area do triangulo
float AreaTri(vec2 p1, vec2 p2, vec2 p3);

//define soma de vetores
vec2 operator+ (vec2 v1, vec2 v2);

//multiplicação de vetor por escalar
vec2 operator* (float a, vec2 v1);

//imprime um vetor ou ponto
void printVet (vec2 v1);

//grava no vetor b as coordenadas baricentricas do ponto pt em relação ao triangulo tri
void barycentric (vec2 pt, vec2 *tri, float *b);

//seta os x e y minimos e maximos do vetor de pontos
void limitesVetor (vec2 *pts, int tam, int *xmin, int *ymin, int *xmax, int *ymax);

//faz a interpolaçao de dois vetores a e b pelo parametro t
vec2 lerp (float t, vec2 a, vec2 b);

//acha um ponto sobre uma curva de bezier com o algoritmo de decasteljau
vec2 decasteljau(vec2 P[4], float t);

//translada um vetor p pelo vetor v
vec2 translate(vec2 P, vec2 v);

//translada um conjunto de vetores p de tamanho tam por um vetor v e salva o resultado em R
void translateV(vec2 P[], int tam, vec2 v, vec2 R[]);

//multiplicação de matriz 2x2 por ponto
vec2 multMP2(float M[2][2], vec2 P);

//multiplicação de matriz 2x2 por vetor de pontos
void multMV2(float M[2][2], vec2 P[], int N, vec2 R[]);

//multiplica 2 matrizes no R2
void multMM2(float M1[2][2], float M2[2][2], float M[2][2]);

complexo toComplex(vec2 P);

vec2 toVec2(complexo c);

vec2 operator*(vec2 P, complexo a);

float dot (vec2 u, vec2 v);

vec3 operator+(vec3 u, vec3 v);

vec3 operator*(float a, vec3 v);

vec3 operator- (vec3 u, vec3 v);

float dot (vec3 u, vec3 v);

float norm (vec3 u);

vec3 normalize (vec3 u);

vec3 cross (vec3 a, vec3 b);

vec4 operator+(vec4 u, vec4 v);

vec4 operator*(float a, vec4 v);

vec3 vec4to3(vec4 u);

mat4 operator*(mat4 M1, mat4 M2);

mat4 multMM4(mat4 M1, mat4 M2, int n);

mat4 translate(float x, float y, float z);

mat4 scale (float x, float y, float z);

mat4 rotate_x (float t);

mat4 rotate_y (float t);

mat4 rotate_z (float t);

vec4 operator* (mat4 M, vec4 v);

void multMV4 (mat4 M, vec4 *P, int tam, vec4 *R);

mat4 orthogonal (float l, float r, float b, float t, float n, float f);

mat4 frustum (float l, float r, float b, float t, float n, float f);

mat4 lookAt (vec3 O, vec3 C, vec3 Up);

mat4 perspective (float theta, float a, float n, float f);

vec4 CylToCart(float z, float t, float ang);

//retorna as equações parametricas da superficie de ondas
vec4 waves (float u, float v);

//retorna as equações parametricas da esfera
vec4 sphere (float u, float v);

vec4 fun (float u, float v);

#endif //GEOMETRIA
