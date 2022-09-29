## Some Updates

2.add #include "underflow.h" to include the head file

1.add #define NULL ((void*)0) to define NULL

## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|----|
|Underflow|`./Underflow.sh ./examples/libsodium_binhex.c`|246.66s|3 top level insec; 1 top level err& 4 conditional err|result-libsodium_binhex.txt|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/libsodium_binhex.c`|82.924ms|No issues found||
