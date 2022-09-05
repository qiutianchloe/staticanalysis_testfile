## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh  ./examples/use_after_free.c`|ms|no specification |
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/use_after_free.c`|24.12ms|1 issues found|
