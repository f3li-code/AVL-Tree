CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(avltree
        src/main.cpp header/AVLTree.cpp header/Node.cpp)

ADD_EXECUTABLE(test
        src/unit_test.cpp header/AVLTree.cpp header/Node.cpp)

TARGET_LINK_LIBRARIES(test
        gtest)

TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)