#pragma once
#include <stdio.h>
#include <stdlib.h>

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

int max(int x, int y)
{
    return (x > y) ? x : y; 
}

struct drawableColor makeDrawable(struct color c)
{
    struct drawableColor dc;
    dc.r = max(min(255, (c.r - (int)c.r < (float)rand()/((float)RAND_MAX)) ? (int)c.r : (int)c.r + 1), 0);
    dc.g = max(min(255, (c.g - (int)c.g < (float)rand()/((float)RAND_MAX)) ? (int)c.g : (int)c.g + 1), 0);
    dc.b = max(min(255, (c.b - (int)c.b < (float)rand()/((float)RAND_MAX)) ? (int)c.b : (int)c.b + 1), 0);
    return dc;
}

struct color dimColorPercent(struct color c, float d)
{
    struct color dimmedColor = {c.r/d, c.g/d, c.b/d};
    return dimmedColor;
}

struct color brightenColorPercent(struct color c, float d)
{
    d++;
    struct color brightenedColor = {c.r*d, c.g*d, c.b*d};
    return brightenedColor;
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

struct color color(float r, float g, float b)
{
    struct color c = {r, g, b};
    return c;
}
