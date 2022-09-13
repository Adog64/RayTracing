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
    float scale;
    struct vector3 normal;
    struct vector3 center;
    float rotation;
    struct planeTexture texture;
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

// get a pixel from the plane texture
struct color getPixelFromTexture(struct planeTexture t, int x, int y);

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
        int xPos = (((int)(dotpv3(f, planeUV1)*50/p.scale)) % (p.texture.width-1) + (p.texture.width-1)) % (p.texture.width-1);
        int yPos = (((int)(dotpv3(f, planeUV2)*50/p.scale)) % (p.texture.height-1) + (p.texture.height-1)) % (p.texture.height-1);
        c = getPixelFromTexture(p.texture, xPos, yPos);
    }
    return c;
}

struct color getPixelFromTexture(struct planeTexture t, int x, int y)
{
    if (x < t.width && x >= 0 && y < t.height && y >= 0)
    {
        const unsigned char *center = t.data + (3 * (y * t.width + x));
        struct color rgb = {*center, *(center+1), *(center+2)};
        return rgb;
    }
    struct color rgb = {0,0,0};
    return rgb;
}

bool isValidTexture(struct planeTexture t)
{
    return t.data != 0;
}