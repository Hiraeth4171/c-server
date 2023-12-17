#include "utils/parser.h"
#include <stdbool.h>

typedef enum File_Type {
    F_BIN,
    F_ASCII
} File_Type;

void init_router(I_Config config);
char* find_route(char* routing_string);
bool validate_path(char* filepath);
File_Type determine_filetype(char* file);
char* determine_mimetype(char* file);
