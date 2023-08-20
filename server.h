typedef struct Server {
    char* hostname;
    int port;
    
} Server;

typedef void(*RequestHandler)(char*);

//Server server; // public server

void load_config(char* config_file);
void launch(char* hostname, int port);
void bind_handler(RequestHandler request_handler);
