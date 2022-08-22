## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh examples/ct_select.c`|73ms|1 insecure|
|Pulse-x|`infer  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/ct_select.c`|41.51ms|No issues found|
