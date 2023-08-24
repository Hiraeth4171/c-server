#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

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
    while (*ptr++ != '\0');
    return (unsigned int)(ptr-str);
}

int str_cmp(char* lhs, char* rhs) {
    while(*lhs && (*lhs == *rhs)) {
        lhs++;
        rhs++;
    }
    return *(const unsigned char*)lhs - *(const unsigned char*)rhs;
}

void str_cat(char* dest, char* src, char* end_ptr) {
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
        while (*ptr != '\0') *end_ptr++ = *ptr++;
    }
}

char* pread_file(char* filepath, long *len) {
    if (filepath == NULL) return NULL;
    FILE* fp = fopen(filepath, "r");
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

    buffer = (char*)malloc(sizeof(char)* (l_size+1));
    if (buffer == NULL) {
        fclose(fp);
        log_err(-10, "MALLOC FAILED YOU CUNT file: %s", filepath);
        exit(-10);
    }

    if (fread(buffer, l_size, 1, fp) != 1) {
        fclose(fp);
        free(buffer);
        log_err(-96,"FILE READ FAILED file: %s", filepath);
        exit(1);
    }
    if (len != NULL) *len = l_size;
    fclose(fp);
    return buffer; // :D
}
