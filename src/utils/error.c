#include "utils/error.h"

static const char* error_message = 0;

bool has_errored()
{
    return error_message != 0;
}

void set_error(const char* message)
{
    error_message = message;
}

void clear_error()
{
    set_error(0);
}