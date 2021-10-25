# Changelog

## 20.04.4

### Bugfixes

*Deadlock removed*

some logs mutex needs to be recursive, because sometimes we create logs, that log
informations.
## 20.04.3

### Bugfixes

*Deadlock removed*

The logs mutex needs to be recursive, because sometimes we create logs, that log
informations.

*Deadlock removed*

This one is in the process class. When the process is stopping and we write to
its stdin, we could arrive to a deadlock.

Another one in the process\_manager class is also fixed.

*Fast processes*

If process fastly writes to stdout and then exits, process\_manager could miss
the output.

## 20.04.2

### Enhancement

No change concerning the code. This is the first time, we provide this library
compiled using C++14 with the last C++ ABI. The binary changes needed a new
version.

## 20.04.1

`February x, 2021`

### Bugfixes

*Deadlock removed*

Start/Stop process\_manager mechanism is rewritten and much more simpler. The
consequences are that there are less dead locks in the processes management.

The process manager calls waitpid with the NOHANG flag, so that it cannot be
blocked in this call.

*Timestamp*

The simple cases that are addition, subtraction and some others cases, have
their computations simplified, that is to say less computations, so faster.

## 20.04.0

`April 22, 2020`

### Bugfixes

*Deadlock removed*

A possible deadlock was removed when a process is added and at the same time
a process is removed because in timeout.
