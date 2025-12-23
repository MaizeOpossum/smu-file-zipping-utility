#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "helper.h"
#include "miniz/miniz/miniz.h"

int main() {
    // check directory for LT_FILES
    int FILES_cap = 0;
    char ** FILES = get_filenames(&FILES_cap);

    char * LT_FILE_name = validate_LT_FILES_presence(FILES);
    if (LT_FILE_name == NULL) {
        return 1;
    }

    FILE * LT_FILE = fopen(LT_FILE_name, "rb");;
    if (LT_FILE == NULL) {
        printf("Could not open %s\n", LT_FILE_name);
        return 1;
    }

    // get stuff from .LT_FILES
    // check for singular files
    char ** SINGULAR = check_SINGLE(LT_FILE);

    rewind(LT_FILE);

    // check for all
    char ** ALL = check_ALL(LT_FILE);

    // while(*ALL != NULL) {
    //     printf("%s", *ALL);
    //     ALL++;
    // }

    // hash to determine which file to involve
    bool involve[FILES_cap];
    for (int i = 0; i < FILES_cap; i++) {
        involve[i] = false;
    }

    // go through list and index all
    char ** ALLptr = ALL;
    while (*ALLptr != NULL) {
        for (int i = 0; i < FILES_cap; i++) {

            if (strstr(FILES[i], *ALLptr) != NULL) {
                involve[i] = true;
            }
        }

        ALLptr++;
    }

    // go through list and index singular, noting ones that are not included
    char ** SINGptr = SINGULAR;
    while (*SINGptr != NULL) {
        bool found = false;
        
        for (int i = 0; i < FILES_cap; i++) {
            if (!strcasecmp(*SINGptr, FILES[i])) {
                found = true;
                involve[i] = true;
            }
        }

        if (!found) {
            printf("file not found: %s\n", *SINGptr);
        }

        SINGptr++;
    }

    // initialise zip
    char studentID[14];
    printf("Enter your student ID: ");
    scanf(" %9s", studentID);
    strcat(studentID, ".zip");

    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));

    bool init_passed = mz_zip_writer_init_file(&zip, studentID, 0);
    if (!init_passed) {
        printf("Error initialising zip\n");
        return -1;
    }

    // zip files
    for (int i = 0; i < FILES_cap; i++) {
        char* filename = FILES[i];

        if (involve[i] == false) {
            continue;
        } else {
            printf("ZIPPED %s\n", filename);
        }

        FILE *fptr = fopen(filename, "rb");
        if (fptr == NULL) {
            printf("%s not found, zipping without %s\n", filename, filename);
            continue;
        }

        // find size of the file
        fseek(fptr, 0, SEEK_END);
        int size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);
        char * buffer = malloc(size);

        fread(buffer, 1, size, fptr);

        mz_zip_writer_add_mem(&zip, filename, buffer, size, MZ_BEST_COMPRESSION);

        free(buffer);
        fclose(fptr); // close file
    }

    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);

    free_lists(FILES);
    free_lists(ALL);
    free_lists(SINGULAR);
}