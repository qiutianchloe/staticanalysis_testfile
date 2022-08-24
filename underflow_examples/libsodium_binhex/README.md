## Some Updates

2.add #include "underflow.h" to include the head file

1.add #define NULL ((void*)0) to define NULL

## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh ./examples/libsodium_binhex.c`|???s|???|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/libsodium_binhex.c`|82.924ms|No issues found|
