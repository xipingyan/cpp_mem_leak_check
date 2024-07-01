# README
Abort and exit, print current function's backtrace at the same time.

# How to run

    Build:
    $ mkdir build && cd build
    $ cmake ..
    $ make -j2

    Run:
    $ valgrind ./testapp
    0# print_stacktrace() in ./testapp
    1# fun3() in ./testapp
    2# fun2() in ./testapp
    3# fun1() in ./testapp
    4# main in ./testapp
    5# 0x00007593CFE29D90 in /lib/x86_64-linux-gnu/libc.so.6
    6# __libc_start_main in /lib/x86_64-linux-gnu/libc.so.6
    7# _start in ./testapp
    Aborted (core dumped)

# Refer:

    https://stackoverflow.com/questions/3899870/how-to-print-a-stack-trace-whenever-a-certain-function-is-called
