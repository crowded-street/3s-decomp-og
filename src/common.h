#ifndef COMMON_H
#define COMMON_H

#include "types.h"

[[noreturn]] void decomp_not_implemented(const char* symbol);
#define NOT_IMPLEMENTED decomp_not_implemented(__func__)

#endif
