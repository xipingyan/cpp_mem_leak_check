# Readme
Check memory leak via valgrind. Only work for Linux.

# How to run

    Build:
    $ mkdir build && cd build
    $ cmake ..
    $ make -j2

    Run:
    $ valgrind ./testapp
    ==6034== Memcheck, a memory error detector
    ==6034== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==6034== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==6034== Command: ./testapp
    ==6034==
    ==6034==
    ==6034== HEAP SUMMARY:
    ==6034==     in use at exit: 80 bytes in 4 blocks
    ==6034==   total heap usage: 5 allocs, 1 frees, 72,784 bytes allocated
    ==6034==
    ==6034== LEAK SUMMARY:
    ==6034==    definitely lost: 16 bytes in 1 blocks
    ==6034==    indirectly lost: 64 bytes in 3 blocks
    ==6034==      possibly lost: 0 bytes in 0 blocks
    ==6034==    still reachable: 0 bytes in 0 blocks
    ==6034==         suppressed: 0 bytes in 0 blocks
    ==6034== Rerun with --leak-check=full to see details of leaked memory

# Key word

``"definitely lost"``：New or malloc, but don't call free or delete. 

``"indirectly lost"``：The class with PRT is normal release, but the corresponding ptr don't been released.

``"possibly lost"``： Can't reproduce it.

``"still reachable"``：Static variable or shared ptr.

``"suppressed"``：Maybe the system can process the potential leak.


# Refer:

    https://aleksander.es/data/valgrind-memcheck.pdf
    https://cloud.tencent.com/developer/article/1680519
