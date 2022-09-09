#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#define PATH "/tmp/qperrog/level1/level2"
#define NAME "buffer.bin"
#define F PATH "/" NAME

static void dmce_mkdir(char const* path) {
    char const* pos_path = path;

    char* dir = calloc(strlen(path) + 1, sizeof(char));
    char* pos_dir = dir;

    while (*pos_path != '\0') {
        if (*pos_path == '/') {
            mkdir(dir, S_IRWXU);
        }
        *pos_dir = *pos_path;
        pos_dir++;
        pos_path++;
    }

    mkdir(dir, S_IRWXU);
    free(dir);
}

int main (void)
{
    FILE* fp;

    dmce_mkdir(PATH);
    fp = fopen(F, "w");

    printf("fp %ld errno %d\n", (long int)fp, errno);

    return 0;
}
