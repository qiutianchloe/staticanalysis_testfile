## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|------|
|Underflow|`./Underflow.sh examples/db.c`|||results-db.txt|
|Pulse-x|`infer --pulse-isl --pulse-only --debug -- gcc -c -I./include/ ./examples/db.c`|76.281m|No issues found|db.html|
