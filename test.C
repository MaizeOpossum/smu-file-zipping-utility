
#include <stdio.h>
#include "miniz/miniz/miniz.h"


int main(int argc, char* argv[]) {
    mz_zip_archive zip; // defines a zip object
    memset(&zip, 0, sizeof(zip)); // allocates memory for it

    if (!mz_zip_writer_init_file(&zip, "test.zip", 0)) {
        return 1;
    }

    const char *msg = "Hello from miniz!";
    mz_zip_writer_add_mem(
        &zip,
        "hello.txt",
        msg,
        strlen(msg),
        MZ_BEST_COMPRESSION
    );

    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);

    return 0;
}
