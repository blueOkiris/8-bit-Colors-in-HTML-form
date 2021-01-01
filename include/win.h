#pragma once

#include <stdint.h>

#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720

int window_init();
void window_fill_rect(
    int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b
);
void window_draw_text(
    int x, int y, int w, int h, const char *text,
    uint8_t r, uint8_t g, uint8_t b
);
void window_clear();
void window_update();
void window_destroy();
