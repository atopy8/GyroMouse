#include "Utils.hpp"
#include <gtest/gtest.h>


TEST(ParsePortTest, InvalidTwoArgumentOoR) {
    const int argcTest = 2;
    const char *argvTest1[] = {"void", "0"};
    EXPECT_EQ(0, parse_port(argcTest, argvTest1));

    const char *argvTest2[] = {"void", "65536"};
    EXPECT_EQ(0, parse_port(argcTest, argvTest2));
}

TEST(ParsePortTest, ValidOneArgument) {
    const int argcTest = 1;
    const char *argvTest[] = {"void"};
    EXPECT_EQ(5000, parse_port(argcTest, argvTest));
}

TEST(ParsePortTest, ValidTwoArgument) {
    const int argcTest = 2;
    const char *argvTest1[] = {"void", "8080"};
    EXPECT_EQ(8080, parse_port(argcTest, argvTest1));

    const char *argvTest2[] = {"void", "1"};
    EXPECT_EQ(1, parse_port(argcTest, argvTest2));

    const char *argvTest3[] = {"void", "65535"};
    EXPECT_EQ(65535, parse_port(argcTest, argvTest3));
}

TEST(ParsePortTest, InvalidTwoArgument) {
    const int argcTest = 2;
    const char *argvTest1[] = {"void", "80ab"};
    EXPECT_EQ(0, parse_port(argcTest, argvTest1));

    const char *argvTest2[] = {"void", "abc"};
    EXPECT_EQ(0, parse_port(argcTest, argvTest2));
}

TEST(ParsePortTest, InvalidArgumentNumber) {
    const int argcTest = 3;
    const char *argvTest1[] = {"void", "80ab", "abc"};
    EXPECT_EQ(0, parse_port(argcTest, argvTest1));
}

