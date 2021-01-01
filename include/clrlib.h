#pragma once

#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} color_t;

color_t rgb8_to_rgb24(uint8_t rgb8);
