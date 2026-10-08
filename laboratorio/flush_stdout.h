#include <stdio.h>

#define printf(...) (fflush(stdout), printf(__VA_ARGS__), fflush(stdout))
