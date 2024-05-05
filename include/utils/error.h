#pragma once

#include <stdbool.h>

/*
 * Checks if an error has been set.
 */
bool has_errored();

/*
 * Sets an error message.
 */
void set_error(const char*);

/*
 * Asserts a condition and sets an error message if it fails.
 */
void assert_error(bool, const char*);

/*
 * Shows the error message if it has been set.
 */
void show_error();

/*
 * Clears the error message.
 */
void clear_error();