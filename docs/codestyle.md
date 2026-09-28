# Codestyle

## No void parameters

Don't use void parameters

## Whitespace

Separate define guards and closing `#endif` from other code by a single newline:
```c
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#endif
```

Separate blocks from other code:
```c
int a = 3;

if (a == 2) {
    if (a != 1) {
        a = 1;
    }

    a = 7;
}

a = 0;
```

Separate types from other code

Don't separate with more than one newline

## Includes

Separate includes into three groups in this order:
1. Local headers
2. Library headers (e.g. SDL)
3. System headers (e.g. stdio)

## Hex literals

Use uppercase hex literals:
- Good: `0xABC`
- Bad: `0xabc`

## Redundant returns

Don't add redundant returns where control flow would naturally exit the function
