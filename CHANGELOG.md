# Changelog

## 20.10.5

### Bug fixes

*Deadlock removed*

A mutex in the log engine needs to be recursive, because sometimes we create logs, that log
informations.
## 20.10.4

### Bug fixes

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

## 20.10.3

### Bug fixes

*Libraries loading*

libraries are loaded lazily now. This allows not to check all link issues during
the load.

## 20.10.2

### Enhancement

*Compilation in C++14 with conan-center*

bintray has stopped. We had to switch to the conan-center. And then our conan
dependencies had to upgrade and then we had to switch to C++14. So here is the
corresponding compilation.

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
