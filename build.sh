#!/bin/sh
g++ -std=c++14 -Wno-write-strings -c win0001.cc
g++ -std=c++14 -Wno-write-strings -c win0001_impl.cc
g++ -std=c++14 -Wno-write-strings -c win0002.cc
g++ -std=c++14 -Wno-write-strings -c wm_main.cc

g++ -std=c++14 -Wno-write-strings -c puzzle.cc
g++ -std=c++14 -Wno-write-strings -c ascii.cc
g++ -std=c++14 -Wno-write-strings -c gadgets.cc
g++ -std=c++14 -Wno-write-strings -c calendar.cc

g++ -std=c++14 -Wno-write-strings -c hint.cc
g++ -std=c++14 -Wno-write-strings -c help.cc
g++ -std=c++14 -Wno-write-strings -c helpwin.cc

g++ -o wm_main wm_main.o win0001.o win0001_impl.o win0002.o \
    puzzle.o ascii.o calendar.o gadgets.o hint.o \
    help.o helpwin.o \
    -L. -lrhtv -lncurses -lgpm
