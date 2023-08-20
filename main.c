#include <stdlib.h>

#include "logger.h"
// basic options - fetch from file
#define PORT 80
#define HOSTNAME "ziraeth.me"
#define CONFIG_FILE "./config.ini"

// include specific backends 
#ifdef _WIN32
#include "winserver.h"
#elif __linux__
#include "server.h"
#else
#define UNKNOWN_OS
#endif

void _handler (char* buffer) {
    // request recieved.
    log_warn(10,"[<METHOD> REQUEST RECIEVED] - <ip> - <time>");
}

int main (void) {
    
    #ifdef UNKNOWN_OS
    log_err(100, "FAILED TO LOAD APPROPRIATE BACKEND, OS NOT SUPPORTED\n");
    return EXIT_FAILURE;
    #elif __linux__
    log_info("LOADED LINUX BACKEND\n");
    #elif _WIN32
    log_info("LOADED WINDOWS BACKEND\n");
    #endif

    log_info("[MAIN INSTANCE OF SMILEY-SERVER v0.0.1]\n");
    // this will detail the expected behavior ------------------------
    load_config(CONFIG_FILE);
    bind_handler(_handler);
    launch(HOSTNAME, PORT);
    // bind basic handlers
    // unbind basic handlers
    // close - shutdown

    return EXIT_SUCCESS;
}
