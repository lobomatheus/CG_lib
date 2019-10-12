#ifndef MODEL_H
#define MODEL_H

#include "rasterization.h"

//modelo com vetor de pontos P e seu tamanho N; vetor de indices e seu tamanho Ni, e vetor de Cores de tamanho 4
struct Modelo{
    vec4 * P;
    int N;
    int* indices;
    int Ni;
    mat4 Model;
    Color* C;
};

//inicia um modelo de nxm vertices arrranjando seus vertices com base na funcção f e calculando a cor de cada um com biLerp das cores
Modelo initModelo(mat4 Model, int n, int m, vec4 (*f)(float u, float v), Color *colors = sea);

//recebe um vetor de modelo com nModels modelos e desenha em uma figura
//se preencher == false, desenha somente as arestas com draw_elements_lines
//se preencher == true, desenha e pinta as faces com draw_elements_triangles
void desenha(Image Img, Modelo* models, int nModels, bool preencher = false);

#endif // MODEL_H
