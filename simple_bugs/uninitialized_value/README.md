## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh  ./examples/uninitialized_value.c `|165ms|1 ok contracts|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/uninitialized_value.c`|24.483ms|No issues found|
