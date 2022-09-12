#include <math.h>
#include <stdio.h>
#include "vector3.h"

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

struct vector3 rotatev3(struct vector3 n, struct vector3 v, float t)
{
    n = normv3(n);
    return addv3(addv3(scalarpv3(n, dotpv3(n,v)), crosspv3(scalarpv3(crosspv3(n,v), cosf(t)), n)), scalarpv3(crosspv3(n,v), sinf(t)));
}

struct vector3 reflectv3(struct vector3 n, struct vector3 v)
{
    return subv3(v, scalarpv3(n, 2*dotpv3(v,n)));
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
