#include "gtest/gtest.h"

// include test files
#include "../unit_tests/insert_test.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}