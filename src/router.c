/*
*   ROUTER;
*   - config, routing string :  IN
*   - filetype, filepath : OUT
*
*/
#include <malloc.h>
#include <stdio.h>
#include "router.h"
#include "utils/utils.h"
#include <stdbool.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access

char* get_mimetype() {
    char* type = "do stuff here";
    return type;
}

#elif __linux__
#include <unistd.h>
#include <stdlib.h>

char* get_mimetype(char* filepath) {
    char* cmd = calloc(85, sizeof(char));
    str_cpy(cmd, "mimetype -b ", 20);
    str_cat(cmd, filepath, NULL);
    FILE *mime = popen(cmd, "r");
    char *mimetype = calloc(65, sizeof(char));
    char *res = NULL;
    if(fgets(mimetype, 65, mime) != 0) {
        char* ptr = mimetype;
        int count = 0;
        while (*ptr++ != '\0') count++;
        res = calloc(count, sizeof(char));
        char* res_ptr = res;
        while (*mimetype != '\n'){
            *res_ptr = *mimetype;
            res_ptr++; mimetype++;
        }
    }
    pclose(mime);
    return res;
}
#endif

I_Config local_config;

void init_router(I_Config config) {
    local_config = config;
}

char* find_route(char* routing_string) {
    printf("%s\n\n", routing_string);
    if (*routing_string == '/' && str_len(routing_string) <= 1) routing_string = "/index.html";
    printf("%s\n\n", routing_string);
    char* filepath = (char*)calloc(sizeof(char),(str_len(routing_string) + str_len(local_config.server.static_root))+1);
    str_cat(filepath, local_config.server.static_root, NULL);
    str_cat(filepath, routing_string, NULL);
    printf("%s", filepath);
    return filepath;
}

bool validate_path(char* filepath) {
    filepath[str_len(filepath)] = '\0';
    if (filepath == NULL) return false;
    if (!access(filepath, F_OK)) return true;
    else return false;
}

File_Type determine_filetype(char* file) {
    char* mimetype = get_mimetype(file);
    // image/
    if (str_n_cmp(mimetype, "image/", 5) == 0) {
        return F_BIN;
    } else {
        return F_ASCII;
    }
}

char* determine_mimetype(char* file) {
    return get_mimetype(file);
}

char* strip_to_file(char* filepath) {
    char* ptr = filepath;
    char* slash = filepath;
    int counter = 0;
    while (*ptr++ != '\0') {
        if (*ptr == '/') {
            slash = ptr;
            counter = 0;
        }
        counter++;
    }
    char* result = (char*)malloc((counter+1)*sizeof(char));
    char* result_itr = result;
    while (*slash != '\0') *result_itr++ = *slash++;
    result[counter] = '\0';
    return result;
}
