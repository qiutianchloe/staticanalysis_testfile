## Results

|Tool|command Line|exec time  |issues found                         |
|----------------|-------------------------------|-----------------------------|---------------------------|
|Underflow|`./Underflow.sh  ./examples/double_free.c`|1.32 s|1 top level bug|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/double_free.c`|30.155ms|1 USE_AFTER_FREE issues found|
