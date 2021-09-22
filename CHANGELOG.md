# Changelog

## 21.04.3

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

## 21.04.2

*Libraries loading*

Libraries are loaded lazily now. This allows not to check all link issues during
the load.

## 21.04.1

*Compilation in C++14 with conan-center*

bintray has stopped. We had to switch to the conan-center. And then our conan
dependencies had to upgrade and then we had to switch to C++14. So here is the
corresponding compilation.

## 21.04.0

New release.
