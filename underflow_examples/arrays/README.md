## Some Updates

1.add #include "underflow.h" to include the head file

## Results

|Tool|Command Line|exec time|issues found|debug report|
|----------------|-------------------------------|-----------------------------|---------------------------|-----------|
|Underflow|`./Underflow.sh  ./examples/arrays.c `|1117 ms|1 bug and 1 memory and 1 condition error|result-arrays.txt|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/arrays.c`|29.095ms|No issues found|arrays_pulse.html|
|Pulse-x|`infer --bufferoverrun-only -- gcc -c -I./include/ ./examples/arrays.c `|27.808ms|Buffer Overrun L2|arrays_bufferoverrun.html|



./Underflow.sh  ./examples/arrays.c    
./examples/arrays.c
  main2_error ... 
    memset32 ... 
    got 2 new specs for memset32
  ⚡ memory bug detected at line: 13, col: 5 reachable from main2_error
  discovered 1 bugs (conditional: 0)  memory: 1 (0 conditional)  
  discovered 1 contracts    err(memory): 1  ❤   (time 1117 ms)
  Total solver time: 363ms. Total solver calls: 64
  max observed width: 10
  main ... 
  discovered 0 bugs (conditional: 0)  
  discovered 1 contracts    ok: 1  ❤   (time 72 ms)
  Total solver time: 31ms. Total solver calls: 4
  max observed width: 10
