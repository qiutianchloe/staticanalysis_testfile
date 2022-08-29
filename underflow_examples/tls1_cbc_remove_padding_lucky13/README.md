## Some Updates

 - 19/8 We modified tls1_cbc_remove_padding_lucky13.c executable for Pulse-x

## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`command Line`            |          ||
|Pulse-x|`infer --pulse-model-skip-pattern "LOW"  --pulse-model-alloc-pattern "alloc"  --pulse-widen-threshold 128 --pulse-max-disjuncts 128  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/tls1_cbc_remove_padding_lucky13.c`         |140ms       |0|
|Infer default mode and enable bufferoverrun |`infer --bufferoverrun -- gcc -c -I./include/ ./examples/tls1_cbc_remove_padding_lucky13.c`|264ms|1 UNINITIALIZED_VALUE issue found|
|Infer with only bufferoverrun |`infer --bufferoverrun --bufferoverrun-only -- gcc -c -I./include/ ./examples/tls1_cbc_remove_padding_lucky13.c`|34.446ms|0|
