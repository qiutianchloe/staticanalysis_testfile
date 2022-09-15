## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|---|
|Underflow|`./Underflow.sh examples/insec.c `|6.224 s|1 top-level err & 1 conditional memory & 1 conditional insecr||
|Pulse-x|`infer  --pulse-isl --pulse-only -- gcc -c -I../include/ ./examples/insec.c`|68.614ms|3 USE_AFTER_FREE issues found||



  false_negative ... 
  discovered 0 bugs (conditional: 0)  
  discovered 0 contracts   ❤   (time 4537 ms)
  Total solver time: 2251ms. Total solver calls: 387
  max observed width: 64
  isl_push_back ... 
  ⚡ memory bug detected at line: 448, col: 5 reachable from isl_push_back
  discovered 1 bugs (conditional: 0)  memory: 1 (0 conditional)  
  discovered 1 contracts    err(memory): 1  ❤   (time 144 ms)
  Total solver time: 64ms. Total solver calls: 4
  max observed width: 64
  load_and_branch ... 
  discovered 0 bugs (conditional: 2)  
  discovered 4 contracts    err(insecure): 1   ok: 2   err(memory): 1  ❤   (time 176 ms)
  Total solver time: 138ms. Total solver calls: 8
  max observed width: 64
