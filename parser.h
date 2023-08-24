#include "utils.h"

#define LINE_LENGTH 512

typedef struct I_Server {
    char* active_static_root;
    char* static_root;
    char* hostname;
    int port;
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

char** allocate_string_array(int size);

char** split_key_value_pair(char* input, char delim);

I_Config* parse_ini(char* config_file);

