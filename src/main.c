#include "art_3d.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

#define SCALE 300
#define WIDTH 640
#define HEIGHT 480
#define BRIGHTNESS 6
#define FPS 60

#define PI M_PI

#define DEBUG false

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void clearScreen();
void putPixel(int, int, ART_AnalogColor);
void render(int);
void raytrace();
void debug();

int main()
{
    if (DEBUG)
        debug();
    else
        raytrace();
    return 0;
}

void debug()
{
    ART_AnalogColor c = hslToAnalog(183, 4, 63);
    // printDC(makeDrawable(c));
    printAC(c);
}

void raytrace()
{
    window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;

    int frame = 0;

    while (running)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;
        }

        clearScreen();
        render(frame);  

        SDL_RenderPresent(renderer);
        frame++;
        // SDL_Delay(1/FPS);
    }
}


void putPixel(int x, int y, ART_AnalogColor c)
{
    struct drawableColor dc = makeDrawable(c);
    unsigned int r = dc.r, g = dc.g, b = dc.b;
    SDL_SetRenderDrawColor(renderer, r,g,b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void render(int frame)
{
    int numPlanes = 6;
    ART_Plane planes[] = {
        {SCALE, scalarpv3(K_HAT,-1), {0,0,6}, PI/4, planeTextureFromFile("assets/ceiling.jpg")},
        {SCALE, scalarpv3(I_HAT, -1), {10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, I_HAT, {-10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, scalarpv3(J_HAT, -1), {0,10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, J_HAT, {0,-10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, K_HAT, {0,0,-3}, PI/4, planeTextureFromFile("assets/floor.jpg")}
    };

    int numSpheres = 3;
    ART_Sphere spheres[] = {
        {SCALE, {5, 0, -2}, 1, {1, 0.1, 0.1}},
        {SCALE, {7, 2, -2}, 1, {0.1, 1, 0.1}},
        {{SCALE}, {3, -2, -2}, 1, {0.1, 0.1, 1}},
        {{SCALE}, {5, 3, -2.8}, 0.2, {0.8, 0.2, 0.8}}
    };

    int numTris = 6;
    ART_Tri tris[] = {
        // front
        triFromVerticies(SCALE, vector3(4, -4, -1), vector3(4, -2, -1), vector3(4, -2, -3), true, art_analogColor(0.5, 0.1, 0.5)),
        triFromVerticies(SCALE, vector3(4, -4, -1), vector3(4, -4, -3), vector3(4, -2, -3), false, art_analogColor(0.5, 0.1, 0.5)),
        // right
        triFromVerticies(SCALE, vector3(4, -2, -1), vector3(6, -2, -1), vector3(6, -2, -3), true, art_analogColor(0.5, 0.1, 0.5)),
        triFromVerticies(SCALE, vector3(4, -2, -1), vector3(4, -2, -3), vector3(6, -2, -3), false, art_analogColor(0.5, 0.1, 0.5)),
        // top
        triFromVerticies(SCALE, vector3(4, -4, -1), vector3(4, -2, -1), vector3(6, -2, -1), false, art_analogColor(0.5, 0.1, 0.5)),
        triFromVerticies(SCALE, vector3(4, -4, -1), vector3(6, -4, -1), vector3(6, -2, -1), true, art_analogColor(0.5, 0.1, 0.5)),
    };

    int numLightSources = 5;
    float ls1b = 2;
    int lh = 20, ll = 90;
    ART_LightSource lightSources[] = {
        art_lightSource(vector3(2.3, 0.3, 4.5), ls1b, lh, ll),
        art_lightSource(vector3(2.3, -0.3, 4.5), ls1b, lh, ll),
        art_lightSource(vector3(2,0.3,4.5), ls1b, lh, ll),
        art_lightSource(vector3(2.15,0,4.5), ls1b, lh, ll),
        art_lightSource(vector3(2,-0.3,4.5), ls1b, lh, ll),
        art_lightSource(vector3(9.8,3,0), 0.1, 180, 50),
    };

    ART_Vector3 camera = {0, 0, 0};
    ART_Vector3 screenPos = {camera.x+0.7, 0, 0};

    float roll = 0;
    float pitch = 0;
    float yaw = frame*PI/512;

    ART_Intersection intersections[numSpheres + numPlanes + numTris];
    int mindex = -1;
    ART_Intersection mintersection;
    ART_Vector3 minormal;
    ART_Vector3 light_dir;

    float d, b, lt;
    bool shadow = false;


    for (int i = 0; i < HEIGHT; i++)
    {
        screenPos.z = ((float)(-i + (HEIGHT/2)))/(HEIGHT/2);
        for (int j = 0; j < WIDTH; j++)
        {

            screenPos.y = ((float)(j - (WIDTH/2)))/(WIDTH/2);
            ART_AnalogColor c = {0,0,0};
            ART_Vector3 origin = camera;
            ART_Vector3 dir = {screenPos.x-camera.x, screenPos.y+camera.y, screenPos.z+camera.z};

            // adjust camera rotation
            dir = rotatev3(I_HAT, dir, roll);
            dir = rotatev3(J_HAT, dir, pitch);
            dir = rotatev3(K_HAT, dir, yaw);

            // ====== GLOBAL ILLUMINATION ======
            mindex = -1;

            // find shortest intersection between ray and plane
            for (int p = 0; p < numPlanes; p++)
            {
                intersections[p] = planeIntersection(planes[p], camera, dir);
                if (intersections[p].t > 0 && (mindex == -1 || intersections[p].t < intersections[mindex].t))
                {
                    mindex = p;
                    minormal = planeNormalAt(planes[p], intersections[mindex].pos);
                }
            }

            // find shortest intersection between ray and sphere
            for (int s = 0; s < numSpheres; s++)
            {
                intersections[numPlanes + s] = sphereIntersection(spheres[s], camera, dir);
                if (intersections[numPlanes + s].t > 0 && (mindex == -1 || intersections[numPlanes + s].t < intersections[mindex].t))
                    {
                        mindex = numPlanes + s;
                        minormal = sphereNormalAt(spheres[s], intersections[mindex].pos);
                    }
            }

            // find shortest intersection between ray and tri
            for (int t = 0; t < numTris; t++)
            {
                intersections[numPlanes+numSpheres+t] = triIntersection(tris[t], camera, dir);
                if (intersections[numPlanes+numSpheres+t].t > 0 && (mindex == -1 || intersections[numPlanes+numSpheres+t].t < intersections[mindex].t))
                {
                    mindex = numPlanes + numSpheres + t;
                    minormal = triNormalAt(tris[t], intersections[mindex].pos);
                }
            }
            
            // no intersection with scene
            if (mindex == -1)
                continue;
            
            mintersection = intersections[mindex];
            d = absv3(subv3(mintersection.pos, origin));
            d /= BRIGHTNESS;
            if (mindex >= numPlanes+numSpheres)
                c = triColorAt(tris[mindex-(numPlanes+numSpheres)], mintersection.pos);
            else if (mindex >= numPlanes)
                c = sphereColorAt(spheres[mindex-numPlanes], mintersection.pos);
            else if (mindex >= 0)
                c = planeColorAt(planes[mindex], mintersection.pos);
            c = scaleBrightness(c, BRIGHTNESS*0.05);

            // ====== LOCAL ILLUMINATION ======
            for (int l = 0; l < numLightSources; l++)
            {
                light_dir = subv3(lightSources[l].pos, mintersection.pos);
                shadow = false;
                for (int p = 0; p < numPlanes && !shadow; p++)
                {
                    lt = planeIntersection(planes[p], mintersection.pos, light_dir).t;
                    shadow = lt > 0.000001 && lt < 1;    // object in shadow if the ray between the point and the light source is blocked
                }
                for (int s = 0; s < numSpheres && !shadow; s++)
                {
                    lt = sphereIntersection(spheres[s], mintersection.pos, light_dir).t;
                    shadow = lt > 0.000001 && lt < 1;
                }
                for (int t = 0; t < numTris && !shadow; t++)
                {
                    lt = triIntersection(tris[t], mintersection.pos, light_dir).t;
                    shadow = lt > 0.000001 && lt < 1;
                }
                if (!shadow)
                {
                    d = absv3(light_dir);
                    // brighten color based on inverse square law and difference in direction between ray and surface normal
                    b = dotpv3(light_dir, minormal);
                    c = scaleBrightness(c, 1+b*lightSources[l].luminosity/(d*d));
                    c = sourceTint(c, lightSources[l], d);
                }
            }

            putPixel(j, i, c);
        }
    }
}