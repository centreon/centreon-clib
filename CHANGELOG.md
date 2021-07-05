# Changelog

## 20.10.2

### Bugfixes

*Libraries loading*

A library is loaded lazily now. This allows not to check all link issues during
the load.

## 20.10.1

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

## 20.10.0

`October 21, 2020`

### Bugfixes

*Deadlock removed*

A possible deadlock was removed when a process is added and at the same time
a process is removed because in timeout.
