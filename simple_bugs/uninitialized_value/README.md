## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh  ./examples/uninitialized_value.c `|165ms|1 ok contracts|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/uninitialized_value.c`|48.483ms|1 issues found|


The result is different from what I figure out two weeks ago :<
