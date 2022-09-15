## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|------|
|Underflow|`./Underflow.sh ./examples/cttk_inner.c`|10.34s|No issues found, 3 ok summs|result-ct_inner.txt|
|Pulse-x|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 100 --pulse-max-disjuncts 100 --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/cttk_inner.c `|315ms|No issues found|Pulse_cttk_inner.html|
|Pulse-x with debug|`infer --pulse-model-skip-pattern "LOW" --pulse-model-alloc-pattern "alloc" --pulse-widen-threshold 100 --pulse-max-disjuncts 100 --pulse-isl --pulse-only --debug -- gcc -c -I./include/ ./examples/cttk_inner.c`|1min3s|No issues found|Pulse_cttk_inner.html|
