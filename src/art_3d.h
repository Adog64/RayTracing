// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                              ADog64's Ray Tracing 3D Object Library                               ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝
// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                               *** Section 1: Vector Functions ***                                 ║
// ╠════════════════════╦════════════════════════════════════╦═════════════════════════════════════════╣
// ║      Function      ║             Description            ║              Parameter List             ║
// ╠════════════════════╬════════════════════════════════════╬═════════════════════════════════════════╣
// ║ absv3              ║ Magnitude of vector                ║ ART_Vector3                             ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ normv3             ║ Unit direction vector              ║ ART_Vector3                             ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ addv3              ║ Vector sum of 2 vectors            ║ ART_Vector3, ART_Vector3                ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ subv3              ║ Vector difference of 2 vectors     ║ ART_Vector3, ART_Vector3                ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ dotpv3             ║ Float dot product of 2 vectors     ║ ART_Vector3, ART_Vector3                ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ crosspv3           ║ Cross product of 2 vectors         ║ ART_Vector3, ART_Vector3                ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ scalarpv3          ║ Scale a vector by a scalar         ║ ART_Vector3, float                      ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ orthov3            ║ Calculate some orthoganal vector   ║ ART_Vector3                             ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ rotatev3           ║ Rotate a vector around another     ║ ART_Vector3, ART_Vector3, float         ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ reflectv3          ║ Reflect a vector over another      ║ ART_Vector3, ART_Vector3                ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ vector3            ║ Create a 3D vector <x, y, z>       ║ float, float, float                     ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ printv3            ║ Print vector <x, y, z> to console  ║ ART_Vector3                             ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ printlnv3          ║ Print vector to console + linefeed ║ ART_Vector3                             ║
// ╚════════════════════╩════════════════════════════════════╩═════════════════════════════════════════╝
// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                               *** Section 2: Color Functions ***                                  ║
// ╠════════════════════╦════════════════════════════════════╦═════════════════════════════════════════╣
// ║      Function      ║             Description            ║              Parameter List             ║
// ╠════════════════════╬════════════════════════════════════╬═════════════════════════════════════════╣
// ║ hslToAnalog        ║ HSL to analog RGB                  ║ int, int, int                           ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ makeDrawable       ║ Analog RGB to 24-Bit RGB           ║ ART_AnalogColor                         ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ sourceTint         ║ Tint a point from a light source   ║ ART_AnalogColor, ART_LightSource, float ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ printDC            ║ Print 24-Bit color (R, G, B)       ║ ART_DrawableColor                       ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ printAC            ║ Print analog RGB (R, G, B)         ║ ART_AnalogColor                         ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ analogColor        ║ Make a new analog RGB color        ║ float, float, float                     ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ scaleBrightness    ║ Brighten or dim a color by percent ║ ART_AnalogColor, float                  ║
// ╚════════════════════╩════════════════════════════════════╩═════════════════════════════════════════╝
// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                             *** Section 3: 3D Object Functions ***                                ║
// ╠════════════════════╦════════════════════════════════════╦═════════════════════════════════════════╣
// ║      Function      ║             Description            ║              Parameter List             ║
// ╠════════════════════╬════════════════════════════════════╬═════════════════════════════════════════╣
// ║ getTextureFromFile ║ Get a texture from a jpeg file     ║ char*                                   ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ planeIntersection  ║ Intersection between ray and plane ║ ART_Plane, ART_Vector3, ART_Vector3     ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ planeColort        ║ Color on a plane at a point in ℝ3  ║ ART_Plane, ART_Vector3                  ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ planeNormalAt      ║ Normal of a plane at a point in ℝ3 ║ ART_Plane, ART_Vector3                  ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ sphereIntetsection ║ Ray-Sphere intersection            ║ ART_Sphere, ART_Vector3, ART_Vector3    ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ sphereColor        ║ Color of sphere at a point in ℝ3   ║ ART_Sphere, ART_Vector3                 ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ sphereNormal       ║ Normal of sphere at a point in ℝ3  ║ ART_Sphere, ART_Vector3                 ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ triFromVerticies   ║ New ART_tri from 3 verticies       ║ ART_Vector3, ART_Vector3, ART_Vector3   ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ triIntersection    ║ Intersection between ray and tri   ║ ART_Tri, ART_Vector3, ART_Vector3       ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ triNormalAt        ║ Normal of tri at a point in ℝ3     ║ ART_Tri, ART_Vector3                    ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ triColorAt         ║ Color of tri at point in ℝ3        ║ ART_Tri, ART_Vector3                    ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ art_lightSource    ║ Create a point light source        ║ ART_Vector3, float, int, int            ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ sampleTextureAt    ║ Sample a texture at relative point ║ ART_Texture, int, int int               ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ isValidTexture     ║ Check if a texture is valid        ║ ART_Texture                             ║
// ╚════════════════════╩════════════════════════════════════╩═════════════════════════════════════════╝
// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                               *** Section 4: Utility Functions ***                                ║
// ╠════════════════════╦════════════════════════════════════╦═════════════════════════════════════════╣
// ║ Function           ║             Description            ║              Parameter List             ║
// ╠════════════════════╬════════════════════════════════════╬═════════════════════════════════════════╣
// ║ min                ║ returns the lesser of two ints     ║ int, int                                ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ max                ║ returns the greater of two ints    ║ int, int                                ║
// ╚════════════════════╩════════════════════════════════════╩═════════════════════════════════════════╝
// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                               *** Section N: XXXXX Functions ***                                  ║
// ╠════════════════════╦════════════════════════════════════╦═════════════════════════════════════════╣
// ║ Function           ║             Description            ║              Parameter List             ║
// ╠════════════════════╬════════════════════════════════════╬═════════════════════════════════════════╣
// ║ ║ ║ ║
// ╟────────────────────╫────────────────────────────────────╫─────────────────────────────────────────╢
// ║ ║ ║ ║
// ╚════════════════════╩════════════════════════════════════╩═════════════════════════════════════════╝

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                                        ** I Custom Types **                                       ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝

typedef struct art_vector3
{
    float x, y, z;
}ART_Vector3;

/// @brief Floating-point RGB of the form: ((0f-1f), (0f, 1f), (0f, 1f)).
typedef struct art_analogColor
{
    float r, g, b;
}ART_AnalogColor;

/// @brief 24-Bit RGB color.
typedef struct drawableColor
{
    unsigned int r, g, b;
}ART_DrawableColor;

/// @brief Image texture for texture mapping (Currently only used by planes)
typedef struct art_texture
{
    int width, height, channels;
    unsigned char *data;
}ART_Texture;

typedef struct art_plane
{
    float scale;
    ART_Vector3 normal;
    ART_Vector3 center;
    float rotation;
    ART_Texture texture;
}ART_Plane;

typedef struct art_sphere
{
    float scale;
    ART_Vector3 center;
    float radius;
    ART_AnalogColor color;
}ART_Sphere;

/// @brief 3D Triangle defined by 3 verticies. IMPORTANT: To avoid surface problems, please ONLY initialize with constructor function.
typedef struct art_tri
{
    float scale;
    ART_Vector3 p[3];
    ART_Vector3 normal;
    ART_AnalogColor color;
}ART_Tri;

typedef struct art_lightSource
{
    ART_Vector3 pos;
    float luminosity;
    int hue;
    int lightness;
}ART_LightSource;

typedef struct art_intersection
{
    ART_Vector3 pos;
    float t;
}ART_Intersection;

// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                                     ** II Utility Constants **                                    ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝

// Axis unit vectors
static const ART_Vector3 I_HAT = {1,0,0};
static const ART_Vector3 J_HAT = {0,1,0};
static const ART_Vector3 K_HAT = {0,0,1};
static const ART_Vector3 MINUS_I_HAT = {-1,0,0};
static const ART_Vector3 MINUS_J_HAT = {0,-1,0};
static const ART_Vector3 MINUS_K_HAT = {0,0,-1};

// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                               *** Section 1: Vector Functions ***                                 ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝

/// @return Magnitude of vector v.
float absv3(ART_Vector3 v);

/// @return Direction vector of vector v.
ART_Vector3 normv3(ART_Vector3 v);

/// @brief u + v
/// @return Vector sum of u and v.
ART_Vector3 addv3(ART_Vector3 u, ART_Vector3 v);

/// @brief u - v
/// @return Vector difference of u and v.
ART_Vector3 subv3(ART_Vector3 u, ART_Vector3 v);

/// @brief (u ⋅ v)
/// @return Dot product of u and v.
float dotpv3(ART_Vector3 u, ART_Vector3 v);

/// @brief (u ✕ v)
/// @return Cross product of u and v
ART_Vector3 crosspv3(ART_Vector3 u, ART_Vector3 v);

/// @brief Scale a vector by a scalar.
/// @param v vector
/// @param x scalar
/// @return x(v)
ART_Vector3 scalarpv3(ART_Vector3 v, float x);

/// @brief Create a vector such that its dot product with v is 0.
/// @param v Initial direction
/// @return A vector orthogonal to v with the same magnitude.
ART_Vector3 orthov3(ART_Vector3 v);

/// @brief Rotate a vector around an arbitray axis.
/// @param n Axis direction vector
/// @param v Rotated vector
/// @param t Angle in radians
/// @return v rotated around n by angle t
ART_Vector3 rotatev3(ART_Vector3 n, ART_Vector3 v, float t);

/// @brief Reflect v off of a surface following ∠Incedence = ∠Reflection.
/// @param n Normal of reflector surface
/// @param v Incoming vector
/// @return The reflected vector.
ART_Vector3 reflectv3(ART_Vector3 n, ART_Vector3 v);

/// @brief Construct and return a vector <x, y, z>.
ART_Vector3 vector3(float x, float y, float z);

/// @brief Print <v.x, v.y, v.z> to console.
void printv3(ART_Vector3 v);

/// @brief Print <v.x, v.y, v.z> to console and carraige return line feed. 
void printlnv3(ART_Vector3 v);

// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                               *** Section 2: Color Functions ***                                  ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝

/// @brief Convert hue and lightness to analog rgb.
/// @param hue integer hue on the range: (0, 360)
/// @param saturation integer saturation on the range (0, 100)
/// @param lightness integer lightess on the range (0, 100)
/// @return Analog rgb color with equivalent hue and lightness
ART_AnalogColor hslToAnalog(int hue, int saturation, int lightness);

/// @brief Convert analog color to 24-bit drawable color.
ART_DrawableColor makeDrawable(ART_AnalogColor c);

/// @brief Tint an object at a point based on light source distance.
/// @param c Initail analog color
/// @param l Light source providing tint
/// @param d Distancee between tinted point and light source
/// @return Tinted analog color
ART_AnalogColor sourceTint(ART_AnalogColor c, ART_LightSource l, float d);

/// @brief Print a 24-Bit color (R, G, B).
/// @param c color to print
void printDC(ART_DrawableColor c);

/// @brief Print an analog RGB color (R, G, B).
/// @param c color to print
void printAC(ART_AnalogColor c);

/// @brief Make an analog RGB color.
/// @param r red color channel on the range (0f, 1f)
/// @param g green color channel on the range (0f, 1f)
/// @param b blue color channel on the range (0f, 1f)
/// @return New analog RGB color from defined values
ART_AnalogColor art_analogColor(float r, float g, float b);

/// @brief Scale color by brightness.
/// @param c color to scale
/// @param brightness percent brightness (1 does not change color)
/// @return scaled color
ART_AnalogColor scaleBrightness(ART_AnalogColor c, float brightness);

// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                             *** Section 3: 3D Object Functions ***                                ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝

/// @brief Create a helpful texture struct from a jpeg file.
/// @param path path of image file starting at directory of executeable
/// @return Newly constructed texture
ART_Texture getTextureFromFile(char *path);

/// @brief Find the point of intersection between a plane and a ray.
/// @param p plane
/// @param rayOrigin position vector of ray 
/// @param rayDirection direction vector of ray
/// @return Intersection defined by position vector and parametric t
ART_Intersection planeIntersection(ART_Plane p, ART_Vector3 rayOrigin, ART_Vector3 rayDirection);

/// @brief Texturemapped color of a plane at a point in ℝ3.
/// @param p plane to get color from
/// @param pos point in ℝ3; must be on the plane
/// @return analog color of plane at point
ART_AnalogColor planeColorAt(ART_Plane p, ART_Vector3 pos);

/// @brief Get the normal of a plane.
/// @param p plane in question
/// @param pos position to get normal at in ℝ3
/// @return normal vector of the plane
ART_Vector3 planeNormalAt(ART_Plane p, ART_Vector3 pos);

/// @brief Intersection between a ray and a sphere.
/// @param s sphere in question
/// @param rayOrigin position vector of ray
/// @param rayDirection direction vector of ray
/// @return position and parametric solution, t, of intersection
ART_Intersection sphereIntersection(ART_Sphere s, ART_Vector3 rayOrigin, ART_Vector3 rayDirection);

/// @brief Color of sphere at a point in ℝ3.
/// @param s sphere in question
/// @param pos point in ℝ3; must be on the sphere
/// @return analog color of sphere at point
ART_AnalogColor sphereColorAt(ART_Sphere s, ART_Vector3 pos);

/// @brief Normal of sphere at point in ℝ3.
/// @param s sphere in question
/// @param pos point in ℝ3; must be on the sphere
/// @return normal vector of sphere at point
ART_Vector3 sphereNormalAt(ART_Sphere s, ART_Vector3 pos);

/// @brief Create a tri from 3 verticies.
/// @param scale scale of texturing
/// @param p0 first vertex
/// @param p1 second vertex
/// @param p2 third vertex
/// @param inverted whether or not to invert the normal
/// @param c analog color of triangle
/// @return newly created triangle
ART_Tri triFromVerticies(float scale, ART_Vector3 p0, ART_Vector3 p1, ART_Vector3 p2, bool inverted, ART_AnalogColor c);

/// @brief Intersection between a ray and tri.
/// @param t triangle in question
/// @param rayOrigin ray position vector
/// @param rayDirection ray direction vector
/// @return Position of intersection and parametric t
ART_Intersection triIntersection(ART_Tri t, ART_Vector3 rayOrigin, ART_Vector3 rayDirection);

/// @brief Get the color of a tri.
/// @param t tri in question
/// @param pos point in ℝ3; must be on the tri
/// @return color of at point
ART_AnalogColor triColorAt(ART_Tri t, ART_Vector3 pos);

/// @brief Get the normal of a tri at a point in ℝ3.
/// @param t triangle in question
/// @param pos 
/// @return 
ART_Vector3 triNormalAt(ART_Tri t, ART_Vector3 pos);

/// @brief Create a new light source.
/// @param pos position of light source
/// @param luminosity brightness
/// @param hue color
/// @param lightness 
/// @return newly constructed light source
ART_LightSource art_lightSource(ART_Vector3 pos, float luminosity, int hue, int lightness);

/// @brief Sample a color from a texture from a pixel or aveage a square of pixels.
/// @param t texture to sample
/// @param x x-coordinate of center of sample
/// @param y y-coordinate of center of sample
/// @param aa radius of sampling square - 0 to sample only one pixel
/// @return Analog RGB color of pixel sampled
ART_AnalogColor sampleTextureAt(ART_Texture t, int x, int y, int aa);

/// @brief Check if a texture is valid.
/// @param t texture to validate
bool isValidTexture(ART_Texture t);

// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                               *** Section 4: Helper Functions ***                                 ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝

/// @brief Lesser of two evils (ints).
/// @return integer minimum
int min(int a, int b);

/// @brief Bigger is better.
/// @return integer maximum
int max(int a, int b);

// ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
// ║                              ** FOR NERDS: Function Definitions **                                ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝

float absv3(ART_Vector3 v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

ART_Vector3 normv3(ART_Vector3 v)
{
    float l = absv3(v);
    ART_Vector3 n;
    n.x = v.x/l;
    n.y = v.y/l;
    n.z = v.z/l;
    return n;
}

ART_Vector3 addv3(ART_Vector3 u, ART_Vector3 v)
{
    ART_Vector3 w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    return w;
}

ART_Vector3 subv3(ART_Vector3 u, ART_Vector3 v)
{
    ART_Vector3 w;
    w.x = u.x - v.x;
    w.y = u.y - v.y;
    w.z = u.z - v.z;
    return w;
}

float dotpv3(ART_Vector3 u, ART_Vector3 v)
{
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

ART_Vector3 crosspv3(ART_Vector3 u, ART_Vector3 v)
{
    ART_Vector3 w;
    w.x = u.y*v.z - u.z*v.y;
    w.y = u.z*v.x - u.x*v.z;
    w.z = u.x*v.y - u.y*v.x;
    return w;
}

ART_Vector3 scalarpv3(ART_Vector3 v, float x)
{
    ART_Vector3 w;
    w.x = v.x*x;
    w.y = v.y*x;
    w.z = v.z*x;
    return w;
}

ART_Vector3 orthov3(ART_Vector3 v)
{
    ART_Vector3 w[] = {{v.z, v.z, -v.x-v.y}, {-v.y-v.z, v.x, v.x}};
    return w[(v.z != 0 && -v.x != v.y)];
}

ART_Vector3 rotatev3(ART_Vector3 n, ART_Vector3 v, float t)
{
    n = normv3(n);
    return addv3(addv3(scalarpv3(n, dotpv3(n,v)), crosspv3(scalarpv3(crosspv3(n,v), cosf(t)), n)), scalarpv3(crosspv3(n,v), sinf(t)));
}

ART_Vector3 reflectv3(ART_Vector3 n, ART_Vector3 v)
{
    return subv3(v, scalarpv3(n, 2*dotpv3(v,n)));
}

ART_Vector3 vector3(float x, float y, float z)
{
    ART_Vector3 v3 = {x, y, z};
    return v3;
}

void printv3(ART_Vector3 v)
{
    printf("<%f, %f, %f>", v.x, v.y, v.z);
}

void printlnv3(ART_Vector3 v)
{
    printf("<%f, %f, %f>\n", v.x, v.y, v.z);
}

ART_AnalogColor sourceTint(ART_AnalogColor c, ART_LightSource l, float d)
{
    ART_AnalogColor c1 = hslToAnalog(l.hue, 100, l.lightness);
    float b0 = sqrtf(c.r*c.r + c.g*c.g + c.b*c.b);
    c.r = c.r + c.r*c1.r;
    c.g = c.g + c.g*c1.g;
    c.b = c.b + c.b*c1.b;
    b0 /= sqrtf(c.r*c.r + c.g*c.g + c.b*c.b) * d*d;
    c.r *= b0;
    c.g *= b0;
    c.b *= b0;
    return c;
}

void printAC(ART_AnalogColor c)
{
    printf("(%f, %f, %f)", c.r, c.g, c.b);
}

void printDC(ART_DrawableColor c)
{
    printf("(%d, %d, %d)", c.r, c.g, c.b);
}

ART_AnalogColor art_analogColor(float r, float g, float b)
{
    ART_AnalogColor c = {r, g, b};
    return c;
}

ART_DrawableColor makeDrawable(ART_AnalogColor c)
{
    ART_DrawableColor dc = {
        min(255, max(0, (int)(255*c.r))),
        min(255, max(0, (int)(255*c.g))),
        min(255, max(0, (int)(255*c.b)))
    };
    return dc;
}

ART_AnalogColor scaleBrightness(ART_AnalogColor c, float brightness)
{
    return art_analogColor(c.r*brightness, c.g*brightness, c.b*brightness);
}

ART_AnalogColor hslToAnalog(int hue, int saturation, int lightness)
{
    ART_AnalogColor c;
    float s = saturation / 100.0;
    float l = lightness / 100.0;
    
    if (saturation == 0)
    {
        c.r = c.g = c.b = l;
    }
    else
    {

        float v1 = (l < 0.5) ? l*(1 + s) : l+s - l*s;
        float v2 = 2*l - v1;
        // hue conversion
        c.r = fmin(fmax(-(fabs(((hue-180)%360+360)%360 - 180)/60.0) + 2, 0), 1);
        c.g = fmin(fmax(-(fabs(((hue-300)%360+360)%360 - 180)/60.0) + 2, 0), 1);
        c.b = fmin(fmax(-(fabs(((hue- 60)%360+360)%360 - 180)/60.0) + 2, 0), 1);
        // lightness conversion
        c.r = (l >= .5)*(2*(l - l*c.r + c.r) - 1) + (l < 0.5)*(2*c.r*l);
        c.g = (l >= .5)*(2*(l - l*c.g + c.g) - 1) + (l < 0.5)*(2*c.g*l);
        c.b = (l >= .5)*(2*(l - l*c.b + c.b) - 1) + (l < 0.5)*(2*c.b*l);
        // saturation conversion
        c.r = (c.r - l)*s + l;
        c.g = (c.g - l)*s + l;
        c.b = (c.b - l)*s + l;
    }
    return c;
}


ART_Texture planeTextureFromFile(char *path)
{
    ART_Texture t;
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

ART_Intersection planeIntersection(ART_Plane p, ART_Vector3 rayOrigin, ART_Vector3 rayDirection)
{
    // ========== RAY PARAMETRIC ==========
    // / x = rayOrigin.x + rayDirection.x*t
    // { y = rayOrigin.y + rayDirection.y*t
    // \ z = rayOrigin.z + rayDirection.z*t
    //
    // ========== PLANE EQUATION ==========
    // (x-center.center.x) + (y-center.center.y) + (z-center.center.z) = 0
    ART_Intersection is;
    float l1 = dotpv3(p.normal, subv3(p.center, rayOrigin));
    float l2 = dotpv3(p.normal, rayDirection);
    is.t = (l2 != 0) ? l1/l2 : -1;

    is.pos = scalarpv3(rayDirection, is.t);
    return is;
}

ART_AnalogColor planeColorAt(ART_Plane p, ART_Vector3 pos)
{
    ART_AnalogColor c = {0, 0, 0};
    
    if (isValidTexture(p.texture))
    {
        // some vector in the plane by the plane rotation around plane center
        ART_Vector3 planeUV1 = rotatev3(p.normal, normv3(orthov3(p.normal)), p.rotation);
        ART_Vector3 planeUV2 = crosspv3(p.normal, planeUV1);
        
        ART_Vector3 f = scalarpv3(addv3(p.center, pos), p.scale);
        int xPos = (((int)(dotpv3(f, planeUV1)*200/p.scale)) % (p.texture.width-1) + (p.texture.width-1)) % (p.texture.width-1);
        int yPos = (((int)(dotpv3(f, planeUV2)*200/p.scale)) % (p.texture.height-1) + (p.texture.height-1)) % (p.texture.height-1);
        c = sampleTextureAt(p.texture, xPos, yPos, 3);
    }
    return c;
}

ART_Vector3 planeNormalAt(ART_Plane p, ART_Vector3 pos)
{
    return p.normal;
}

ART_Intersection sphereIntersection(ART_Sphere s, ART_Vector3 rayOrigin, ART_Vector3 rayDirection)
{
    ART_Intersection i = {{0,0,0}, -1};
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

ART_Vector3 sphereNormalAt(ART_Sphere s, ART_Vector3 pos)
{
    return normv3(subv3(pos, s.center));
}

ART_AnalogColor sphereColorAt(ART_Sphere s, ART_Vector3 pos)
{
    return s.color;
}

ART_Intersection triIntersection(ART_Tri t, ART_Vector3 rayOrigin, ART_Vector3 rayDirection)
{
    ART_Intersection is;
    ART_Vector3 E1 = subv3(t.p[1], t.p[0]);
    ART_Vector3 E2 = subv3(t.p[2], t.p[0]);
    ART_Vector3 N = crosspv3(E1, E2);
    float invdet = -1.0/dotpv3(rayDirection, N);    
    ART_Vector3 AO = subv3(rayOrigin, t.p[0]);
    ART_Vector3 DAO = crosspv3(AO, rayDirection);
    float u = dotpv3(E2, DAO) * invdet;
    float v = -dotpv3(E1, DAO) * invdet;
    is.t = (u >= -1e-5 && v >= -1e-5 && u+v <= 1+1e-5) ? dotpv3(AO, N) * invdet : -1;
    is.pos = addv3(rayOrigin, scalarpv3(rayDirection, is.t));
    return is;
}

ART_Tri triFromVerticies(float scale, ART_Vector3 p0, ART_Vector3 p1, ART_Vector3 p2, bool inverted, ART_AnalogColor c)
{
    ART_Tri t;
    t.scale = scale;
    t.p[0] = p0;
    t.p[1] = p1;
    t.p[2] = p2;
    t.normal = (inverted) ? crosspv3(subv3(t.p[1], t.p[0]), subv3(t.p[2], t.p[0])) : crosspv3(subv3(t.p[2], t.p[0]), subv3(t.p[1], t.p[0]));
    t.normal = normv3(t.normal);
    t.color = c;
    return t;
}

ART_AnalogColor triColorAt(ART_Tri t, ART_Vector3 pos)
{
    return t.color;
}

ART_Vector3 triNormalAt(ART_Tri t, ART_Vector3 pos)
{
    return t.normal;
}

ART_LightSource art_lightSource(ART_Vector3 pos, float luminosity, int hue, int lightness)
{
    ART_LightSource ls;
    ls.pos = pos;
    ls.luminosity = luminosity;
    ls.hue = hue;
    ls.lightness = lightness;
    return ls;
}

ART_AnalogColor sampleTextureAt(ART_Texture t, int x, int y, int aa)
{
    int colors = 0;
    ART_AnalogColor rgb = {0,0,0};
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
        rgb.r /= colors*255.0;
        rgb.g /= colors*255.0;
        rgb.b /= colors*255.0;
    }
    return rgb;
}

bool isValidTexture(ART_Texture t)
{
    return t.data != 0;
}

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int max(int a, int b)
{
    return (a < b) ? b : a;
}