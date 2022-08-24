## Some Updates

3.add #include "underflow.h" to include the head file

2.add #define NULL ((void*)0) to define NULL

1.Change the order of the code to make Infer able to run

## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh ./examples/cttk_int31_ppp.c `|???s|???|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/cttk_int31_ppp.c`|1.959s|No issues found|
