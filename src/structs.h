#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"

// Partial work types containing the fields reconstructed so far.
typedef struct {
    u8 operator;
    s16 routine_no[8];
} WORK;

typedef struct {
    WORK wu;
} PLW;

typedef struct {
    s8 stage;
    s8 area;
    s16 unk_4a;
} BG;

#endif
