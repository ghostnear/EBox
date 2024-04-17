#include "utils/logging.h"
#include "utils/memfree_list.h"

#include <stdlib.h>

typedef struct
{
    FILE* file;
} Logger;

static Logger* logger = NULL;

void free_log_file(void* logger)
{
    Logger* log = (Logger*)logger;
    fclose(log->file);
    free(log);
}

Logger* create_log_file()
{
    Logger* logger = calloc(1, sizeof(Logger));
    logger->file = fopen("log.txt", "w");
    memfree_add(logger, free_log_file);
    return logger;
}

void logging_set_file(FILE* file)
{
    if(logger == NULL)
        logger = create_log_file();

    logger->file = file;
}

FILE* logging_get_file()
{
    if(logger == NULL)
        logger = create_log_file();

    return logger->file;
}