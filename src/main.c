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
#define BRIGHTNESS 10
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
        {SCALE, {1,0,0}, {10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, {1,0,0}, {-10,0,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, {0,1,0}, {0,10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, {0,1,0}, {0,-10,0}, 0, planeTextureFromFile("assets/wall.jpg")},
        {SCALE, {0,0,1}, {0,0,5}, PI/4, planeTextureFromFile("assets/ceiling.jpg")},
        {SCALE, {0,0,1}, {0,0,-3}, PI/4, planeTextureFromFile("assets/floor.jpg")}
    };

    struct vector3 camera = {0, 0, 0};
    struct vector3 screenPos = {camera.x+1, 0, 0};

    float roll = 0;
    float pitch = 0;
    float yaw = frame*(PI/256);

    struct intersection planeIntersections[numPlanes];
    int planeMindex = -1;

    float d;

    for (int i = 0; i < HEIGHT; i++)
    {
        screenPos.z = ((float)(-i + (HEIGHT/2)))/(HEIGHT/2);
        for (int j = 0; j < WIDTH; j++)
        {
            screenPos.y = ((float)(j - (WIDTH/2)))/(WIDTH/2);
            struct color c = {0,0,0};
            struct vector3 origin = camera;
            struct vector3 dir = {screenPos.x-camera.x, screenPos.y+camera.y, screenPos.z+camera.z};

            dir = rotatev3(iHat, dir, roll);
            dir = rotatev3(jHat, dir, pitch);
            dir = rotatev3(kHat, dir, yaw);

            for (int p = 0; p < numPlanes; p++)
            {
                planeIntersections[p] = planeIntersection(planes[p], camera, dir);
                if (planeIntersections[p].t > 0 && (planeMindex == -1 || planeIntersections[p].t < planeIntersections[planeMindex].t))
                    planeMindex = p;
            }

            if (planeMindex >= 0)
            {
                d = dotpv3(subv3(planeIntersections[planeMindex].pos, origin), dir);
                d /= BRIGHTNESS;
                c = planeColorAt(planes[planeMindex], planeIntersections[planeMindex].pos);
                c = dimColorPercent(c, d);
                planeMindex = -1;
            }
            putPixel(j, i, c);
        }
    }
}