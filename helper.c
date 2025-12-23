#include <stdio.h>
#include <dirent.h> 
#include <stdlib.h>
#include <string.h>

int validate_file_presence(int n, char * argv[]) {
    // function to validate the presence of the named files
    // returns -1 if file is not present
    // returns 0 for normal operation

    int returnval = 0;
    for (int i = 1; i < n; i++) {
        char* filename = argv[i];

        FILE *fptr = fopen(filename, "rb");
        if (fptr == NULL) {
            printf("%s not found\n", filename);
            returnval = -1;
        }
    }

    return returnval;
}
char * validate_LT_FILES_presence(char ** files) {
    /* O(n) search for .LT_FILES
        will use the first instance
        warning when there are more than one instance of .LT_FILES
        returns the .LT_FILES file name
    */ 

    char ** fptr = files;
    char * haystack = ".LT_FILES";
    int count = 0;
    char * filename;

    while (*fptr != NULL) {
        if (strstr(*fptr, haystack) != NULL) {
            count++;
            
            if (count == 1) {
                filename = malloc(strlen(*fptr) + 1);
                strcpy(filename, *fptr);
            }
        }

        fptr++;
    }

    if (count == 0) {
        printf("No .LT_FILES found\n");
        return NULL;
    }

    if (count > 1) {
        printf("more than one instance of .LT_FILES found, will use %s\n", filename);
    }

    return filename;
}
int validate_LT_FILES_presence_archive(int n, char * argv[]) {
    // function to validate the presence of the .LT_FILES file
    // returns -1 if file is not present
    // returns 0 for normal operation

    int returnval = 0;
    for (int i = 1; i < n; i++) {
        char* filename = argv[i];

        FILE *fptr = fopen(filename, "rb");
        if (fptr == NULL) {
            printf("%s not found\n", filename);
            returnval = -1;
        }
    }

    return returnval;
}

// file directory manipulation
void grow (char*** lst, int * max_cap) {
    int growth_factor = 2;
    *max_cap *= growth_factor;

    *lst = realloc(*lst, *max_cap * sizeof(char *));
    (*lst)[*max_cap - 1] = NULL;
}

char ** get_filenames (int * cap) {
    // get the filenames, needs to be freed
    // return NULL for error
    int max_cap = 2;
    *cap = 0;

    DIR *dir = opendir(".");
    if (!dir) {
        printf("could not open directory\n");
        return NULL;
    }

    struct dirent * entry = readdir(dir);
    char ** ans = malloc(2 * sizeof(char *));

    while (entry != NULL) {
        if (*cap == max_cap - 1) {
            grow(&ans, &max_cap);
        }

        char * filename = entry -> d_name;
        ans[*cap] = malloc(strlen(filename) + 1);
        strcpy(ans[*cap], filename);

        (*cap)++;
        entry = readdir(dir);
    }

    ans[*cap] = NULL;

    closedir(dir);
    return ans;
}

void free_lists(char ** filenames) {
    char ** ptr = filenames;
    while (*ptr != NULL) {
        free(*ptr);
        ptr++;
    }
    free(filenames);
}

char ** check_ALL(FILE * stream) {
    // returns all lines with * op
    // assumes that double \n is used correctly
    char buff[100];

    char * stat = fgets(buff, 100, stream);

    int cap = 0;
    int max_cap = 2;
    char ** ans = malloc(sizeof(char *) * max_cap);
    
    while (stat != NULL) {
        if (buff[0] == '\n') {
            stat = fgets(buff, 100, stream);
            while (stat != NULL) {
                if (cap == max_cap - 1) {
                    grow(&ans, &max_cap);
                }

                if (strlen(buff) > 0 && buff[strlen(buff) - 1] == '\n') {
                    buff[strlen(buff) - 1] = '\0';
                }

                ans[cap] = malloc(strlen(buff) + 1);
                strcpy(ans[cap], &(buff[1]));

                stat = fgets(buff, 100, stream);
                
                cap++;
            }

            ans[cap] = NULL;
            return ans;
        }

        stat = fgets(buff, 100, stream);
    }

    free(ans);
    return NULL;
}

char ** check_SINGLE(FILE * stream) {
    char buff[100];
    char * stat = fgets(buff, 100, stream);
    int cap = 0;
    int max_cap = 2;
    char ** ans = malloc(sizeof(char *) * max_cap);

    while (stat != NULL) {
        if (cap == max_cap - 1) {
            grow(&ans, &max_cap);
        }

        ans[cap] = malloc(strlen(buff) + 1);
        if (strlen(buff) > 0 && buff[strlen(buff) - 1] == '\n') {
            buff[strlen(buff) - 1] = '\0';
        }
        strcpy(ans[cap], buff);
        cap++;

        stat = fgets(buff, 100, stream);
        if (stat != NULL && buff[0] == '\n') {
            ans[cap] = NULL;
            return ans;
        }
    }

    ans[cap] = NULL;
    return ans;
}

void zip_all(char * ext) {

}