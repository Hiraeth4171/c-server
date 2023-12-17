typedef struct Server {
    char* hostname;
    int port;
    
} Server;

typedef void(*RequestHandler)(char*);

//Server server; // public server

void load_config(char* config_file);
void launch_server();
void bind_handler(RequestHandler request_handler);
int shutdown_server(int code);
