#include "utils/file.h"

uint32_t file_size_get(FILE* file)
{
    // Go to end.
    fseek(file, 0L, SEEK_END);

    // Get size.
    uint32_t size = ftell(file);

    // Reset.
    fseek(file, 0L, SEEK_SET);

    // Done.
    return size;
}