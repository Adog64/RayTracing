#include "vector3.h"
#include "scene_objs.h"
#include "colors.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

#define SCALE 250
#define WIDTH 2*SCALE
#define HEIGHT 2*SCALE
#define FPS 30

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void clearScreen();
void putPixel(int, int, struct color);
void render();

int main()
{

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;

    while (running)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;
        }
        clearScreen();
        render();
        SDL_RenderPresent(renderer);

        SDL_Delay(1/FPS);
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

void render()
{
    int numPlanes = 5;
    struct plane planes[] = {
        {{1,0,0}, {9,0,0}, planeTextureFromFile("assets/wall.jpg")},
        {{0,0,1}, {0,0,-3}, planeTextureFromFile("assets/floor.jpg")}
    };

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            
        }
        // printf("Rendered... [%d/%d]\n", i+1, HEIGHT);
    }
}