## Some Updates

2.add #include "underflow.h" to include the head file

1.add #define NULL ((void*)0) to define NULL

## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|----|
|Underflow|`./Underflow.sh ./examples/libsodium_memcmp.c`|61.44s|1 top level insec &  2 conditional err|results-libsodium_memcmp.txt|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 64 --pulse-max-disjuncts 69 --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/libsodium_memcmp.c`|248ms|No issues found|libsodium_memcmp.html|
