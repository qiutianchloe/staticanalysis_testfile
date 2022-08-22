## Add #include<stdio.h> to handle use of undeclared identifier 'NULL' error warning

## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh examples/cttk_hex.c`|???ms|???|
|Pulse-x|`infer  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/cttk_hex.c`|109ms|No issues found|
