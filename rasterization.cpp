#include <iostream>
#include "rasterization.h"
#include <math.h>

void draw_pixel (Image I, int x, int y, Color color)
{
    if (x>=0 && x<I.width && y>=0 && y<I.height){
        Color *p = pixel(I, x, y);
        *p = color;
    }
}

void draw_pixel (Image i, vec3 p, Color c)
{
    float *zb = zbuffer(i, p.x, p.y);

    if(p.z > *zb){
        draw_pixel_aux(i, p. x, p.y, c);
        *zb = p.z;
    }
}

}

void draw_implicit (Image I, Color c, Funcao f)
{
    int x, y;

    for (x=0; x<I.width; x++){
        for (y=0; y<I.height; y++){
            if (f(x, y) <= 0){
                draw_pixel(I, x, y, c);
            }
        }
    }
}

void draw_line (Image i, int x0, int y0, int x1, int y1, Color c){
    int dx = (x1 - x0);
    int dy = (y1 - y0);
    int mdx = abs(dx);
    int mdy = abs(dy);
    int erro = 0; // erro inicial
    int y = y0;
    int x = x0;

    if (dx == 0){
        for (y = std::min(y0, y1); y <= std::max(y0, y1); y++)
            draw_pixel(i, x0, y, c);
    }
    else if (dy == 0) {
        for (x = std::min(x0, x1); x <= std::max(x0, x1); x++)
            draw_pixel(i, x, y0, c);
    }
    else if (mdx >= mdy){
        if (dx > 0){
            for (x = x0; x < x1; x++){
                draw_pixel(i, x, y, c);
                erro = erro + 2*mdy;
                if (erro > mdx){
                    erro = erro - 2*mdx;
                    if (dy > 0)
                        y = y + 1;
                    else
                        y = y - 1;
                }
            }
        }
        else if (dx < 0){
            for (x = x0; x > x1; x--){
                draw_pixel(i, x, y, c);
                erro = erro + 2*mdy;
                if (erro > mdx){
                    erro = erro - 2*mdx;
                    if (dy > 0)
                        y = y + 1;
                    else
                        y = y - 1;
                }
            }
        }
    }
    else if (mdy > mdx) {
        if (dy > 0){
            for (y = y0; y < y1; y++){
                draw_pixel(i, x, y, c);
                erro = erro + 2*mdx;
                if (erro > mdy){
                    erro = erro - 2*mdy;
                    if (dx > 0)
                        x = x + 1;
                    else
                        x = x - 1;
                }
            }
        }
        else if (dy < 0){
            for (y = y0; y > y1; y--){
                draw_pixel(i, x, y, c);
                erro = erro + 2*mdx;
                if (erro > mdy){
                    erro = erro - 2*mdy;
                    if (dx > 0)
                        x = x + 1;
                    else
                        x = x - 1;
                }
            }
        }
    }
}

void draw_lines (Image img, vec2 *V, int tam, Color c)
{
    int i;

    for (i=0; i<tam-1; i = i+2){
        draw_line(img, V[i].x, V[i].y, V[i+1].x, V[i+1].y, c);
    }
}

void draw_line_strip (Image img, vec2 *V, int tam, Color c)
{
    int i;

    for (i=0; i<tam-1; i++){
        draw_line(img, V[i].x, V[i].y, V[i+1].x, V[i+1].y, c);
    }
}

void draw_line_loop(Image img, vec2 *V, int tam, Color c)
{
    draw_line_strip(img, V, tam, c);
    draw_line(img, V[0].x, V[0].y, V[tam-1].x, V[tam-1].y, c);
}

void draw_elements_lines (Image img, vec2 *v, int *indices, int tam, Color c)
{
    int i;

    for (i=0; i<tam-1; i=i+2)
        draw_line(img, v[indices[i]].x, v[indices[i]].y, v[indices[i+1]].x, v[indices[i+1]].y, c);
}

void draw_elements_line_strip (Image img, vec2 *v, int *indices, int tam, Color c)
{
    int i;

    for (i=0; i<tam-1; i++)
        draw_line(img, v[indices[i]].x, v[indices[i]].y, v[indices[i+1]].x, v[indices[i+1]].y, c);
}

void draw_elements_line_loop (Image img, vec2 *v, int *indices, int tam, Color c)
{
    draw_elements_line_strip(img, v, indices, tam, c);
    draw_line(img, v[indices[tam-1]].x, v[indices[tam-1]].y, v[indices[0]].x, v[indices[0]].y, c);
}

void draw_circle (Image img, int xc, int yc, int r, Color c)
{
    int y = r; // primeiro ponto = (0,r)
    int d = 1-r; // primeiro valor de decisão
    int x;

    for(x=0; x<=y; x++){
        draw_pixel(img, xc+x, yc+y, c);
        draw_pixel(img, xc+y, yc+x, c);
        draw_pixel(img, xc+y, yc-x, c);
        draw_pixel(img, xc+x, yc-y, c);
        draw_pixel(img, xc-x, yc+y, c);
        draw_pixel(img, xc-y, yc+x, c);
        draw_pixel(img, xc-y, yc-x, c);
        draw_pixel(img, xc-x, yc-y, c);

        if(d > 0){
            d += 2*x - 2*y + 5;
            y--;
        }
        else
            d += 2*x + 3;
    }
}

void draw_triangle (Image img, vec2 *pts, Color c)
{
    int xmin, xmax, ymin, ymax, i, j, k;
    vec2 pt;
    float bar[3]; // alfas das coordenadas baricentricas do ponto

    limitesVetor(pts, 3, &xmin, &ymin, &xmax, &ymax);

    for(j=ymin; j<=ymax; j++){
        for(i=xmin; i<=xmax; i++){
            pt = {i, j};
            barycentric(pt, pts, bar);
            if(bar[0]>=0 && bar[0]<=1 && bar[1]>=0 && bar[1]<=1 && bar[2]>=0 && bar[2]<=1)
                draw_pixel(img, i, j, c);
        }
    }
}

void draw_triangles (Image img, vec2 *pts, int tam, Color c)
{
    int i;

    for(i=0; i<tam; i+=3){
        draw_triangle(img, pts+i, c);
    }
}

void draw_triangle_strip (Image img, vec2 *pts, int tam, Color c)
{
    int i;

    for(i=0; i<tam-2; i++){
        draw_triangle(img, pts+i, c);
    }
}

void draw_triangle_fan (Image img, vec2 *pts, int tam, Color c)
{
    int i;
    vec2 tri[3];

    tri[0] = pts[0];

    for(i=1; i<tam-1; i++){
        tri[1] = pts[i];
        tri[2] = pts[i+1];
        draw_triangle(img, tri, c);
    }
}

void draw_triangle_interpolation (Image img, vec2 *pts, Color *colors)
{
    int xmin, xmax, ymin, ymax, i, j;
    vec2 pt;
    float bar[3]; // alfas das coordenadas baricentricas do ponto
    Color c;

    limitesVetor(pts, 3, &xmin, &ymin, &xmax, &ymax);

    for(j=ymin; j<=ymax; j++){
        for(i=xmin; i<=xmax; i++){
            pt = {i, j};
            barycentric(pt, pts, bar);
            if(bar[0]>=0 && bar[0]<=1 && bar[1]>=0 && bar[1]<=1 && bar[2]>=0 && bar[2]<=1){
                c = triLerp(bar[0], bar[1], bar[2], colors[0], colors[1], colors[2]);
                draw_pixel(img, i, j, c);
            }
        }
    }
}

void draw_triangles_interpolation (Image img, vec2 *pts, int tam, Color *colors)
{
    int i;

    for(i=0; i<tam; i+=3){
        draw_triangle_interpolation(img, pts+i, colors+i);
    }
}

void draw_triangle_strip_interpolation (Image img, vec2 *pts, int tam, Color *colors)
{
    int i;

    for(i=0; i<tam-2; i++){
        draw_triangle_interpolation(img, pts+i, colors+i);
    }
}

void draw_triangle_fan_interpolation (Image img, vec2 *pts, int tam, Color *colors)
{
    int i;
    vec2 tri[3];
    Color c[3];

    tri[0] = pts[0];
    c[0] = colors[0];

    for(i=1; i<tam-1; i++){
        tri[1] = pts[i];
        tri[2] = pts[i+1];
        c[1] = colors[i];
        c[2] = colors[i+1];
        draw_triangle_interpolation(img, tri, c);
    }
}

void draw_elements_triangles (Image img, vec2 *pts, int *indices, int tamIndices, Color *colors)
{
    int i;
    vec2 auxp[3];
    Color auxc[3];

    for(i=0; i<tamIndices; i+=3){
        auxp[0] = pts[indices[i]];
        auxc[0] = colors[indices[i]];
        auxp[1] = pts[indices[i+1]];
        auxc[1] = colors[indices[i+1]];
        auxp[2] = pts[indices[i+2]];
        auxc[2] = colors[indices[i+2]];

        draw_triangle_interpolation(img, auxp, auxc);
    }

}
void draw_bezier_spline (Image img, vec2 *pts, int tam, Color c)
{
    vec2 curve[PTS_CURVE];
    for(int j = 0; j < tam-1; j += 3){ //j+3 pois a curva 2 começa do ultimo ponto da curva 1; tam-1 pelo msm motivo
        for(int i = 0; i < PTS_CURVE; i++){
            float t = i/(PTS_CURVE-1.0);
            curve[i] = decasteljau(pts+j, t);
        }
        draw_line_strip(img, curve, PTS_CURVE, c);
    }
}

void draw_line (Image i, vec3 a, vec3 b, Color c){
    draw_line(i, a.x, a.y, b.x, b.y, c);
}

void draw_triangle(Image img, vec3 *P, Color *C)
{
    vec2 pts[3] = {{P[0].x, P[0].y}, {P[1].x, P[1].y}, {P[2].x, P[2].y}};

    draw_triangle_interpolation(img, pts, C);
}

vec3 toScreen (Image img, vec4 P)
{
	vec3 v = vec4to3(P);
	v.x = ((v.x+1)*img.width - 1)/2;
	v.y = ((v.y+1)*img.height - 1)/2;
	return v;
}

void draw_line(Image img, vec4 A, vec4 B, Color color)
{
	vec3 v0 = toScreen(img, A);
	vec3 v1 = toScreen(img, B);
	draw_line(img, v0, v1, color);
}

void draw_triangle(Image img, vec4 P[3], Color C[3])
{
	vec3 P3[] = {
		toScreen(img, P[0]),
		toScreen(img, P[1]),
		toScreen(img, P[2])
	};
	draw_triangle(img, P3, C);
}

void draw_lines (Image img, vec4 *V, int tam, Color c)
{
    int i;

    for (i=0; i<tam-1; i = i+2){
        draw_line(img,V[i], V[i+1], c);
    }
}

void draw_line_strip (Image img, vec4 *V, int tam, Color c)
{
    int i;

    for (i=0; i<tam-1; i++){
        draw_line(img, V[i], V[i+1], c);
    }
}

void draw_line_loop (Image img, vec4 *V, int tam, Color c)
{
    draw_line_strip(img, V, tam, c);
    draw_line(img, V[0], V[tam-1], c);
}

void draw_elements_lines (Image img, vec4 *v, int *indices, int tamIndices, Color c)
{
    int i;
    for (i=0; i<tamIndices-1; i=i+2){
        draw_line(img, v[indices[i]], v[indices[i+1]], c);
        /*printf("%g ", v[indices[i]].x);
        printf("%g ", v[indices[i]].y);
        printf("%g ", v[indices[i]].z);
        printf("%g\n", v[indices[i]].w);*/
    }
}

void draw_elements_line_strip (Image img, vec4 *v, int *indices, int tam, Color c)
{
    int i;

    for (i=0; i<tam-1; i++)
        draw_line(img, v[indices[i]], v[indices[i+1]], c);
}

void draw_elements_line_loop (Image img, vec4 *v, int *indices, int tam, Color c)
{
    draw_elements_line_strip(img, v, indices, tam, c);
    draw_line(img, v[indices[tam-1]], v[indices[0]], c);
}

void draw_triangles (Image img, vec4 *pts, int tam, Color *c)
{
    int i;

    for(i=0; i<tam; i+=3){
        draw_triangle(img, pts+i, c);
    }
}

void draw_triangle_strip (Image img, vec4 *pts, int tam, Color *c)
{
    int i;

    for(i=0; i<tam-2; i++){
        draw_triangle(img, pts+i, c);
    }
}

void draw_triangle_fan (Image img, vec4 *pts, int tam, Color *c)
{
    int i;
    vec4 tri[3];

    tri[0] = pts[0];

    for(i=1; i<tam-1; i++){
        tri[1] = pts[i];
        tri[2] = pts[i+1];
        draw_triangle(img, tri, c);
    }
}

void draw_elements_triangles (Image img, vec4 *pts, int *indices, int tamIndices, Color *colors)
{
    int i;
    vec4 tri[3];
    Color c[3];

    for (i=0; i<tamIndices-2; i+=3){
        tri[0] = pts[indices[i]];
        tri[1] = pts[indices[i+1]];
        tri[2] = pts[indices[i+2]];
        c[0] = colors[indices[i]];
        c[1] = colors[indices[i+1]];
        c[2] = colors[indices[i+2]];
        draw_triangle(img, tri, c);
    }
}

void draw_elements_triangle_strip (Image img, vec4 *pts, int *indices, int tamIndices, Color *c)
{
    vec4 tri[3];
    Color c2[3];

    for (int i=0; i<tamIndices-2; i++){
        tri[0] = pts[indices[i]];
        tri[1] = pts[indices[i+1]];
        tri[2] = pts[indices[i+2]];
        c2[0] = c[indices[i]];
        c2[1] = c[indices[i+1]];
        c2[2] = c[indices[i+2]];
        draw_triangle(img, tri, c2);
    }
}

void draw_elements_triangle_fan (Image img, vec4 *pts, int *indices, int tamIndices, Color *c)
{
    vec4 tri[3];
    Color c2[3];

    tri[0] = pts[indices[0]];
    c2[0] = c[indices[0]];

    for (int i=1; i<tamIndices-1; i++){
        tri[1] = pts[indices[i]];
        tri[2] = pts[indices[i+1]];
        c2[1] = c[indices[i]];
        c2[2] = c[indices[i+1]];
        draw_triangle(img, tri, c2);
    }
}



void calculaPosicao (float xmin, float xmax, float ymin, float ymax, vec2 *v)
{
    if (v->x < xmin) v->posicao += 1;
    if (v->x > xmax) v->posicao += 2;
    if (v->y < ymin) v->posicao += 4;
    if (v->y > ymax) v->posicao += 8;
}



void cohen_sutherland (float xmin, float xmax, float ymin, float ymax, vec2 *p1, vec2 *p2)
{
    /*vec2 *v[2] = {p1, p2};

    for (int i=0; i<2; i++){
        /*if (v[i].x < xmin) v[i].posicao += 1;
        if (v[i].x > xmax) v[i].posicao += 2;
        if (v[i].y < ymin) v[i].posicao += 4;
        if (v[i].y > ymax) v[i].posicao += 8;*/
        /*calculaPosicao(xmin, xmax, ymin, ymax, v[i]);
    }

    if (v[0]->posicao==0 && v[1]->posicao ==0) return;

    if ((v[0]->posicao & v[1]->posicao) != 0) return;

    else{
        while (v[0]->posicao!=0 || v[1]->posicao!=0){
            vec2 *aux;

            if (v[0]->posicao != 0)
                aux = v[0];
            else
                aux = v[1];

            if(aux->posicao)

        }
    }*/


}

