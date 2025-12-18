#include <stdio.h>

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
