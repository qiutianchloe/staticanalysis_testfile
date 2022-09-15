## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|------|
|Underflow|`./Underflow.sh examples/tea.c`|10.78 s|12 conditional err|results-tea.txt|
|Pulse-x|`infer  --pulse-isl --pulse-only --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 32 --pulse-max-disjuncts 37 -- gcc -c -I./include/ ./examples/tea.c`|227ms|No issues found|pulse_tea.html|
