## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|------|
|Underflow|`./Underflow.sh examples/ct_sort.c`|8.9 s|2 insec top-level(12 insec)|result-ct_sort.txt|
|Pulse-x|`infer  --pulse-isl --pulse-only -- gcc -c -I./include/ ./examples/ct_sort.c`| 132ms|No issues found|ct_sort.html|
