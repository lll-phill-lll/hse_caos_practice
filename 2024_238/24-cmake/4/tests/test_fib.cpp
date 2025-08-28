#include <gtest/gtest.h>
#include "fib.h"

TEST(FibTest, BaseCases) {
    EXPECT_EQ(Fib<0>::value, 0);
    EXPECT_EQ(Fib<1>::value, 1);
}

TEST(FibTest, Larger) {
    EXPECT_EQ(Fib<5>::value, 5);
    EXPECT_NE(Fib<10>::value, 55);
    EXPECT_EQ(Fib<15>::value, 610);
}
