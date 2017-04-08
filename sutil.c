#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
print_stack(void)
{
    int j, nptrs;
#define SIZE 4098
    void *buffer[4098];
    char **strings;

    nptrs = backtrace(buffer, SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
       would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        return;
        //exit(EXIT_FAILURE);
    }

    FILE *fp = fopen("/home/dev/backtrace.log", "a");
    if (fp == NULL) {
        free(strings);
        return;
    }
    for (j = 0; j < nptrs; j++)
        fprintf(fp, "%s\n", strings[j]);
    fclose(fp);

    free(strings);
}


