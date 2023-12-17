void str_cpy(char* dest, char* src, unsigned int n);
unsigned int str_len(char* str);
int str_cmp(char* lhs, char* rhs);
int str_n_cmp(char* lhs, char* rhs, int n);
void str_cat(char* dest, char* src, char** end_ptr);
void bin_cat(char* dest, char* src, char** end_ptr, long length);
char* pread_file(char* filepath, long* len, char* type);
