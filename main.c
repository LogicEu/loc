#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t loc_count(FILE* file)
{
    char c;
    size_t count = 0;
    if ((c = fgetc(file)) == EOF) {
        return count;
    }

    do {
        count += (c == '\n');
    } while ((c = fgetc(file)) != EOF);
    return count;
}

static int loc_print(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file) {
        return EXIT_FAILURE;
    }
    
    const size_t loc = loc_count(file);
    fprintf(stdout, "%s -> %zu loc\n", path, loc);
    fclose(file);
    return EXIT_SUCCESS;
}

int main(const int argc, const char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "loc: missing input file. Use with: 'loc <file>'\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        if (loc_print(argv[i]) != EXIT_SUCCESS) {
            fprintf(stderr, "loc: could not open file: %s\n", argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
