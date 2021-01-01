#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <error.h>
#include <win.h>

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static TTF_Font *g_font = NULL;

int window_init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return CLR_ERR_SDL_FAILED;
    }
    if(TTF_Init() < 0) {
        printf("TTF could not initialize! TTF Error: %s\n", TTF_GetError());
        return CLR_ERR_TTF_FAILED;
    }

    g_window = SDL_CreateWindow(
        "8 Bit Colors in HTML Format",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if(g_window == NULL) {
        printf("SDL could not create window! SDL Error: %s\n", SDL_GetError());
        return CLR_ERR_WINDOW_FAILED;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if(g_renderer == NULL) {
        printf("Could not create renderer! SDL Error: %s\n", SDL_GetError());
        return CLR_ERR_RENDERER_FAILED;
    }

    g_font = TTF_OpenFont("fonts/Ubuntu-R.ttf", 100);
    if(g_font == NULL) {
        printf("Could not open font! TTF Error: %s\n", TTF_GetError());
        return CLR_ERR_FONT_FAILED;
    }

    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return CLR_ERR_NONE;
}

void window_fill_rect(
        int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b) {
    SDL_Rect draw_rect = { x, y, w, h };
    SDL_SetRenderDrawColor(g_renderer, r, g, b, 0xFF);
    SDL_RenderFillRect(g_renderer, &draw_rect);
}

void window_draw_text(
        int x, int y, int w, int h, const char *text,
        uint8_t r, uint8_t g, uint8_t b) {
    SDL_Color white = { r, g, b };
    SDL_Surface *message_surface = TTF_RenderText_Solid(g_font, text, white);
    SDL_Texture *message = SDL_CreateTextureFromSurface(
        g_renderer, message_surface
    );
    SDL_Rect message_box = { x, y, w, h };
    
    SDL_RenderCopy(g_renderer, message, NULL, &message_box);

    SDL_FreeSurface(message_surface);
    SDL_DestroyTexture(message);
}

void window_clear() {
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(g_renderer);
}

void window_update() {
    SDL_RenderPresent(g_renderer);
}

void window_destroy() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    TTF_CloseFont(g_font);
    g_renderer = NULL;
    g_window = NULL;
    g_font = NULL;

    SDL_Quit();
}
