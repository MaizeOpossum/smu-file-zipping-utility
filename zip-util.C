#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "miniz/miniz/miniz.h"

int main(int argc, char* argv[]) {
    int n = argc;

    if (n <= 2) {
        printf("usage: smu_zip_util [output name].zip [input file(s)]\n");
        return -1;
    }

    char * outname = argv[1];

    // zip file initialisation
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));

    bool init_passed = mz_zip_writer_init_file(&zip, outname, 0);
    if (!init_passed) {
        printf("Error initialising zip\n");
        return -1;
    }

    // zipping files into zip file
    for (int i = 2; i < n; i++) {
        char* filename = argv[i];

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

    return 0;
}
