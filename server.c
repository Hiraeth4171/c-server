#include "logger.h"
#include "parser.h"
#include "server.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

I_Config* server_config;

char* default_headers;
long* default_headers_len;

RequestHandler req_handler;

void load_config(char* config_file) {
    if (config_file == NULL) {
        log_warn(1, "Failed to load config file, reverting to hardcoded defaults...");
        I_Server server = (I_Server){"/", "./static/", "./api/"};
        I_API api = (I_API){"./templates"};
        I_Config* local_config = malloc(sizeof(I_Config));
        *local_config = (I_Config){server, api};
        server_config = local_config;
        return;
    }
 
    server_config = parse_ini(config_file);
    if (server_config == NULL) {
        exit (-10);
    }
    log_info("Loaded Config File: \x1b[35m%s\n", config_file);
    //log_info("Current Config:\n");
    //printf("\tServer:\n");
    //printf("\t\tactive_static_root: %s,\n", server_config->server.active_static_root);
    //printf("\t\tstatic_root: %s,\n", server_config->server.static_root);
    //printf("\t\tapi_root: %s\n", server_config->server.api_root);
    //printf("\tAPI:\n");
    //printf("\t\ttemplates: %s\n", server_config->api.templates);
}

void init(int* sockfd, struct sockaddr_in* host_addr, socklen_t addr_len) {
    // create socket
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1) {
        perror("SOCKET ERROR");
        log_err(-100, "Failed to create a socketfd");
        exit(errno);
    }
    if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        perror("SOCKET ERROR");
        log_err(-99, "Failed to set socket options");
        exit(errno);
    }
    // create address
    host_addr->sin_family = AF_INET;
    host_addr->sin_port = htons(server_config->server.port);
    host_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    // bind
    if (bind(*sockfd, (struct sockaddr *)host_addr, addr_len)){
        perror("SOCKET ERROR");
        log_err(-101 ,"Failed to bind socket to address");
        exit(errno);
    }

    // load headers
    default_headers = pread_file("./headers", default_headers_len);
}

void print_req (char* buffer, char* client_ip, unsigned int client_port) {
    char *ptr = buffer;
    unsigned int count;
    while (*ptr++ != '\n') count++;
    char *request_line = (char *)malloc(sizeof (char) * (count+1));
    for (unsigned int i = 0; i < (unsigned int)(ptr-buffer); ++i) {
        request_line[i] = buffer[i];
    }
    request_line[count] = '\0';
    // TODO: filter through known ips for name replacement
    log_info("[%s:%u] -\x1b[0m %s\n", client_ip, client_port, request_line);
    //printf (buffer);
}

void launch (char* hostname, int port) {
    log_info("[Server Launched]\n\t\t\x1b[32m+ HOSTNAME: %s\n\t\t+ PORT: %d\n", hostname, port);
    
    char buff[BUFFER_SIZE];
    
    int sockfd;
    struct sockaddr_in host_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = (socklen_t)sizeof(client_addr);
    socklen_t addr_len = (socklen_t)sizeof(host_addr);
    init(&sockfd, &host_addr, addr_len);

    // listen
    //                 -backlog-
    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("SOCKET ERROR");
        log_err(-102, "Failed to listen to socket");
        exit(errno);
    }

    for (;;) {
        int new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t *)&client_addr_len);
        if (new_sockfd < 0) {
            perror("SOCKET ERROR");
            log_err(-104, "Failed to accept connection.");
            printf("errno; %d", errno);
            continue;
        }
        log_info("Connection Accepted\n");
        // get client info
        /*int socket_name = getsockname(new_sockfd, (struct sockaddr *)&client_addr, 
                (socklen_t*)&client_addr_len);
        if (socket_name < 0) {
            perror("SOCKET NAME GET ERROR");
            log_err(-98, "Failed to get socket name.");
            continue;
        }*/

        // TODO: blacklist
        // read
        int count = read(new_sockfd, buff, BUFFER_SIZE);
        if (count < 0) {
            perror("SOCKET BUFFER READ FAILED");
            log_err(-105, "Failed to read from socket");
            continue;
        }
        
        print_req(buff, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        long* len = (long*)malloc(sizeof(long));
        log_info("segfault?");
        char* index = pread_file("./index.html", len);
        char* response = (char*)calloc(*default_headers_len+*len, sizeof(char));
        log_info("teeeheee segfault not happened yet obviously");
        str_cat(response, default_headers, response);
        log_info("seg fault?");
        str_cat(response, index, response+*default_headers_len);
        log_info("SEG FAULT???");
        count = write(new_sockfd, response, *default_headers_len+*len);
        if (count < 0) {
            perror("SOCKET BUFFER WRITE FAILED");
            log_err(-106, "Failed to write to socket");
            continue;
        }
        close(new_sockfd);
    }
}

int shutdown_server (int code) {
    // this will practically never be invoked with a non-0 error code :D
    if (code != 0) log_err(code, "PROBLEM."); 
    // free resources
    free(server_config);
    // TODO: make a final write to the log files
    // flush_log();
    exit(code);
}

void bind_handler(RequestHandler request_handler) {
    req_handler = request_handler;
}
