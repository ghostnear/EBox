#pragma once

#include <stdio.h>

#include "utils/memfree_list.h"

void logging_set_file(FILE*);
FILE* logging_get_file();