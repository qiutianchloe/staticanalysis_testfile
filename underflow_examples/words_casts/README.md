## Some Updates

2.change the name three test functions

1.add #include "underflow.h" to include the head file

## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|----|
|Underflow|`./Underflow.sh ./examples/words_casts`|1.95s|No issues found|results-wordcasts.txt|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/words_casts.c`|34.757ms|No issues found||
