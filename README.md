# Terminal

## Installing the gtkmm4 library

This project depends on the gtkmm4 library. I was able to install this dependency with the command

    brew install gtkmm4

## Compiling the source code

I wrote a Makefile to automate the build process. After installing the gtkmm4 dependency, the project can be built with the command

    make terminal

This tells g++ to compile all of the source files, and link the object files into a binary named "Terminal".

It is also possible to compile the source files with the clang++ compiler, by editing the Makefile and substituting clang++ for g++. I have tested the build process with both the g++ and clang++ compilers.

## Running the executable file

The Terminal application can be run with the command

    bin/Terminal

It can also be run with the commands

    cd bin
    ./Terminal

The ./ prefix is Unix syntax for running an executable. This syntax is used on Unix, Linux, and MacOS.