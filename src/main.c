#include "vector3.h"
#include "scene_objs.h"
#include "colors.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

#define SCALE 300
#define WIDTH 640
#define HEIGHT 480
#define BRIGHTNESS 1
#define FPS 60

#define PI M_PI

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void clearScreen();
void putPixel(int, int, struct color);
void render(int);

int main()
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
    return 0;
}

void putPixel(int x, int y, struct color c)
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
    struct plane planes[] = {
        {SCALE, K_HAT, {0,0,7}, PI/4, planeTextureFromFile("assets/ceiling.jpg")},
        {SCALE, I_HAT, {10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, I_HAT, {-10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, J_HAT, {0,10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, J_HAT, {0,-10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, K_HAT, {0,0,-3}, PI/4, planeTextureFromFile("assets/floor.jpg")}
    };

    int numSpheres = 2;
    struct sphere spheres[] = {
        {SCALE, {5, 0, -2}, 1, {255, 20, 20}},
        {SCALE, {7, 2, -2}, 1, {20, 255, 20}}
    };

    int numLightSources = 5;
    struct lightSource lightSources[] = {
        {{0.3,0.3,4.5}, 7},
        {{0.3,-0.3,4.5}, 7},
        {{0,0.3,4.5}, 7},
        {{0.15,0,4.5}, 7},
        {{0,-0.3,4.5}, 7}
    };

    struct vector3 camera = {0, 0, 0};
    struct vector3 screenPos = {camera.x+1, 0, 0};

    float roll = 0;
    float pitch = 0;
    float yaw = 0*(PI/256);

    struct intersection intersections[numSpheres + numPlanes];
    int mindex = -1;
    struct intersection mintersection;
    struct vector3 minormal;
    struct vector3 light_dir;

    float d, b, t;
    bool shadow = false;


    for (int i = 0; i < HEIGHT; i++)
    {
        screenPos.z = ((float)(-i + (HEIGHT/2)))/(HEIGHT/2);
        for (int j = 0; j < WIDTH; j++)
        {

            screenPos.y = ((float)(j - (WIDTH/2)))/(WIDTH/2);
            struct color c = {0,0,0};
            struct vector3 origin = camera;
            struct vector3 dir = {screenPos.x-camera.x, screenPos.y+camera.y, screenPos.z+camera.z};

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
            
            // no intersection with scene
            if (mindex == -1)
                continue;
            
            mintersection = intersections[mindex];
            d = absv3(subv3(mintersection.pos, origin));
            d /= BRIGHTNESS;
            if (mindex >= numPlanes)
                c = sphereColorAt(spheres[mindex-numPlanes], mintersection.pos);
            else if (mindex >= 0)
                c = planeColorAt(planes[mindex], mintersection.pos);
            c = dimColorPercent(c, 10);

            // ====== LOCAL ILLUMINATION ======
            for (int l = 0; l < numLightSources; l++)
            {
                light_dir = subv3(lightSources[l].pos, mintersection.pos);
                shadow = false;
                for (int p = 0; p < numPlanes && !shadow; p++)
                {
                    t = planeIntersection(planes[p], mintersection.pos, light_dir).t;
                    shadow = t > 0.000001 && t < 1;    // object in shadow if the ray between the point and the light source is blocked
                }
                for (int s = 0; s < numSpheres && !shadow; s++)
                {
                    t = sphereIntersection(spheres[s], mintersection.pos, light_dir).t;
                    shadow = t > 0.000001 && t < 1;
                }
                if (!shadow)
                {
                    d = absv3(light_dir);
                    // brighten color based on inverse square law and difference in direction between ray and surface normal
                    c = brightenColorPercent(c, fabs(dotpv3(light_dir, minormal))*lightSources[l].luminosity/(d*d));
                }
            }

            putPixel(j, i, c);
        }
    }
}