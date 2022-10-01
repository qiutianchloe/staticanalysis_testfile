## Some Updates

1.Change the order of the code to make Infer able to run

## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|------|
|Underflow|`./Underflow.sh ./examples/cttk_oram1.c`|91.56 s|3 insec top-level bugs & 2 conditional error|results-cttk_oram1.txt|
|Pulse-x|`infer --pulse-isl --pulse-only --pulse-widen-threshold 8 --pulse-max-disjuncts 31 -- gcc -c -I./include/ ./examples/cttk_oram1.c`|133ms|No issues found|cttk_oram1.html|


./examples/cttk_oram1.c
  main_array_eq ... 
    cttk_array_eq ... 
      cttk_u32_eq0 ... 
        cttk_u32_neq0 ... 
          cttk_bool_of_u32 ... 
          got 1 new specs for cttk_bool_of_u32
        got 1 new specs for cttk_u32_neq0
        cttk_not ... 
        got 1 new specs for cttk_not
      got 1 new specs for cttk_u32_eq0
    got 1 new specs for cttk_array_eq
  discovered 0 bugs (conditional: 0)  
  discovered 1 contracts    ok: 1  ❤   (time 3442 ms)
  Total solver time: 863ms. Total solver calls: 176
  max observed width: 8
  main_array_read ... 
    cttk_array_read ... 
      memset ... 
      got 1 new specs for memset
      cttk_u64_eq ... 
        cttk_u64_eq0 ... 
          cttk_u64_neq0 ... 
          got 1 new specs for cttk_u64_neq0
        got 1 new specs for cttk_u64_eq0
      got 1 new specs for cttk_u64_eq
      cttk_cond_copy ... 
      got 3 new specs for cttk_cond_copy
      cttk_cond_copy ... 
      got 0 new specs for cttk_cond_copy
      cttk_cond_copy ... 
      got 0 new specs for cttk_cond_copy
    got 1 new specs for cttk_array_read
  ⚡ insecure bug detected at line: 68, col: 6 reachable from main_array_read
  discovered 1 bugs (conditional: 0)  insecure: 1 (0 conditional)  
  discovered 1 contracts    err(insecure): 1  ❤   (time 10485 ms)
  Total solver time: 2642ms. Total solver calls: 759
  max observed width: 8
  main_array_cmp ... 
    cttk_array_cmp ... 
    got 1 new specs for cttk_array_cmp
  discovered 0 bugs (conditional: 0)  
  discovered 1 contracts    ok: 1  ❤   (time 2970 ms)
  Total solver time: 825ms. Total solver calls: 174
  max observed width: 8
  cttk_cond_swap ... 
  ⚡ insecure bug detected at line: 107, col: 14 reachable from cttk_cond_swap
  discovered 1 bugs (conditional: 2)  insecure: 1 (0 conditional)  
  discovered 53 contracts    err(insecure): 1   ok: 50   err(memory): 2  ❤   (time 68707 ms)
  Total solver time: 34482ms. Total solver calls: 554
  max observed width: 50
  main_array_write ... 
    cttk_array_write ... 
      cttk_cond_copy ... 
      got 0 new specs for cttk_cond_copy
      cttk_cond_copy ... 
      got 0 new specs for cttk_cond_copy
    got 1 new specs for cttk_array_write
  ⚡ insecure bug detected at line: 68, col: 6 reachable from main_array_write
  discovered 1 bugs (conditional: 0)  insecure: 1 (0 conditional)  
  discovered 1 contracts    err(insecure): 1  ❤   (time 4436 ms)
  Total solver time: 923ms. Total solver calls: 257
  max observed width: 50
specifications output to results-20220915-201701.txt