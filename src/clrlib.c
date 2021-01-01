#include <stdint.h>
#include <clrlib.h>

/*
 * 8-bit color is has its byte like so:
 * RRR GGG BB
 * 
 * So we have to convert a number out of 8 to a number out of 256
 * for Red and Green
 * then a number out of 4 to a number out of 256 for Blue
 * 
 */
color_t rgb8_to_rgb24(uint8_t rgb8) {
    return (color_t) {
        (uint8_t) ((float) (rgb8 >> 5) / 7 * 255),          // Red
        (uint8_t) ((float) ((rgb8 >> 2) & 0x07) / 7 * 255), // Green
        (uint8_t) ((float) (rgb8 & 0x03) / 3 * 255)         // Blue
    };
}
