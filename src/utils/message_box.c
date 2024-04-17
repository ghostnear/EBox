#include "utils/message_box.h"

#include "utils/logging.h"

#include <SDL_messagebox.h>

void show_simple_error_messagebox(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
    FILE* logging_file = logging_get_file();
    fprintf(logging_file, "[ERROR]: %s\n", message);
}