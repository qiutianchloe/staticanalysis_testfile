## Results

|Tool|Command Line|exec time|issues found|Debug File|
|----------------|-------------------------------|-----------------------------|---------------------------|------|
|Underflow|`./Underflow.sh examples/db.c`|2045.27s|5 top-level insec & 5 conditional insec; 8 conditional err |results-db.txt|
|Pulse-x|`infer --pulse-isl --pulse-only --debug -- gcc -c -I./include/ ./examples/db.c`|76.281m|No issues found|db.html|






seccdb
  #(unique) top-level bugs:
    5 (5 insec; 0 err)
  #(unique) top-level conditional bugs:
    13 (5 insec; 8 err)
  #summs:
    401 (401; 138 ok; 255 insec; 8 err)
  time: 
    2045.27555082 (1593.029)
   maxwidth: 64

