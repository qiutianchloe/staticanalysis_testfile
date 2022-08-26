## Some Updates

2.change the name three test functions

1.add #include "underflow.h" to include the head file

## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh ./examples/words_casts`|???s|???|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/words_casts.c`|34.757ms|No issues found|
