#pragma once
#include <stdio.h>
struct color
{
    float r, g, b;
};

struct drawableColor
{
    unsigned int r, g, b;
};

int min(int x, int y)
{
    return (x < y) ? x : y;
}

struct drawableColor makeDrawable(struct color c)
{
    struct drawableColor dc;
    dc.r = min(255, (unsigned int)c.r);
    dc.g = min(255, (unsigned int)c.g);
    dc.b = min(255, (unsigned int)c.b);
    return dc;
}

void printcolor(struct color c)
{
    printf("<");
    printf("%f", c.r);
    printf(", ");
    printf("%f", c.g);
    printf(", ");
    printf("%f", c.b);
    printf(">\n");
}