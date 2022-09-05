## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh  ./examples/double_free.c`|ms|no specification |
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/double_free.c`|30.155ms|1 issues found|
