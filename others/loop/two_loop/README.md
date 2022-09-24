## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh ./examples/two_loop.c`|941 ms|1 memory err found|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 5 --pulse-max-disjuncts 6 --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/two_loop.c`|26.252ms|2 issue found|
