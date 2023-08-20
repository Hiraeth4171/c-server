#include "logger.h"
#include "iniparser.h"
#include "server.h"
#include <sys/socket.h>

I_Config* server_config;

// TODO: basic server setup 

RequestHandler req_handler;

void load_config(char* config_file) {
    server_config = parse(config_file);
    if (config_file == NULL) {
        log_warn(1, "Failed to load config file, reverting to hardcoded defaults...");
        I_Server server = (I_Server){"/", "./static/", "./api/"};
        I_API api = (I_API){"./templates"};
        I_Config local_config = (I_Config){server, api};
        server_config = &local_config;
    }
    //log_info("Loaded Config File: \x1b[35m%s", config_file);
    log_info("Loaded Config File:\x1b[35m config.ini\n");
    //log_info("Current Config:\n");
    //printf("\tServer:\n");
    //printf("\t\tactive_static_root: %s,\n", server_config->server.active_static_root);
    //printf("\t\tstatic_root: %s,\n", server_config->server.static_root);
    //printf("\t\tapi_root: %s\n", server_config->server.api_root);
    //printf("\tAPI:\n");
    //printf("\t\ttemplates: %s\n", server_config->api.templates);
}

void launch(char* hostname, int port) {
    // TODO: launch server
    // TODO: get a way to do this: 
    // log_info("[Server Launched]\n\tHOSTNAME: %s\n\tPORT: %d\n", hostname, port);
    log_info("[Server Launched]\n\t\t\x1b[32m+ HOSTNAME: ziraeth.me\n\t\t+ PORT: 80\n");
    // test case
    //req_handler(msg);
}

void shutdown() {
   // free resources
   free(server_config);
   // TODO: make a final write to the log files
}

void bind_handler(RequestHandler request_handler) {
    req_handler = request_handler;
}
