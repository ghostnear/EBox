#pragma once

#include <stdio.h>

#include "utils/memfree_list.h"

#ifdef BUILD_PLATFORM_VITA
    #define LOGGING_DEFAULT_PATH "ux0:/data/EBox/last.log"
#else
    #define LOGGING_DEFAULT_PATH "last.log"
#endif

void logging_set_file(FILE*);
FILE* logging_get_file();
void log_print(const char*, ...);