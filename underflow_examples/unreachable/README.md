## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|---|
|Underflow|`./Underflow.sh ./examples/unreachable.c`|1s|No issues found (0 summs)|results-unreachable.txt|
|Pulse-x|`infer --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/unreachable.c`|28.588ms|No issues found|pulse_unreachable.html|
