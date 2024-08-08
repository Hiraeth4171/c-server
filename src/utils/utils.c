#include "./utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./logger.h"

#define LINE_LENGTH 128
#define LINE_COUNT 16

void str_cpy(char* dest, char* src, unsigned int n) {
    char* src_ptr = src;
    char* dest_ptr = dest;
    for (unsigned int i = 0; i < n; ++i) {
       *dest_ptr++ = *src_ptr++;
    }
}

unsigned int str_len(char* str) {
    char* ptr = str;
    unsigned int counter = 0;
    while (*ptr++ != '\0') ++counter;
    return counter;
}

int str_cmp(char* lhs, char* rhs) {
    while(*lhs && (*lhs == *rhs)) {
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

int str_n_cmp(char* lhs, char* rhs, int n) {
    while(n-- > 0 && *lhs && (*lhs == *rhs)) {
        lhs++;
        rhs++;
    }
    if (n == 0) return 0;
    return  *lhs - *rhs;
}

void str_cat(char* dest, char* src, char** end_ptr) {
    if (end_ptr == NULL) {
        char* ptr1 = dest;
        while (*ptr1++ != '\0');
        char* ptr2 = src; --ptr1;
        while (*ptr2 != '\0') {
            *ptr1++ = *ptr2++;
        }
        *ptr1 = *ptr2;
    } else {
        char* ptr = src;
        while (*ptr != '\0') *((*end_ptr)++) = *ptr++;
    }
}

void bin_cat(char* dest, char* src, char** end_ptr, long length) {
    // end_ptr will necessarily have something, throw otherwise
    if (end_ptr == NULL) exit(1);
    else {
        memcpy(*end_ptr, src, length);
    }
}

char* pread_file(char* filepath, long *len, char* type) {
    if (filepath == NULL) return NULL;
    FILE* fp = fopen(filepath, type);
    if (fp == NULL) {
        log_err(-97, "failed to read file: %s", filepath);
        return NULL;
    }

    char* buffer;
    long l_size;
    // i'm just gonna do it all in one step instead :D
    fseek(fp, 0L, SEEK_END);
    l_size = ftell(fp);
    rewind(fp);
    buffer = (char*)calloc(l_size+1, sizeof(char));
    if (buffer == NULL) {
        fclose(fp);
        log_err(-10, "MALLOC FAILED YOU CUNT file: %s", filepath);
        exit(-10);
    }

    if (fread(buffer, 1, l_size, fp) != l_size) {
        fclose(fp);
        free(buffer);
        log_err(-96,"FILE READ FAILED file: %s", filepath);
        exit(1);
    }
    *len = l_size;
    fclose(fp);
    return buffer; // :D
}
