#include <stdlib.h>
#include "./utils/logger.h"

// basic options - fetch from file
#define PORT 80
#define HOSTNAME "ziraeth.me"
#define CONFIG_FILE "../data/config.ini"

// include specific backends 
#ifdef _WIN32
#include "./backends/winserver.h"
#elif __linux__
#include "./backends/server.h"
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

    log_info("[MAIN INSTANCE OF SMILEY-SERVER v1.0.0]\n");
    load_config(CONFIG_FILE);
    // 


    // bind request handler
    bind_handler(_handler);
    // launch server
    launch_server();
    // shutdown server
    shutdown_server(0);
    return EXIT_SUCCESS;
}
