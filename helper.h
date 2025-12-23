char * validate_LT_FILES_presence(char ** FILES);
char ** get_filenames (int * cap);
char ** check_ALL(FILE * stream);
char ** check_SINGLE(FILE * stream);
void free_lists(char ** filenames);
