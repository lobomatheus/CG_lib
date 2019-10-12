#ifndef COLOR_H
#define COLOR_H

//define um Byte como um tipo de 8 bits
typedef unsigned char Byte;

//define a estrutura Color
struct Color {
    Byte r, g, b;
};

#include "colors_list.h"

//retorna um numero no intervalo [a,b]
float clamp (float v, float a, float b);

//Interpolaçao linear de duas cores A e B
Color lerp (float t, Color a, Color b);

//interpolação bilinear de 4 cores
Color biLerp (float u, float v, Color a, Color b, Color c, Color d);

//imprime uma cor
void printColor (Color c);

//compara 2 cores
bool operator== (Color c1, Color c2);

//interpolação de 3 cores pelas coordenas baricentricas de um triangulo
Color triLerp (float a1, float a2, float a3, Color c1, Color c2, Color c3);

#endif // COLOR_H
