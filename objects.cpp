#include "objects.h"

Color *get_color_vertices(Color *color, vec4 *vertices, int nvert)
{
    auto *cout = (Color*) malloc(nvert*sizeof(Color));

    for(int i=0; i<nvert; i++){
        cout[i] = interpolacaoBilinear(vertices[i].x, vertices[i].y, color[0], color[1], color[2], color[3]);
    }

    return cout;
}

int* get_indices(vec3 *arestas, int narest)
{
    int* indices = (int*)malloc(3*narest*sizeof(int));

    for(int i=0, k=0; i<narest; i++)
    {
        indices[k++] = (int) arestas[i].x-1;
        indices[k++] = (int) arestas[i].y-1;
        indices[k++] = (int) arestas[i].z-1;
    }

    return indices;
}