## Some Updates

1.add #include "underflow.h" to include the head file

## Results

|Tool|Command Line|exec time|issues found|debug report|
|----------------|-------------------------------|-----------------------------|---------------------------|-----------|
|Underflow|`./Underflow.sh ./examples/auction.c`|229.553s| 1 insec top-level & 58 insec|result-auction.txt|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 500 --pulse-max-disjuncts 500 --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/auction.c`|4.458s|1 MEMORY_LEAK|arrays_pulse.html|



./examples/auction.c
  get_winner_with_reserve ... 
  discovered 0 bugs (conditional: 8)  
  discovered 12 contracts    err(insecure): 3   ok: 4   err(memory): 5  ❤   (time 720 ms)
  Total solver time: 352ms. Total solver calls: 32
  max observed width: 1
  idqt_max_ct ... 
  discovered 0 bugs (conditional: 4)  
  discovered 5 contracts    ok: 1   err(memory): 4  ❤   (time 218 ms)
  Total solver time: 127ms. Total solver calls: 17
  max observed width: 1
  run_auction ... 
    start_auction ... 
    got 1 new specs for start_auction
    register_bid ... 
    got 1 new specs for register_bid
    register_bid ... 
      idqt_max ... 
      got 3 new specs for idqt_max
    got 3 new specs for register_bid
    close_auction_and_get_winner ... 
    got 1 new specs for close_auction_and_get_winner
    close_auction_and_get_winner ... 
    got 1 new specs for close_auction_and_get_winner
  ⚡ insecure bug detected at line: 62, col: 7 reachable from run_auction
  discovered 1 bugs (conditional: 0)  insecure: 1 (0 conditional)  
  discovered 124 contracts    ok: 64   err(insecure): 60  ❤   (time 230546 ms)
  Total solver time: 189983ms. Total solver calls: 1383
  max observed width: 64
  close_auction ... 
  discovered 0 bugs (conditional: 3)  
  discovered 6 contracts    err(insecure): 2   ok: 3   err(memory): 1  ❤   (time 246 ms)
  Total solver time: 209ms. Total solver calls: 15
  max observed width: 64
specifications output to results-20220912-102425.txt