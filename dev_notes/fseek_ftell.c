#include <stdio.h>
#include <string.h>

int main() {
    FILE * inp = fopen("notes.txt", "rb");
    fseek(inp, 0, SEEK_END);
    int n = ftell(inp);
    fseek(inp, 0, SEEK_SET);

    char data[20];
    memset(data, 0, sizeof(data));
    fread(data, 1, 19, inp);

    printf("%s\n", data);

    printf("%d\n", n);
}