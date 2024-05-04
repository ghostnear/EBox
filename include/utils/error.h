#pragma once

#include <stdbool.h>

bool has_errored();

void set_error(const char*);

void clear_error();