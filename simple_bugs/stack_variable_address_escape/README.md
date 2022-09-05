## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh  ./examples/stack_variable_address_escape.c`|21ms|1 ok contract|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/stack_variable_address_escape.c`|25.349m|1 issue found|
