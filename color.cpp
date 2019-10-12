#include <iostream>
#include "color.h"

float clamp (float v, float a, float b)
{
    if (v < a)
        v = a;
    else if (v > b)
        v = b;
    return v;
}

Color lerp (float t, Color a, Color b)
{
    Color c;

    c.r = clamp((1-t)*a.r + t*b.r, 0, 255);
    c.g = clamp((1-t)*a.g + t*b.g, 0, 255);
    c.b = clamp((1-t)*a.b + t*b.b, 0, 255);

    return c;
}

Color biLerp (float u, float v, Color a, Color b, Color c, Color d)
{
    Color e, f, g;

    e = lerp (u, a, b);
    f = lerp (u, c, d);
    g = lerp (v, e, f);

    return g;
}

void printColor (Color c)
{
    printf("{%d, %d, %d}\n", c.r, c.g, c.b);
}

bool operator== (Color c1, Color c2)
{
    if ((c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b))
        return true;
    return false;
}


Color triLerp (float a1, float a2, float a3, Color c1, Color c2, Color c3)
{
    Color c;

    c.r = clamp(a1*c1.r + a2*c2.r + a3*c3.r, 0, 255);
    c.g = clamp(a1*c1.g + a2*c2.g + a3*c3.g, 0, 255);
    c.b = clamp(a1*c1.b + a2*c2.b + a3*c3.b, 0, 255);

    return c;
}
