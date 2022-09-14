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
#define BRIGHTNESS 5
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
    int numPlanes = 0;
    struct plane planes[] = {
        {SCALE, I_HAT, {10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, I_HAT, {-10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, J_HAT, {0,10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, J_HAT, {0,-10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, K_HAT, {0,0,5}, PI/4, planeTextureFromFile("assets/ceiling.jpg")},
        {SCALE, K_HAT, {0,0,-3}, PI/4, planeTextureFromFile("assets/floor.jpg")}
    };

    int numSpheres = 1;
    struct sphere spheres[] = {
        {SCALE, {7, 0, 0}, 2, {255, 20, 20}},
        {SCALE, {7, 2, 0}, 1, {20, 255, 20}}
    };

    struct vector3 camera = {0, 0, 0};
    struct vector3 screenPos = {camera.x+1, 0, 0};

    float roll = 0;
    float pitch = 0;
    float yaw = frame*(PI/256);

    struct intersection planeIntersections[numPlanes];
    int planeMindex = -1;

    struct intersection sphereIntersections[numSpheres];
    int sphereMindex = -1;

    float d0, d1;

    for (int i = 0; i < HEIGHT; i++)
    {
        screenPos.z = ((float)(-i + (HEIGHT/2)))/(HEIGHT/2);
        for (int j = 0; j < WIDTH; j++)
        {
            screenPos.y = ((float)(j - (WIDTH/2)))/(WIDTH/2);
            struct color c = {0,0,0};
            struct vector3 origin = camera;
            struct vector3 dir = {screenPos.x-camera.x, screenPos.y+camera.y, screenPos.z+camera.z};

            dir = rotatev3(I_HAT, dir, roll);
            dir = rotatev3(J_HAT, dir, pitch);
            dir = rotatev3(K_HAT, dir, yaw);

            // find shortest intersection between ray and plane
            for (int p = 0; p < numPlanes; p++)
            {
                planeIntersections[p] = planeIntersection(planes[p], camera, dir);
                if (planeIntersections[p].t > 0 && (planeMindex == -1 || planeIntersections[p].t < planeIntersections[planeMindex].t))
                    planeMindex = p;
            }

            // find shortest intersection between ray and sphere
            for (int s = 0; s < numSpheres; s++)
            {
                sphereIntersections[s] = sphereIntersection(spheres[s], camera, dir);
                if (sphereIntersections[s].t > 0 && (sphereMindex == -1 || sphereIntersections[s].t < sphereIntersections[sphereMindex].t))
                    sphereMindex = s;
            }

            //get the shortest distance and the color of the closest object            
            if (planeMindex >= 0 && sphereMindex >= 0)
            {
                d0 = dotpv3(subv3(planeIntersections[planeMindex].pos, origin), dir);
                d1 = dotpv3(subv3(sphereIntersections[sphereMindex].pos, origin), dir);
                if (d1 < d0)
                {
                    d0 = d1;
                    c = sphereColorAt(spheres[sphereMindex], sphereIntersections[sphereMindex].pos);
                }
                else
                    c = planeColorAt(planes[planeMindex], planeIntersections[planeMindex].pos);
            }
            else if (planeMindex >= 0)
            {
                d0 = dotpv3(subv3(planeIntersections[planeMindex].pos, origin), dir);
                c = planeColorAt(planes[planeMindex], planeIntersections[planeMindex].pos);
            }
            else if (sphereMindex >= 0)
            {
                d0 = dotpv3(subv3(sphereIntersections[sphereMindex].pos, origin), dir);   
                c = sphereColorAt(spheres[sphereMindex], sphereIntersections[sphereMindex].pos);
                printf("Dist & color: %f ", d0);
                printcolor(c);
            }
            else 
            {
                planeMindex = -1;
                sphereMindex = -1;
                continue;
            }
            d0 /= BRIGHTNESS;
            c = dimColorPercent(c, d0);
            planeMindex = -1;
            sphereMindex = -1;
            putPixel(j, i, c);
        }
    }
}