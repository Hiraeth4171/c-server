#include "utils.h"

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
