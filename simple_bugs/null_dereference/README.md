## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh examples/null_dereference.c `|171ms|1 contracts|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c ./examples/null_dereference.c`|24.424ms|1 issue found|