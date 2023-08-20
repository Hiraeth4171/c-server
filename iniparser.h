#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "logger.h"

#define LINE_LENGTH 512

typedef struct I_Server {
    char* active_static_root;
    char* static_root;

    char* api_root;
} I_Server;

typedef struct I_API {
    char* templates;
} I_API;

typedef struct I_Config {
    I_Server server;
    I_API api;
} I_Config;

typedef enum INI_Type {
    SERVER,
    API
} INI_Type;

// TODO: move to c file later

char** allocate_string_array(int size) {
    char** lines = (char**)malloc(sizeof(char*) * size);
    for (int i = 0; i < size; ++i) lines[i] = (char*)malloc(sizeof(char)*LINE_LENGTH);
    return lines;
}

char** split_key_value_pair(char* input, char delim) {
    char** ret = allocate_string_array(2);
    char* ptr = input;
    int i = 0;
    int j = 0;
    while (*ptr != '\0') {
        if (*ptr == delim) {
            i = 1;
            ret[0][j] = '\0';
            j = 0;
        } else {
            if(*ptr != '"' && *ptr != '\n') {
                ret[i][j++] = *ptr;
            }
        }
        ptr++;
    }
    ret[1][j] = '\0';
    return ret;
}

//TODO: move to the logger file 
void print_file(char** lines, int size, char* filename) {
    //TODO: fill empty space, word-wrap
    printf("\n\n\t\x1b[38;5;0m\x1b[48;5;15m%s ----------------------------------------------\x1b[0m\n", filename);
    for (int i = 0; i < size; ++i) printf("\x1b[38;5;15m\t\t%s", lines[i]);
    printf("\x1b[0m\n\n");
}

I_Config* parse(char* config_file) {
    //create struct
    I_Config* config = (I_Config*)malloc(sizeof(I_Config));
    
    if (config == NULL) {
        // TODO: handle alloc error.
        log_err(-10,"MEMORY ALLOCATION ERROR\n");
        return NULL;
    }

    // TODO: read file, parse ini, place into appropriate struct here
    // read file
    FILE* fp = fopen(config_file, "r");
    char* line = NULL; 
    size_t len = 0;
    ssize_t read;
    char capacity = 5; // assuming the config file won't get longer than 256
    // create string array
    char** lines = allocate_string_array((int)capacity); // start with 5 lines
    log_info("READING FILE\n");
    char counter = 0;
    char size = 0;
    //  - tokenize
    while((read = getline(&line, &len, fp)) != -1) {
        if (size >= capacity) {
            capacity += 5;
            lines = (char**)realloc(lines, (int)capacity*(sizeof (char*)));
            for (int i = 0; i < 5; ++i) lines[capacity-5+i] = (char*)malloc(sizeof(char)*LINE_LENGTH);
            if (lines == NULL) {
                log_err(-10, "MEMORY ALLOCATION ERROR\n");
            }
            str_cpy(lines[(int)size++], line, (int)read);
        } else {
            str_cpy(lines[(int)size++], line, (int)read);
        }
        counter++;
    }
    fclose(fp); // close file
    free(line);
    line = NULL;
    //  - enum token groups
    print_file(lines, size, config_file);
    // parse ini from tokens
    I_Server server = (I_Server){"this", "is", "bad"};
    I_API api = (I_API){"very bad"};
    INI_Type ini_type;
    char** key_value;
    for (int i = 0; i < (int)counter; ++i) {
        if (lines[i][0] == ';') continue;
        if (lines[i][0] == '\n') continue;
        if (!str_cmp(lines[i], "[SERVER]\n")) {
            ini_type = SERVER;
        } else if (!str_cmp(lines[i], "[API]\n")) {
            ini_type = API;
        } else {
            key_value = split_key_value_pair(lines[i], '=');
            switch (ini_type) {
                case SERVER:
                    if (!str_cmp(key_value[0], "active_static_root")) {
                        server.active_static_root = key_value[1];
                    } else if (!str_cmp(key_value[0], "static_root")) {
                        server.static_root = key_value[1];
                    } else if (!str_cmp(key_value[0], "api_root")) {
                        server.api_root = key_value[1];
                    } else {
                        log_err(10, "PROBLEM.");
                    }
                    break;
                case API:
                    if (!str_cmp(key_value[0], "templates")) {
                        api.templates = key_value[1];
                    } else {
                        log_err(10, "PROBLEM.");
                    }
                    break;
            }
        }
    }

    *config = (I_Config){server, api};
    return config;
}


