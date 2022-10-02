## Some Updates

2.add null pointer dereference after the recursion

1.add #include "underflow.h" to include the head file

## Results

|Tool|Command Line|exec time|issues found|debug report|
|----------------|-------------------------------|-----------------------------|---------------------------|-------------------|
|Underflow|`./Underflow.sh ./examples/ackermann.c`|72459ms|No Issues found|result-ackermann.txt|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/ackermann.c`|31.245ms|No issues found|ackermann.html|
|Underflow|`./Underflow.sh ./examples/ackermann.c`|286ms|No Issues found|result-ackermann.txt|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 0 --pulse-max-disjuncts 1 --pulse-isl --pulse-only --debug -- gcc -c -I./include/ ./examples/ackermann.c `|245ms|1 NULLPTR_DEREFERENCE|ackermann.html|


Underflow
  discovered 0 bugs (conditional: 0)  
  discovered 3 contracts    ok: 3  ❤   (time 795760 ms)
  Total solver time: 72459ms. Total solver calls: 36300
  max observed width: 64
