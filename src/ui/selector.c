#include "ui/window.h"
#include "ui/selector.h"

#include "utils/inifile.h"
#include "utils/logging.h"
#include "utils/memfree_list.h"

#include <dirent.h>

int config_filter(const struct dirent *name)
{
    // We only care about .cfg files.
    if(strlen(name->d_name) < 4)
        return 0;

    return (strcmp(name->d_name + strlen(name->d_name) - 4, ".cfg") == 0);
}

static int config_count = 0;
void free_configs(void* configData)
{
    ini_file_data** configs = (ini_file_data**) configData;
    for(int index = 0; index < config_count; index++)
        ini_file_free(configs[index]);
    free(configs);
}


void rom_selector_main_loop()
{
    SDL_Window* window = window_get_sdl();
    SDL_SetWindowTitle(window, "EBox ROM selector");

    SDL_Event* event = window_get_event();
    SDL_Renderer* renderer = window_get_renderer();

#ifdef BUILD_PLATFORM_VITA
    const char* configPath = "ux0:data/EBox/configs";
#else 
    const char* configPath = "./configs";
#endif

    // Load the config files paths.
    struct dirent **configFiles;
    config_count = scandir(configPath, &configFiles, &config_filter, alphasort);
    if(config_count < 0)
    {
        FILE* log_file = logging_get_file();
        fprintf(log_file, "Error: Could not load config files.\n");
        exit(-1);
    }

    int count = config_count;

    ini_file_data** configs = calloc(count, sizeof(ini_file_data*));

    while(count--)
    {
        // Building the path.
        char* path = malloc(strlen(configPath) + strlen(configFiles[count]->d_name) + 2);
        sprintf(path, "%s/%s", configPath, configFiles[count]->d_name);
        
        // Loading the file.
        FILE* current_file = fopen(path, "r");
        configs[count] = ini_file_read(current_file);
        fclose(current_file);

        free(configFiles[count]);
        free(path);
    }
    free(configFiles);

    memfree_add(configs, free_configs);

    while(true)
    {
        // Poll events and draw.
        while(SDL_PollEvent(event))
        {
            switch(event->type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }
}