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