## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh  ./examples/use_after_lifetime.c `| 235 ms|1 ok contract|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/use_after_lifetime.c`|23.915ms|No issues found|
