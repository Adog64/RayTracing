#pragma once

struct vector3
{
    float x, y, z;
};

static const struct vector3 I_HAT = {1,0,0};
static const struct vector3 J_HAT = {0,1,0};
static const struct vector3 K_HAT = {0,0,1};

// x = length of vector v
float absv3(struct vector3 v);

// direction unit vector of v
struct vector3 normv3(struct vector3 v);

// w = u + v
struct vector3 addv3(struct vector3 u, struct vector3 v);

// w = u - v
struct vector3 subv3(struct vector3 u, struct vector3 v);

// x = u dot v
float dotpv3(struct vector3 u, struct vector3 v);

// x = u cross v
struct vector3 crosspv3(struct vector3 u, struct vector3 v);

// w = xv
struct vector3 scalarpv3(struct vector3 v, float x);

// some vector orthogonal to v
struct vector3 orthov3(struct vector3 v);

// w is v rotated around n by angle t
struct vector3 rotatev3(struct vector3 n, struct vector3 v, float t);

// w is v reflected off of plane with normal n
struct vector3 reflectv3(struct vector3 n, struct vector3 v);

// construct and return a vector {x, y, z}
struct vector3 vector3(float x, float y, float z);

// print vector to console
void printv3(struct vector3 v);

float absv3(struct vector3 v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

struct vector3 normv3(struct vector3 v)
{
    float l = absv3(v);
    struct vector3 n;
    n.x = v.x/l;
    n.y = v.y/l;
    n.z = v.z/l;
    return n;
}

struct vector3 addv3(struct vector3 u, struct vector3 v)
{
    struct vector3 w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    return w;
}

struct vector3 subv3(struct vector3 u, struct vector3 v)
{
    struct vector3 w;
    w.x = u.x - v.x;
    w.y = u.y - v.y;
    w.z = u.z - v.z;
    return w;
}

float dotpv3(struct vector3 u, struct vector3 v)
{
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

struct vector3 crosspv3(struct vector3 u, struct vector3 v)
{
    struct vector3 w;
    w.x = u.y*v.z - u.z*v.y;
    w.y = u.z*v.x - u.x*v.z;
    w.z = u.x*v.y - u.y*v.x;
    return w;
}

struct vector3 scalarpv3(struct vector3 v, float x)
{
    struct vector3 w;
    w.x = v.x*x;
    w.y = v.y*x;
    w.z = v.z*x;
    return w;
}

struct vector3 orthov3(struct vector3 v)
{
    struct vector3 w[] = {{v.z, v.z, -v.x-v.y}, {-v.y-v.z, v.x, v.x}};
    return w[(v.z != 0 && -v.x != v.y)];
}

struct vector3 rotatev3(struct vector3 n, struct vector3 v, float t)
{
    n = normv3(n);
    return addv3(addv3(scalarpv3(n, dotpv3(n,v)), crosspv3(scalarpv3(crosspv3(n,v), cosf(t)), n)), scalarpv3(crosspv3(n,v), sinf(t)));
}

struct vector3 reflectv3(struct vector3 n, struct vector3 v)
{
    return subv3(v, scalarpv3(n, 2*dotpv3(v,n)));
}

struct vector3 vector3(float x, float y, float z)
{
    struct vector3 v3 = {x, y, z};
    return v3;
}

void printv3(struct vector3 v)
{
    printf("[");
    printf("%f", v.x);
    printf(", ");
    printf("%f", v.y);
    printf(", ");
    printf("%f", v.z);
    printf("]\n");
}
