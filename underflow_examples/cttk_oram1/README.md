## Some Updates

1.Change the order of the code to make Infer able to run

## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh ./examples/cttk_oram1.c`|???s|???|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/cttk_oram1.c`|133ms|No issues found|
