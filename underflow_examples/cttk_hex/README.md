## Add #include<stdio.h> to handle use of undeclared identifier 'NULL' error warning

## Results

|Tool|Command Line|exec time|issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh examples/cttk_hex.c`|???ms|???|
|Pulse-x|`infer  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/cttk_hex.c`|109ms|No issues found|
|Pulse-x|`
infer --pulse-model-skip-pattern "LOW"  --pulse-model-alloc-pattern "alloc"  --pulse-widen-threshold 128 --pulse-max-disjuncts 128  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/cttk_hex.c`|783ms|No issues found|
