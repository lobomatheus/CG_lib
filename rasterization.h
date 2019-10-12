#ifndef RASTERIZATION
#define RASTERIZATION

#include "image.h"
#include "geometry.h"

#define PTS_CURVE 50 // numero de pontos usados para desenhar uma curva; quanto maior mais suave; usado na draw_bezier_spline

//ponteiro p função que recebe 2 inteiros e retorna 1
typedef int (*Funcao)(int, int);

void draw_pixel (Image I, int x, int y, Color color);

//colore um pixel (x, y) com uma cor color
void draw_pixel_aux (Image I, int x, int y, Color color);

//colore com uma cor c uma area definida por uma função implicita f(x, y) <= 0
void draw_implicit (Image I, Color c, Funcao f);

//desenha uma linha de (x0, y0) ate (x1, y1) com uma cor c
//se nenhuma cor for passada, o padrão será preto
void draw_line (Image i, int x0, int y0, int x1, int y1, Color c = black);

//liga pares de pontos consecutivos (na ordem do vetor) do vetor V com uma linha da cor c
//se nenhuma cor for passada, o padrão será preto
void draw_lines (Image i, vec2 *V, int tam, Color c = black);

//liga todos os pontos consecutivos do vetor V com uma cor c
//se nenhuma cor for passada, o padrão será preto
void draw_line_strip (Image img, vec2 *V, int tam, Color c = black);

//liga totos os pontos consecutivos do vetor V e liga o ultimo ponto ao primeiro, com uma cor c
//se nenhuma cor for passada, o padrão será preto
void draw_line_loop(Image img, vec2 *V, int tam, Color c = black);

//liga pares de pontos do vetor v na ordem especificada pelo vetor indices, com uma cor c
//se nenhuma cor for passada, o padrão será preto
void draw_elements_lines (Image img, vec2 *v, int *indices, int tam, Color c = black);

//liga os pontos do vetor v na ordem especificada pelo vetor indices com a cor c
//se nenhuma cor for passada, o padrão será preto
void draw_elements_line_strip (Image img, vec2 *v, int *indices, int tam, Color c = black);

//liga os pontos do vetor v na ordem especificada pelo vetor indices e liga o ultimo ponto do indice ao primeiro, com a cor c
//se nenhuma cor for passada, o padrão será preto
void draw_elements_line_loop (Image img, vec2 *v, int *indices, int tam, Color c = black);

//desenha um circulo de raio r centrado em (xc, yc), na cor c
//se nenhuma cor for passada, o padrão será preto
void draw_circle (Image img, int xc, int yc, int r, Color c = black);

//desenha um triangulo definido pelos pontos em pts com a cor c
//se nenhuma cor for passada, o padrao sera preto
void draw_triangle (Image img, vec2 *pts, Color c = black);

//desenha tam/3 triangulos, definidos pelos trios de pontos em pts (na sequencia do vetor) com a cor c
//se nenhuma cor for passada, o padrao sera preto
void draw_triangles (Image img, vec2 *pts, int tam, Color c);

//(FAIXA DE TRIANGULOS) desenha todos os trinagulos definidos pelos pontos em pts (na sequencia do vetor) com a cor c
//se nenhuma cor for passada, o padrao sera preto
void draw_triangle_strip (Image img, vec2 *pts, int tam, Color c);

//(LEQUE DE TRIANGULOS)desenha todos os trinagulos definidos por um p0 central + 2 pontos em pts (na sequencia do vetor)
//com a cor c. se nenhuma cor for passada, o padrao sera preto
void draw_triangle_fan (Image img, vec2 *pts, int tam, Color c);

//desenha um triangulo definido pelos pontos em pts
//cada pixel recebe a interpolação das 3 cores em colors pelas coordenadas baricentricas do ponto em relação ao triangulo
void draw_triangle_interpolation (Image img, vec2 *pts, Color *colors);

//draw_triangles fazendo interpolação das cores (1 cor p cada vertice)
void draw_triangles_interpolation (Image img, vec2 *pts, int tam, Color *colors);

//draw_triangle_strip fazendo interpolação das cores (1 cor p cada vertice)
void draw_triangle_strip_interpolation (Image img, vec2 *pts, int tam, Color *colors);

//draw_triangle_fan fazendo interpolação das cores (1 cor p cada vertice)
void draw_triangle_fan_interpolation (Image img, vec2 *pts, int tam, Color *colors);

//desenha trinagulos a partir de um vetor de indices que indica os pontos a serem usados p cada triangulo
//as cores são interpoladas
void draw_elements_triangles (Image img, vec2 *pts, int *indices, int tamIndices, Color *colors);

//desenha uma spline (sequencia de polinomios [curvas]) de curvas de bezier
//se nenhuma cor for passada, o padrao sera preto
void draw_bezier_spline (Image img, vec2 *pts, int tam, Color c = black);

void draw_line (Image i, vec3 a, vec3 b, Color c);

void draw_triangle(Image, vec3 *P, Color *C);

vec3 toScreen (Image img, vec4 P);

void draw_line(Image img, vec4 A, vec4 B, Color color);

void draw_triangle(Image img, vec4 P[3], Color C[3]);

void draw_lines (Image img, vec4 *V, int tam, Color c);

void draw_line_strip (Image img, vec4 *V, int tam, Color c);

void draw_line_loop (Image img, vec4 *V, int tam, Color c);

void draw_elements_lines (Image img, vec4 *v, int *indices, int tamIndices, Color c);

void draw_elements_line_strip (Image img, vec4 *v, int *indices, int tam, Color c);

void draw_elements_line_loop (Image img, vec4 *v, int *indices, int tam, Color c);

void draw_triangles (Image img, vec4 *pts, int tam, Color *c);

void draw_triangle_strip (Image img, vec4 *pts, int tam, Color *c);

void draw_triangle_fan (Image img, vec4 *pts, int tam, Color *c);

void draw_elements_triangles (Image img, vec4 *pts, int *indices, int tamIndices, Color *colors);

void draw_elements_triangle_strip (Image img, vec4 *pts, int *indices, int tamIndices, Color *c);

void draw_elements_triangle_fan (Image img, vec4 *pts, int *indices, int tamIndices, Color *c);

//calcula a posicao do ponto em relação a area de desenho para algoritmo de cohen sutherland
void calculaPosicao (float xmin, float xmax, float ymin, float ymax, vec2 *v);

#endif // RASTERIZATION
