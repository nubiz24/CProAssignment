// filestat.c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>

const char *file_type(mode_t mode)
{
    if (S_ISREG(mode))
        return "Regular File";
    if (S_ISDIR(mode))
        return "Directory";
    if (S_ISLNK(mode))
        return "Symbolic Link";
    return "Unknown";
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./filestat <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[1];
    struct stat st;

    if (lstat(path, &st) != 0)
    {
        fprintf(stderr, "lstat failed on '%s': %s\n", path, strerror(errno));
        return EXIT_FAILURE;
    }

    // File Path
    printf("File Path: %s\n", path);

    // File Type
    printf("File Type: %s\n", file_type(st.st_mode));

    // Size
    printf("Size: %lld bytes\n", (long long)st.st_size);

    // Last Modified
    struct tm *tm_info = localtime(&st.st_mtime);
    if (tm_info == NULL)
    {
        // fallback: raw ctime
        char *raw = ctime(&st.st_mtime);
        if (raw)
            printf("Last Modified: %s", raw); // ctime adds newline
        else
            printf("Last Modified: (unable to format time)\n");
    }
    else
    {
        char buf[64];
        if (strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info) == 0)
        {
            printf("Last Modified: (time formatting error)\n");
        }
        else
        {
            printf("Last Modified: %s\n", buf);
        }
    }

    return EXIT_SUCCESS;
}
