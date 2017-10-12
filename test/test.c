#include <stdio.h>
//#include "sutil.h"
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
print_stack(void)
{
    int j, nptrs;
//#define SIZE 4098
#define SIZE 1
    //void *buffer[4098];
    void *buffer[1];
    char **strings;

    nptrs = backtrace(buffer, SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
       would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        return;
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen("/home/dev/backtrace.log", "a");
    if (fp == NULL) {
        return;
    }
    for (j = 0; j < nptrs; j++)
        fprintf(fp, "%s\n", strings[j]);
    fclose(fp);

    free(strings);
}
int main() {
    print_stack();
    //char *str[] = {"hello"};
    //char (*str)[] = {"hello"};
    //printf("%s\n", str[0]);

    return 0;
}
