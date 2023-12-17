#include "./logger.h"
#include <stdio.h>
#include <stdarg.h>

#define LOG_BUFFER_LEN 2048
// TODO: consider having a different thread for this
// TODO: file logging system - create a buffer, fill it bit by bit,
// flush the buffer into a file when it fills.

void log_err(char err_code, char* message, ...) {
    char buffer[256]; // i'll assume all error lines don't exceed this;
    va_list args;
    va_start(args, message);
    vsprintf(buffer, message, args);
    fprintf(stderr, "\x1b[31m\t[e]!%d -\x1b[0m\x1b[4m %s\x1b[0m", err_code, buffer);
}

void log_info(char* message, ...) {
    char buffer[256]; // same
    va_list args;
    va_start(args, message);
    vsprintf(buffer, message, args);
    fprintf(stdout, "\x1b[33m\t[i] - %s\x1b[0m", buffer);
}

void log_warn(char err_code, char* message, ...) {
    char buffer[256]; // same;
    va_list args;
    va_start(args, message);
    vsprintf(buffer, message, args);
    fprintf(stdout, "\x1b[38;5;31m\t[w]@%d -\x1b[0m %s\n", err_code, buffer);
}

void print_file(char** lines, int size, char* filename) {
    //TODO: fill empty space, word-wrap
    printf("\n\n\t\x1b[38;5;0m\x1b[48;5;15m%s ----------------------------------------------%d\x1b[0m\n", filename, size);
    for (int i = 0; i < size; ++i) printf("\x1b[38;5;15m\t\t%s", lines[i]);
    printf("\x1b[0m\n\n");
}

