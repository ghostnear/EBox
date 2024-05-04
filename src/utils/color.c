#include "utils/color.h"
#include "utils/error.h"

SDL_Color parse_color_hex(const char* color_string)
{
    SDL_Color color = {0, 0, 0, 0};

    if(color_string != NULL && color_string[0] == '#')
    {
        unsigned int hex_color = 0;
        sscanf(color_string, "#%x", &hex_color);

        color.r = (hex_color >> 16) & 0xFF;
        color.g = (hex_color >> 8) & 0xFF;
        color.b = hex_color & 0xFF;

        return color;
    }

    set_error("Invalid color string. Expected: #RRGGBB");
    return color;
}

SDL_Color parse_color_rgb(const char * color_string)
{
    SDL_Color color = {0, 0, 0, 0};

    if(color_string != NULL)
    {
        unsigned int r, g, b;
        if(sscanf(color_string, "%u,%u,%u", &r, &g, &b) == 3)
        {
            color.r = r;
            color.g = g;
            color.b = b;

            return color;
        }
    }

    set_error("Invalid color string. Expected: R,G,B");
    return color;
}