## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh examples/array_out_of_bound.c`|74ms|1 bugs & 1 memory err|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c ./examples/array_out_of_bound.c`|26.63ms|No issues found|
