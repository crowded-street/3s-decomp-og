#include "common.h"

#include <stdio.h>
#include <stdlib.h>

[[noreturn]] void decomp_not_implemented(const char* symbol) {
    fprintf(stderr, "%s is not implemented\n", symbol);
    abort();
}
