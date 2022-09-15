## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|------|
|Underflow|`./Underflow.sh examples/Hacl_Policies.c`|26.3 s|0 issues found & 1 ok summs|results-Hacl_Policies.txt|
|Pulse-x|`infer  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/Hacl_Policies.c`|43.322ms|No issues found|Pulse_Hacl_Policies.html|
