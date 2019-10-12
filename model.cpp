#include "model.h"

Modelo initModelo(mat4 Model, int n, int m, vec4 (*f)(float u, float v), Color *colors)
{
    Modelo superficie;
    superficie.N = m*n;
    float u0 = -5, u1 = 5;
	float du = (u1-u0)/(m-1);

	float v0 = -5, v1 = 5;
	float dv = (v1-v0)/(n-1);

    superficie.P = (vec4*)malloc(superficie.N*sizeof(Modelo));
    superficie.C = (Color*)malloc(superficie.N*sizeof(Color));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            float u = u0 + i*du;
            float v = v0 + j*dv;
            int ij = i + j*m;
            superficie.P[ij] = f(u,v)/*{u, v, sin(u*v/4), 1}*/;
            superficie.C[ij] = biLerp((float)i/m,(float)j/n, colors[0], colors[1], colors[2], colors[3]);
        }
    }

    superficie.Ni = 6*(m-1)*(n-1);
    superficie.indices = (int*)malloc(superficie.Ni*sizeof(int));

    int k=0;
    for(int i = 0; i < m-1; i++){
		for(int j = 0; j < n-1; j++){
			int ij = i + j*m;

			superficie.indices[k++] = ij;
			superficie.indices[k++] = ij+1;
            superficie.indices[k++] = ij+m;

			superficie.indices[k++] = ij+m+1;
			superficie.indices[k++] = ij+m;
			superficie.indices[k++] = ij+1;
		}
    }
    vec4 MP[superficie.N];
    superficie.Model = Model;

    return superficie;
}

void desenha(Image Img, Modelo* models, int nModels, bool preencher){

    mat4 View = lookAt({0,0,30}, {0,0,0}, {0,1,0});
    mat4 Projection = perspective(50,(float)Img.width/Img.height, 1, 50);

    for(int i=0;i<nModels; i++){

        vec4 MP[models[i].N];  mat4 M = Projection*View*models[i].Model;
        multMV4(M, models[i].P, models[i].N, MP);

        if (preencher == true)
            draw_elements_triangles(Img, MP, models[i].indices, models[i].Ni, models[i].C);
        else
            draw_elements_lines(Img, MP, models[i].indices, models[i].Ni, black);
    }
}


