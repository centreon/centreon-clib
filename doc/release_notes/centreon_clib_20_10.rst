=====================
Centreon Clib 20.10.1
=====================

*********
Bug fixes
*********

Deadlock removed
================
Start/Stop process_manager mechanism is rewritten and much more simpler. The
consequences are that there are less dead locks in the processes management.

Timestamp
=========
The simple cases that are addition, subtraction and some others cases, have
their computations simplified, that is to say less computations, so faster.

=====================
Centreon Clib 20.10.0
=====================

*********
Bug fixes
*********

Deadlock removed
================
A possible deadlock was removed when a process is added and at the same time
a process is removed because in timeout.
