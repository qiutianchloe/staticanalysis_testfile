## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|---------|
|Underflow|`./Underflow.sh ./examples/break_continue.c`|375ms|1 ok contracts|result-breaking_continue|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/break_continue.c`|30.189ms|No issues found|pulse_break_continue.html|
|Buffer Overrun|`infer --bufferoverrun-only --bo-field-depth-limit 200 -- gcc -c -I./include/ ./examples/break_continue.c `|24.731ms|No issues found|bufferoverrun_break_continue.html|


./examples/break_continue.c
  test1 ... 
  discovered 0 bugs (conditional: 0)  
  discovered 1 contracts    ok: 1  ❤   (time 902 ms)
  Total solver time: 375ms. Total solver calls: 61
  max observed width: 7
specifications output to results-20220912-120604.txt