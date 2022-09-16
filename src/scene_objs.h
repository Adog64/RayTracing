#include "vector3.h"
#include "colors.h"
#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct planeTexture
{
    int width, height, channels;
    unsigned char *data;
};

struct plane
{
    float scale;
    struct vector3 normal;
    struct vector3 center;
    float rotation;
    struct planeTexture texture;
};

struct sphere
{
    float scale;
    struct vector3 center;
    float radius;
    struct color color;
};

struct lightSource
{
    struct vector3 pos;
    float luminosity;
};

struct intersection
{
    struct vector3 pos;
    float t;
};

// return the texture file as planeTexture
struct planeTexture planeTextureFromFile(char *path);

// return the intersection between a plane and a ray
struct intersection planeIntersection(struct plane p, struct vector3 rayOrigin, struct vector3 rayDirection);

// return the color at position pos in the plane
struct color planeColorAt(struct plane p, struct vector3 pos);

// return the normal of the plane at point pos
struct vector3 planeNormalAt(struct plane p, struct vector3 pos);

// return the intersection between a sphere and a ray
struct intersection sphereIntersection(struct sphere s, struct vector3 rayOrigin, struct vector3 rayDirection);

// return the color at position pos on the sphere
struct color sphereColorAt(struct sphere s, struct vector3 pos);

// return the normal of the sphere at point pos
struct vector3 sphereNormalAt(struct sphere s, struct vector3 pos);

// get a pixel from the plane texture
struct color getPixelFromTexture(struct planeTexture t, int x, int y, int aa);

// check if a texture is valid and loaded properly
bool isValidTexture(struct planeTexture t);

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

struct intersection planeIntersection(struct plane p, struct vector3 rayOrigin, struct vector3 rayDirection)
{
    // ========== RAY PARAMETRIC ==========
    // / x = rayOrigin.x + rayDirection.x*t
    // { y = rayOrigin.y + rayDirection.y*t
    // \ z = rayOrigin.z + rayDirection.z*t
    //
    // ========== PLANE EQUATION ==========
    // (x-center.center.x) + (y-center.center.y) + (z-center.center.z) = 0
    struct intersection is;
    float l1 = dotpv3(p.normal, subv3(p.center, rayOrigin));
    float l2 = dotpv3(p.normal, rayDirection);
    is.t = (l2 != 0) ? l1/l2 : -1;

    is.pos = scalarpv3(rayDirection, is.t);
    return is;
}

struct color planeColorAt(struct plane p, struct vector3 pos)
{
    struct color c = {0, 0, 0};
    
    if (isValidTexture(p.texture))
    {
        // some vector in the plane by the plane rotation around plane center
        struct vector3 planeUV1 = rotatev3(p.normal, normv3(orthov3(p.normal)), p.rotation);
        struct vector3 planeUV2 = crosspv3(p.normal, planeUV1);
        
        struct vector3 f = scalarpv3(addv3(p.center, pos), p.scale);
        int xPos = (((int)(dotpv3(f, planeUV1)*200/p.scale)) % (p.texture.width-1) + (p.texture.width-1)) % (p.texture.width-1);
        int yPos = (((int)(dotpv3(f, planeUV2)*200/p.scale)) % (p.texture.height-1) + (p.texture.height-1)) % (p.texture.height-1);
        c = getPixelFromTexture(p.texture, xPos, yPos, 3);
    }
    return c;
}

struct vector3 planeNormalAt(struct plane p, struct vector3 pos)
{
    return p.normal;
}

struct intersection sphereIntersection(struct sphere s, struct vector3 rayOrigin, struct vector3 rayDirection)
{
    struct intersection i = {{0,0,0}, -1};
    float a = absv3(rayDirection);
    a = a*a;
    float b = 2*dotpv3(rayDirection, subv3(rayOrigin, s.center));
    float c = absv3(subv3(s.center, rayOrigin));
    c = c*c - s.radius*s.radius;

    float discriminant = b*b - 4*a*c;
    if (discriminant >= 0)
    {
        float i1 = -b - sqrtf(discriminant), i2 = -b + sqrtf(discriminant);
        i.t = ((i1 < i2) ? i1 : i2)/(2*a);
        i.pos = scalarpv3(rayDirection, i.t);
    }
    return i;
}

struct vector3 sphereNormalAt(struct sphere s, struct vector3 pos)
{
    return normv3(subv3(pos, s.center));
}

struct color sphereColorAt(struct sphere s, struct vector3 pos)
{
    return s.color;
}

struct color getPixelFromTexture(struct planeTexture t, int x, int y, int aa)
{
    int colors = 0;
    struct color rgb = {0,0,0};
    for (int i = x-aa; i < x+aa; i++)
        for (int j = y-aa; j < y+aa; j++)
            if (i < t.width && i >= 0 && j < t.height && j >= 0)
            {
                const unsigned char *p = t.data + (3 * (j * t.width + i));
                rgb.r += *p;
                rgb.g += *(p+1);
                rgb.b += *(p+2);
                colors++;
            }
    if (colors > 0)
    {
        rgb.r /= colors;
        rgb.g /= colors;
        rgb.b /= colors;
    }
    return rgb;
}

bool isValidTexture(struct planeTexture t)
{
    return t.data != 0;
}