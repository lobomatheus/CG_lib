#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

//define a estrutura image com largura, altura e um ponteiro p um vetor de cores (pixels)
struct Image {
    int width, height;
    int nrChannels = 3; // usado somente p imagens carregadas
    Color *data;
    //Byte *loaded; // usado somente p imagens carregadas
    float *ZBuffer;
};

//retorna um ponteiro para o pixel (x,y) da imagem I
Color* pixel(Image I, int x, int y);

//retorna uma struct imagem de tamanho (w,h)
//se nenhuma cor for passada, a imagem será preenchida com branco por padrão
Image newImage(int w, int h, Color c = white, bool useZBuffer = false);

//destroi um objeto imagem
void freeImage(Image img);

//salva um arquivo png
void savePNG(const char* filename, Image img);

//inicia uma imagem com uma cor
void initImage(Image img, Color color);

//inverte a imagem verticalmente (eixo y)
//(originalmente o y aponta p baixo)
void invertY(int n);

//preenche a imagem com um quadriculado nxn de duas cores, começando por c1
void quadricular (Image img, Color c1, Color c2, int n);

//carrega uma imagem
Image loadImage(char* nome);

// sobrepoe duas imagens de mesmo tamanho via interpolação linear
Image dissolve (float t, Image img1, Image img2);

// Acessar zbuffer no pixel (x,y)
float* zbuffer(Image I, int x, int y);

//inicializa o zbuffer da imagem com -1 em todas as posições
void initZBuffer(Image img);

#endif // IMAGE_H
