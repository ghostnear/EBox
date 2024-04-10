#include "utils/inifile.h"
#include "utils/dynarray.h"

#include <stdlib.h>
#include <string.h>

ini_file_data* ini_file_create()
{
    ini_file_data* self = calloc(1, sizeof(ini_file_data));
    self->sections = dynarray_create(sizeof(ini_file_section), ini_section_free);
    return self;
}

ini_file_data* ini_file_read(FILE* file)
{
    ini_file_data* self = ini_file_create();

    // Read the file.
    char line[INIFILE_MAX_LINE_LENGTH];
    ini_file_section* current_section = NULL;
    while(fgets(line, sizeof(line), file) != NULL)
    {
        // Remove the newline.
        line[strcspn(line, "\n")] = 0;

        // Check if it's a section.
        if(line[0] == '[')
        {
            // Remove the brackets.
            char* section_name = line + 1;
            section_name[strlen(section_name) - 1] = 0;

            // Add the section.
            current_section = ini_file_add_section(self, section_name);
        }
        else
        {
            // Check if it's an entry.
            char* key = strtok(line, "=");
            char* value = strtok(NULL, "=");

            // Add the entry.
            if(key != NULL && value != NULL)
                ini_section_set_entry(current_section, key, value);
        }
    }

    return self;
}

void ini_file_write(FILE* file, ini_file_data* self)
{
    // Write the sections.
    for(uint32_t index = 0; index < self->sections->size; index++)
    {
        const ini_file_section* section = (ini_file_section*) dynarray_get(self->sections, index);
        fprintf(file, "[%s]\n", section->name);

        // Write the entries.
        for(uint32_t entry_index = 0; entry_index < section->entries->size; entry_index++)
        {
            const ini_file_entry* entry = (ini_file_entry*) dynarray_get(section->entries, entry_index);
            fprintf(file, "%s=%s\n", entry->key, entry->value);
        }
    }
}

ini_file_section* ini_file_add_section(ini_file_data* self, const char* name)
{
    // Section already exists, don't bother.
    if(ini_file_get_section(self, name) != NULL)
        return NULL;

    // Create a new section, save it and free.
    ini_file_section* section = calloc(1, sizeof(ini_file_section));
    section->name = strdup(name);
    section->entries = dynarray_create(sizeof(ini_file_entry), ini_entry_free);
    
    dynarray_push_back(self->sections, section);

    free(section);

    return dynarray_get(self->sections, self->sections->size - 1);
}

ini_file_section* ini_file_get_section(ini_file_data* self, const char* name)
{
    // Go through everything and save the first section with the name.
    for(uint32_t index = 0; index < self->sections->size; index++)
    {
        const ini_file_section* section = (ini_file_section*) dynarray_get(self->sections, index);
        if(strcmp(section->name, name) == 0)
            return (ini_file_section*) section;
    }
    return NULL;
}

ini_file_entry* ini_section_get_entry(ini_file_section* section, const char* key)
{
    // Go through everything and save the first entry with the key.
    for(uint32_t index = 0; index < section->entries->size; index++)
    {
        const ini_file_entry* entry = (ini_file_entry*) dynarray_get(section->entries, index);
        if(strcmp(entry->key, key) == 0)
            return (ini_file_entry*) entry;
    }
    return NULL;
}

ini_file_entry* ini_section_set_entry(ini_file_section* section, const char* key, const char* value)
{
    // Entry already exists, overwrite it.
    ini_file_entry* current = ini_section_get_entry(section, key);
    if(current != NULL)
    {
        current->value = strdup(value);
        return current;
    }

    // Create a new entry.
    ini_file_entry* entry = calloc(1, sizeof(ini_file_entry));
    entry->key = strdup(key);
    entry->value = strdup(value);

    // Save it.
    dynarray_push_back(section->entries, entry);

    free(entry);

    return dynarray_get(section->entries, section->entries->size - 1);
}

void ini_file_remove_entry(ini_file_section* section, const char* key)
{
    // Go through everything and remove the first entry with the key.
    for(uint32_t index = 0; index < section->entries->size; index++)
    {
        ini_file_entry* entry = (ini_file_entry*) dynarray_get(section->entries, index);
        if(strcmp(entry->key, key) == 0)
        {
            dynarray_remove(section->entries, index);
            free(entry);
            return;
        }
    }
}

const char* ini_file_get_string(ini_file_data* file, const char* key, const char* value)
{
    // Get the section.
    ini_file_section* section = ini_file_get_section(file, key);
    if(section == NULL)
        return NULL;

    return ini_section_get_string(section, value);
}

int ini_file_get_int(ini_file_data* file, const char* key, const char* value)
{
    return atoi(ini_file_get_string(file, key, value));
}

float ini_file_get_float(ini_file_data* file, const char* key, const char* value)
{
    return atof(ini_file_get_string(file, key, value));
}

const char* ini_section_get_string(ini_file_section* section, const char* key)
{
    // Get the entry.
    ini_file_entry* entry = ini_section_get_entry(section, key);
    if(entry == NULL)
        return NULL;

    return entry->value;
}

int ini_section_get_int(ini_file_section* section, const char* value)
{
    return atoi(ini_section_get_string(section, value));
}

float ini_section_get_float(ini_file_section* section, const char* value)
{
    return atof(ini_section_get_string(section, value));
}

void ini_entry_free(void* self)
{
    ini_file_entry* entry = (ini_file_entry*) self;
    free(entry->key);
    free(entry->value);
}

void ini_section_free(void* self)
{
    ini_file_section* section = (ini_file_section*) self;
    free(section->name);
    dynarray_free(section->entries);
}

void ini_file_free(void* self)
{
    ini_file_data* file = (ini_file_data*) self;
    dynarray_free(file->sections);
    free(self);
}