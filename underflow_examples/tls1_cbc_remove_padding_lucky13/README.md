## Some Updates
 
 - 2/9 test the file with bug at different place
    - Infer works on the loop as we expected
    - Infer can't work out with some statement(s->options&0x00000200, s->s3->flags & 0x0008, rec->data = data)

 - 29/8 try to workout with bufferoverflow

 - 19/8 We modified tls1_cbc_remove_padding_lucky13.c executable for Pulse-x

## Results

|Tool|command Line|exec time  |issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|-----|
|Underflow|`./Underflow.sh ./examples/tls1_cbc_remove_padding_lucky13.c`|123.67s|4 top-level insec & 1 top-level err|results-tls1_cbc_remove_padding_lucky13.txt|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 8 --pulse-max-disjuncts 16  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/tls1_cbc_remove_padding_lucky13_withtest.c`|54.882ms|1 uninitialized variable and 1 memory leakage|tls1_cbc_remove_padding_lucky13.html|
|Infer default mode and enable bufferoverrun |`infer --bufferoverrun -- gcc -c -I./include/ ./examples/tls1_cbc_remove_padding_lucky13.c`|264ms|1 UNINITIALIZED_VALUE issue found|
|Infer with only bufferoverrun |`infer --bufferoverrun --bufferoverrun-only -- gcc -c -I./include/ ./examples/tls1_cbc_remove_padding_lucky13.c`|34.446ms|0|
