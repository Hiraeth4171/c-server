#include "logger.h"
#include <stdio.h>

#define LOG_BUFFER_LEN 2048
// TODO: consider having a different thread for this
// TODO: file logging system - create a buffer, fill it bit by bit,
// flush the buffer into a file when it fills.

void log_err(char err_code, char* message) {
    fprintf(stderr, "\x1b[31m\t[e]!%d -\x1b[0m\x1b[4m %s\x1b[0m", err_code, message);
}

void log_info(char* message) {
    fprintf(stdout, "\x1b[33m\t[i] - %s\x1b[0m", message);
}

void log_warn(char err_code, char* message) {
    fprintf(stdout, "\x1b[38;5;31m\t[w]@%d -\x1b[0m %s\n", err_code, message);
}
