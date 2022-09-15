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

int max(int x, int y)
{
    return (x > y) ? x : y; 
}

// int roundf(float x)
// {
//     return (x-(int)x < 0.5) ? (int)x : (int)x+1;
// }

struct drawableColor makeDrawable(struct color c)
{
    struct drawableColor dc;
    dc.r = max(min(255, (int)roundf(c.r)), 0);
    dc.g = max(min(255, (int)roundf(c.g)), 0);
    dc.b = max(min(255, (int)roundf(c.b)), 0);
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
