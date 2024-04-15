#include "utils/message_box.h"
#include <SDL_messagebox.h>

void show_simple_error_messagebox(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
    printf("[ERROR]: %s\n", message);
}