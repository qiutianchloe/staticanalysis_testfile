# staticanalysis_testfile
This research seeks to investigate the empirically understanding of strengths and weaknesses of top-down, contextual analysis versus bottom-up analysis as embodied by Underflow and Pulse-X respectively. In what situations does each technique perform best and perform less well? 

# Process
The research will process in two stages. In stage 1, Collect Sample programs to evaluate both tools on. In stage 2, Run each tool on the sample programs under various configurations.

### Stage 1: Collect Sample Programs to Evaluate Both Tools on

Both Underflow and Pulse-X each have their example programs to demonstrate concepts. Underflow has been applied in 11 well-selected C language programs as case studies, and Pulse-X is applied on OpenSSL and some program examples with different programming languages. However, Besides some memory-safety issues like the null dereference that both tools can detect, many Underflow example programs have information leakage vulnerabilities that Pulse-X cannot detect. Similarly, Underflow can only detect C-like program language; some of Pulse-X’s java examples can not use directly. This stage aims to collect sample programs befitting for both tools and modify some sample programs if necessary.

### Stage 2: Run Each of the Tools on the Sample Programs under Various Configurations

Underflow and Pulse-X each have various configuration options that can modify to detect programs’ vulnerabilities differently because some functionalities are set disabled by default in both tools. For example, Pulse-X “Incorrectness Separation Logic mode” is set disable by default for experiments only. After collecting proper sample programs for both tools at stage 1, This stage aims to read the documents of both tools and modify their configurations to the desired mode to evaluate their performance.

In planning, metrics of tool performance are 1) true-positive rate of reported vulnerabilities and 2) execution time. Whether the potential security vulnerabilities are being reported precisely is the original intention of these tools. As for the execution time, if the tools are used in industry code review progress, the execution time should be limited to several minutes instead of several hours because of the rapid software development process.
The metrics might change as research progresses.

### Here are all the examples we are currently working on and its process states
## Underflow Examples
|Underflow Example File|Current State(Pulse-X)|
|----------------|-------------------------------|
|ackermann.c|`Not work`|
|arrays.c|`Not work`|
|auction.c|`No issues found`|
|break_continue.c|`No issues found`|
|ct_openssl_utility.c|`No issues found`|
|ct_select.c|`No issues found`|
|ct_sort.c|`No issues found`|
|ct_ssl3_cbc_remove_padding.c|`Not work`|
|cttk_hex.c|`Not work`|
|cttk_inner.c|`No issues found`|
|cttk_int31_pp.c|`Not work`|
|cttk_oram1.c|`Not work`|
|db.c|`No issues found`|
|Hacl_Policies.c|`No issues found`|
|insec.c|`3 issues found`|
|kremlib_base.c|`No issues found`|
|libsodium_binhex.c|`Not work`|
|libsodium_memcmp.c|`No issues found`|
|location-server.c|`No issues found`|
|pd.c|`Not work`|
|stack_addr.c|`No issues found`|
|tea.c|`No issues found`|
|tls_cbc_remove_padding_luck13.c(version we modified at 19/5)|`No issues found`|
|tls_cbc_remove_padding_patch.c|`Not work`|
|unreachable.c|`No issues found`|
|words_casts.c|`Not work`|


## Simple_Bugs
|File|Underflow State|Pulse-X State|
|--|--|--|
|array_out_of_bound.c|1 issue found|No issues found|
|null_dereference.c|1 contract err found|1 issue found|
