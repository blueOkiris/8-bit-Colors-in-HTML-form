#include <stdio.h>
#include <SDL2/SDL.h>
#include <error.h>
#include <win.h>
#include <clrlib.h>

int main(int argc, char **args) {
    int success = window_init();
    if(success != CLR_ERR_NONE) {
        return success;
    }

    // Some numbers to calculate
    int colors_per_row = 16;
    int num_rows = 256 / colors_per_row;
    int rect_width = WINDOW_WIDTH / colors_per_row;
    int rect_height = WINDOW_HEIGHT / num_rows;

    int color_switch_thresh = 247; // When to switch from white text to black

    // Only clear and draw it once
    window_clear();
    char buffer[11];
    for(int y = 0; y < num_rows; y++) {
        for(int x = 0; x < colors_per_row; x++) {
            // Calculate the 24-bit color from the 8 bit number
            uint8_t rgb8 = (uint8_t) (y * colors_per_row + x);
            color_t rgb24 = rgb8_to_rgb24(rgb8);

            /*
             * Put it in a string:
             * # ## ## ## is the max size
             * Plus null makes it 11
             */
            sprintf(buffer, "#%02x%02x%02x", rgb24.r, rgb24.g, rgb24.b);
            //printf("RGB8 Color: %u, RGB24: %s\n", rgb8, buffer);

            // Draw the color as a square and print the color's text
            window_fill_rect(
                x * rect_width, y * rect_height, rect_width, rect_height,
                rgb24.r, rgb24.g, rgb24.b
            );

            // Switch to black if too bright
            if(rgb8 <= color_switch_thresh) {
                window_draw_text(
                    x * rect_width + 5, y * rect_height + 10,
                    rect_width - 10, rect_height - 20,
                    buffer,
                    0xFF, 0xFF, 0xFF
                );
            } else {
                window_draw_text(
                    x * rect_width + 5, y * rect_height + 10,
                    rect_width - 10, rect_height - 20,
                    buffer,
                    0x00, 0x00, 0x00
                );
            }
        }
    }
    window_update();

    // Loop until window close event
    char quit = 0;
    SDL_Event e;
    while(!quit) {
        SDL_PollEvent(&e);
        switch(e.type) {
            case SDL_QUIT:
                quit = 1;
                break;
        }
    }

    window_destroy(); // cleanup

    return CLR_ERR_NONE;
}