#pragma once

#include <stdio.h>

#include "dynarray.h"

#define INIFILE_MAX_LINE_LENGTH 256

// Simple .ini file handler, should work with most .ini files.

// An entry in the .ini file. Consists of a key and a value.
typedef struct {
    char* key;
    char* value;
} ini_file_entry;

// A section in the .ini file. Consists of a name and a list of entries.
typedef struct {
    char* name;
    dynarray* entries;
} ini_file_section;

// The .ini file data. Consists of a list of sections.
typedef struct {
    dynarray* sections;
} ini_file_data;

ini_file_data* ini_file_create();
ini_file_data* ini_file_read(FILE*);
void ini_file_write(FILE*, ini_file_data*);
ini_file_section* ini_file_add_section(ini_file_data*, const char*);
ini_file_section* ini_file_get_section(ini_file_data*, const char*);

ini_file_entry* ini_section_get_entry(ini_file_section*, const char*);
ini_file_entry* ini_section_set_entry(ini_file_section*, const char*, const char*);
void ini_section_remove_entry(ini_file_section*, const char*);

const char* ini_file_get_string(ini_file_data*, const char*, const char*);
int ini_file_get_int(ini_file_data*, const char*, const char*);
float ini_file_get_float(ini_file_data*, const char*, const char*);

const char* ini_section_get_string(ini_file_section*, const char*);
int ini_section_get_int(ini_file_section*, const char*);
float ini_section_get_float(ini_file_section*, const char*);

void ini_entry_free(void*);
void ini_section_free(void*);
void ini_file_free(void*);
