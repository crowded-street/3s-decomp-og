# 3s-decomp-og

You are helping to decompile Street Fighter III: 3rd Strike for CPS-3.

When asked to reverse engineer a function/symbol/file etc. you should use the decomp from ghidra-mcp as ground truth and 3SX project (found in ignored 3sx folder) as evidence. 

3SX is good evidence for:
- symbol names
- function signatures
- file boundaries and folder structure
- code style and formatting

If a function exists in 3SX, consult its structure to inform your code style. Don't just copy decomp straight from Ghidra

If you find new naming opportunities, be sure to report them to the user so they can apply them to the Ghidra project

To keep the project buildable when you add a call to a function that hasn't been decomped yet, add a stub in the corresponding file:
```c
void FUN_01234567(PLW* wk) {
    NOT_IMPLEMENTED;
}
```

## Rules

- Don't reorder symbols
- Don't assume type sizes will be the same as on CPS3
- Don't add unnecessary static asserts
- Don't write tests
- Don't document your findings in .md files unless asked
- Run clang-format after editing source files
- Don't add comments with ROM address. Instead add an entry to docs/symbols.md
- Follow docs/codestyle.md

## Tech stack

- C23
- CMake
- ghidra-mcp
