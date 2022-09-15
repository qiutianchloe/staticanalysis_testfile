## Some Updates

2.add #include "underflow.h" to include the head file

1.add #define NULL ((void*)0) to define NULL

## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|----|
|Underflow|`./Underflow.sh ./examples/ct_ssl3_cbc_remove_padding.c`|18.33s|No issues found|results-ct_ssl3_cbc_remove_padding.txt|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 0 --pulse-max-disjuncts 1 --pulse-isl --pulse-only --debug -- gcc -c -I./include/ ./examples/ct_ssl3_cbc_remove_padding.c`|56.806ms|1 Memory Leak|pulse_ct_ssl3_cbc_remove_padding.html|
