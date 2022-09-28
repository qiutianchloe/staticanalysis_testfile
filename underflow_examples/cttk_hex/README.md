## Some Updates
2.change #include<stdio.h> to #define NULL ((void*)0)

1.Add #include<stdio.h> to handle use of undeclared identifier 'NULL' error warning

## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|-----|
|Underflow|`./Underflow.sh examples/cttk_hex.c`|206.18 s|9 top-level bugs|results-cttk_hex.txt|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 16 --pulse-max-disjuncts 82 --pulse-isl --pulse-only --debug -- gcc -c -I./include/ ./examples/cttk_hex.c`|517ms|No issues found|cttk_hex.html|



(unique) top-level bugs:
    9 (9 insec; 0 err)
(unique) top-level conditional bugs:
    19 (9 insec; 10 err)
summs:
    90 (90; 56 ok; 24 insec; 10 err)
time: 
    206.185855036 (86.228)
maxwidth: 64




./examples/cttk_hex.c
  cttk_hextobin_gen ... 
    cttk_hexval ... 
      cttk_u32_lt ... 
        cttk_u32_gt ... 
          cttk_bool_of_u32 ... 
          got 1 new specs for cttk_bool_of_u32
        got 1 new specs for cttk_u32_gt
      got 1 new specs for cttk_u32_lt
    got 1 new specs for cttk_hexval
  ⚡ insecure bug detected at line: 169, col: 14 reachable from cttk_hextobin_gen
  ⚡ insecure bug detected at line: 248, col: 6 reachable from cttk_hextobin_gen
  discovered 2 bugs (conditional: 14)  insecure: 2 (8 conditional)  
  discovered 30 contracts    err(insecure): 12   ok: 12   err(memory): 6  ❤   (time 71197 ms)
  Total solver time: 31498ms. Total solver calls: 729
  max observed width: 64
  cttk_bintohex_gen ... 
    cttk_hexdigit ... 
    got 3 new specs for cttk_hexdigit
  ⚡ insecure bug detected at line: 263, col: 6 reachable from cttk_bintohex_gen
  ⚡ insecure bug detected at line: 271, col: 6 reachable from cttk_bintohex_gen
  ⚡ insecure bug detected at line: 285, col: 6 reachable from cttk_bintohex_gen
  ⚡ insecure bug detected at line: 286, col: 7 reachable from cttk_bintohex_gen
  ⚡ insecure bug detected at line: 297, col: 14 reachable from cttk_bintohex_gen
  discovered 5 bugs (conditional: 5)  insecure: 5 (1 conditional)  
  discovered 54 contracts    err(insecure): 10   ok: 40   err(memory): 4  ❤   (time 75056 ms)
  Total solver time: 46251ms. Total solver calls: 947
  max observed width: 64
  main_bintohex ... 
    cttk_bintohex_gen ... 
    got 0 new specs for cttk_bintohex_gen
  discovered 0 bugs (conditional: 0)  
  discovered 0 contracts   ❤   (time 56064 ms)
  Total solver time: 8825ms. Total solver calls: 3430
  max observed width: 64
  cttk_hexscan ... 
  ⚡ insecure bug detected at line: 141, col: 14 reachable from cttk_hexscan
  discovered 1 bugs (conditional: 0)  insecure: 1 (0 conditional)  
  discovered 2 contracts    err(insecure): 1   ok: 1  ❤   (time 84 ms)
  Total solver time: 69ms. Total solver calls: 5
  max observed width: 64
  main_hextobin ... 
  ⚡ insecure bug detected at line: 187, col: 7 reachable from main_hextobin
  discovered 1 bugs (conditional: 0)  insecure: 1 (0 conditional)  
  discovered 2 contracts    err(insecure): 1   ok: 1  ❤   (time 629 ms)
  Total solver time: 390ms. Total solver calls: 30
  max observed width: 64
