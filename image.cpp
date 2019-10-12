#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "image.h"

Color* pixel(Image I, int x, int y){
	return I.data + (y*I.width + x);
}

Image newImage(int w, int h, Color c, bool useZBuffer){
	Image img = {w, h};
	img.data = (Color*)malloc(w*h*sizeof(Color));
	img.ZBuffer = NULL;
	if(useZBuffer)
		img.ZBuffer = (float*)malloc(w*h*sizeof(float));
	initImage(img, c);
	return img;
}

void freeImage(Image img){
	free(img.data);
	free(img.ZBuffer);
}

void savePNG(const char* filename, Image img){
    stbi_write_png(filename, img.width, img.height, 3, img.data, 0);
}

void initImage(Image img, Color color){
    int x, y;

	for(y = 0; y < img.height; y++)
		for(x = 0; x < img.width; x++){
			Color* p = pixel(img, x, y);
			*p = color;
		}
}

void invertY(int n)
{
    stbi_flip_vertically_on_write(n);
}

void quadricular (Image img, Color c1, Color c2, int n)
{
    int x, y;
    int w = img.width/n; //largura de cada quadrado
    int h = img.height/n; //altura de cada quadrado

    for(y = 0; y < img.height; y++){
		for(x = 0; x < img.width; x++){
            Color* p = pixel(img, x, y);
            ///2h == 2*altura do quadrado
            ///2w = 2*largura do quadrado
            if ((y%(2*h)) < h){ ///se o resto de y/(2h) for menor do que a altura do quadrado, ele esta no primeiro quadrado de baixo pra cima
                if ((x%(2*w)) < w) ///se o resto de y/(2w) for menor q a largura do quadrado, ele esta no primeiro da esq pra dir
                    *p = c1;
                else
                    *p = c2;
            }
            else{
                if ((x%(2*w)) < w)
                    *p = c2;
                else
                    *p = c1;
            }
		}
    }
}

Image loadImage (char* nome)
{
    Image i;
    int j, k;

    Byte *aux = stbi_load(nome, &i.width, &i.height, &i.nrChannels, 0);

    i.data = (Color*)malloc(i.width*i.height*sizeof(Color));

    // j pula de 4 em 4 pois a imagem terá 4 canais: R, G, B e o canal de controle (que a gnt ignora)
    for (j=0, k=0; j<(i.width*i.height*i.nrChannels); k++, j+=i.nrChannels){
        i.data[k].r = aux[j];
        i.data[k].g = aux[j+1];
        i.data[k].b = aux[j+2];
    }

    return i;
}

Image dissolve (float t, Image img1, Image img2)
{
    int i;
    Image saida;

    saida = newImage(img1.width, img1.height);

    for (i=0; i<(saida.width*saida.height); i++)
        saida.data[i] = lerp(t, img1.data[i], img2.data[i]);

    return saida;
}

// Acessar zbuffer no pixel (x,y)
float* zbuffer(Image I, int x, int y){
	return I.ZBuffer + (y*I.width + x);
}

void initZBuffer(Image img){
	if(img.ZBuffer == NULL)
		return;

	for(int y = 0; y < img.height; y++)
		for(int x = 0; x < img.width; x++){
			float* zb = zbuffer(img, x, y);
			*zb = -1;
		}
}

