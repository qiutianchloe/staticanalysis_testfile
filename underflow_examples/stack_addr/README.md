## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|---|
|Underflow|`./Underflow.sh ./examples/stack_addr.c`|1.45s|No issues found (2 ok)|results-stack_addr.txt|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/stack_addr.c`|25.146ms|No issues found|pulse_stack_addr.html|
