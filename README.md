#ToyRobot Game
------------------------

1. Source code file
   - There are total four source files in total, the first three files belongs to app, the last file contains unit tests.
   - *ToyRobotMain.cpp*
   - *ToyRobot.cpp*
   - *ToyRobot.h*
   - *ut_ToyRobot.cpp*

2. Pre-requirements
   - I have used Ubuntu 22.04, g++ for complication. Used **CppUTest** (https://cpputest.github.io/) as a unit test framework.
      On Ubuntu if `g++, make, cmake` is not installed before, run the below commands
      ```
        sudo apt-get install g++
        sudo apt-get install build-essential
        sudo apt-get install cmake
      ```

3. How to compile
   - On Ubuntu download all of the files to some location; Go to ToyRobot directory
        ```
        cmake -S. -Bbuild
        cmake --build build
        ```

4. How to run
   - On Ubuntu
        ```
        ./build/ToyRobot
        ./build/UnitTests/UnitTests -v
        ```

5) Assumptions
    - This is a console application, user input provided on stdin should be of newline terminated (instead of space)
    - I have tested this on Ubuntu, but should work on any O.S.
