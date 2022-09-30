## Some Updates

3.change the 'unsigned char [8]' to *unsigned char

2.add #include "underflow.h" to include the head file

1.add #define NULL ((void*)0) to define NULL

## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|-----|
|Underflow|`./Underflow.sh ./examples/tls1_cbc_remove_padding_patch.c`|138.0s|2 top-level insec|results-tls1_cbc_remove_padding_patch.txt|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/tls1_cbc_remove_padding_patch.c `|64.472ms|No issues found||
