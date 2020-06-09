#include <stdio.h>

#define k_Logf(...) \
    fprintf(stdout, "\e[1;37;42m[kore:message]\e[0m  " __VA_ARGS__)

#define k_LogErrorf(...) \
    fprintf(stderr, "\e[1;37;41m[kore:error]\e[0m    " __VA_ARGS__)

#define k_LogWarningf(...) \
    fprintf(stderr, "\e[1;37;43/m[kore:warning]\e[0m " __VA_ARGS__)
