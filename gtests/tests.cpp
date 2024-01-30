#include <gtest/gtest.h>

#include "../src/Nets.hpp"

TEST(NETLOG, DefaultConstructor) {
    Nets nets("dummy.ini");
    // EXPECT_EQ(0u,c.size());
    // EXPECT_EQ(0.5,c.factor());
}
