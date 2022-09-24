## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh ./examples/loop_with_if.c`|344ms|1 memory err found|
|Pulse-x|`infer --pulse-widen-threshold 3 --pulse-max-disjuncts 5 --pulse-isl --pulse-only -debug -- gcc -c ./examples/loop_with_if.c`|91.685ms|1 issue found|
