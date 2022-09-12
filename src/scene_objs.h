#include "vector3.h"
#include "colors.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdbool.h>

struct planeTexture
{
    int width, height, channels;
    unsigned char *data;
};

struct plane
{
    struct vector3 normal;
    struct vector3 p;
    struct planeTexture texture;
};

struct planeTexture planeTextureFromFile(char *path)
{
    struct planeTexture t;
    int width, height, channels;
    t.data = stbi_load(path, &width, &height, &channels, STBI_rgb);
    if (t.data == 0)
    {
        printf("Error loading image.\n");
        printf(stbi_failure_reason());
        t.width = -1;
        t.height = -1;
        t.channels = -1;
    }
        
    t.width = width;
    t.height = height;
    t.channels = channels;
    return t;
}

// struct vector3 planeIntersection(struct plane p, struct vector3 rayOrigin, struct vector3 rayDirection)
// {
    
// }

struct color getPixelFromTexture(struct planeTexture t, int x, int y)
{
    if (x < t.width && y < t.height)
    {
        const unsigned char *p = t.data + (3 * (y * t.width + x));
        struct color rgb = {*p, *(p+1), *(p+2)};
        return rgb;
    }
    struct color rgb = {0,0,0};
    return rgb;
}

bool isValidTexture(struct planeTexture t)
{
    return t.data != 0;
}