# Analog Filter Simulator

Analog Filter Simulator is a program which calculates and outputs the frequency response of an analog circuit.

# Building & Installing the program

This program is built and installed using cmake. The CMakeLists.txt file has been prepared to compile the needed programs using C++20.
The minimum version for cmake is 3.1. The minimum version for Python is 3.6.8.
To build and install the program using cmake, use the following commands while in the top directory of the project:

$ cmake -H. -Btmp -DCMAKE_INSTALL_PREFIX=tmp/install
$ cmake --build tmp --clean-first --target install

# Running the program

To run the program, simply run the executable file in the installation bin/ directory:

$ ./tmp/install/bin/filter_simulator

The program takes user input through the command line, so no further arguments are required when initally running the program.

When interacting with the program, use single digit inputs (1, 2, 3, ...) to select options. Data values may be input using multiple digits and a single decimal point.
Output of the program is done through either the command line or a file specified by the user.

# Running the demo

To run the demo, the file within the installation folder must be executed. After building, use the following command:

$ ./tmp/install/bin/demo