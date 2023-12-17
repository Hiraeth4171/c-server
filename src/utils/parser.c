#include <stdlib.h>
#include <stdio.h>
#include "./parser.h"
#include "./logger.h"

#define CHUNK_SIZE 4096

#ifdef __linux__
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/io.h>
#include <unistd.h>
#elif _WIN32

#endif

#define EXTRACTED_STR_CAP 16

int compare(char* str1, char* str2, int len) {
    // printf("%s", str1);
    char *ptr1 = str1, *ptr2 = str2;
    while (*ptr1++ == *ptr2++) {
        if ((--len)==0) {
            return 1;
        }
    }
    //printf("\x1b[31m str1: \x1b[0m%s\t\t\x1b[31mstr2:\x1b[0m %s,\n\x1b[0m \x1b[31m ptr1: \x1b[0m%s\t\t\x1b[31m ptr2:\x1b[0m %s\n", str1, str2, ptr1, ptr2);
    return 0;
}

#ifdef __linux__
char* read_file(char* filepath) {
    static char* file = NULL;
    static unsigned int at_chunk = 0;
    if (filepath != NULL) { 
        file = filepath;
        at_chunk = 0; 
    }
    if (file == NULL) return NULL;

    size_t size;
    struct stat ss;

    int fp = open(file, O_RDONLY);
    fstat(fp, &ss);
    size = ss.st_size;
    off_t pa_offset, offset = (at_chunk*CHUNK_SIZE);
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    if (offset >= size) {
        return NULL;
    }
    size_t len = CHUNK_SIZE*at_chunk < size ? CHUNK_SIZE : size - (CHUNK_SIZE*at_chunk);

    return (char*)mmap(0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fp, pa_offset);
}

void free_file(char* file, unsigned int size) {
    munmap((void*)file, size);
}

#elif _WIN32
#endif

char* extract_string(char* str, char end, int* len) {
    char* res = (char*)malloc(sizeof(char) * EXTRACTED_STR_CAP);
    unsigned int capacity = EXTRACTED_STR_CAP;
    unsigned int size = 0;
    char* ptr1 = str, *ptr2 = res;
    while(*ptr1 != end) {
        if (size >= capacity) res = realloc(res, sizeof(char)*(capacity*=2)); 
        *ptr2++ = *ptr1++;
        size++;
    }
    res[size] = '\0';
    *len = size;
    //printf("\n\n\tres:%s\n\n", res);
    return res;
}

I_Config* parse_ini(char* config_file) {
    //create struct
    I_Config* config = (I_Config*)malloc(sizeof(I_Config));
    
    if (config == NULL) {
        // TODO: handle alloc error.
        log_err(-10,"MEMORY ALLOCATION ERROR\n");
        return NULL;
    }

    // read file
    char* config_str = read_file(config_file);
    //tokenize
    char* ptr = config_str;
    INI_Type type;
    int comment = 0;
    unsigned int len = 0;
    int* offset = (int*)calloc(sizeof(int), 1);
    while(*ptr != '\0') {
        if (*ptr == ';') comment = 1;
        if (comment && *ptr == '\n') comment = 0;
        if (comment) {
            ptr++;
            continue;
        }
        if (*ptr == '[') {
            if (compare(ptr+1, "SERVER]", 7)) { 
                type = SERVER;
                ptr += 9;
            }
            else if (compare(ptr+1, "API]", 4)) {
                type = API;
                ptr += 6;
            }
        }
        switch (type) {
            case SERVER:
                if (compare(ptr, "active_static_root=", 19)) {
                    config->server.active_static_root = extract_string(ptr+20, '"', offset);
                    ptr += 20 + *offset;
                }
                else if (compare(ptr, "static_root=", 12)) {
                    config->server.static_root = extract_string(ptr+13, '"', offset);
                    ptr += 13 + *offset;
                    printf("%d", *offset);
                }
                else if (compare(ptr, "api_root=", 9)) {
                    config->server.api_root = extract_string(ptr+10, '"', offset);
                    ptr += 10 + *offset;
                }
                else if (compare(ptr, "hostname=", 9)) {
                    config->server.hostname = extract_string(ptr+10, '"', offset);
                    ptr += 10 + *offset;
                }
                else if (compare(ptr, "port=", 5)) {
                    config->server.port = atoi(extract_string(ptr+5, '\n', offset));
                    ptr += 6 + *offset;
                }
            break;
            case API:
                if (compare(ptr, "templates=", 10)) {
                    config->api.templates = extract_string(ptr+11, '"', offset);
                    ptr += 11 + *offset;
                }
            break;
        }
        ptr++;
    }
    free_file(config_str, len);
    //*config = (I_Config){server, api};
    return config;

}
