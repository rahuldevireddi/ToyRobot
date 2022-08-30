PROJECT(UnitTests)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        latest-passing-build # or use release tag, eg. v3.8
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

# Sources:
ADD_DEFINITIONS(-DUNIT_TEST)
include_directories(../)

SET(UnitTests_executable_SRCS
    ut_ToyRobot.cpp
)

SET(UnitTests_executable_HDRS
)

# UnitTests target
ADD_EXECUTABLE(UnitTests ${UnitTests_executable_SRCS} ${UnitTests_executable_HDRS})
TARGET_LINK_LIBRARIES(UnitTests ToyRobotLib CppUTest CppUTestExt)
