// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#ifndef TEST_FIXEDREAL_H
#define TEST_FIXEDREAL_H

#include "./catch.hpp"

#include "./fmaw_fixedreal.h"
#include "./fmaw_fixedreal.cpp"

namespace FixedRealTests {

typedef fixedreal FixedReal;  // Class will be named FixedReal.

TEST_CASE("FixedReal can be initialized", "[FixedReal]") {
    SECTION("constructor with precision represents 0") {
        FixedReal a {1};
        REQUIRE(a.toInt() == 0);
        FixedReal b {2};
        REQUIRE(b.toInt() == 0);
        FixedReal c {0};
        REQUIRE(c.toInt() == 0);
    }

    SECTION("constructor with invalid precision throws exception") {
        REQUIRE_THROWS(FixedReal a { -1});
        REQUIRE_THROWS(FixedReal a {32});
    }

    SECTION("constructor with integer represents the integer") {
        FixedReal a {1, 3};
        REQUIRE(a.toInt() == 1);
        REQUIRE(a.toDouble() == 1);
        FixedReal b {2, 31};
        REQUIRE(b.toInt() == 2);
        REQUIRE(b.toDouble() == 2);
        FixedReal c {0, 1};
        REQUIRE(c.toInt() == 0);
        REQUIRE(c.toDouble() == 0);
    }

    SECTION("constructor with double represents the double (approx)") {
        FixedReal a {3.1415, 8};
        REQUIRE(a.toDouble() - 3.140625 < 0.00001);
        REQUIRE(a.toInt() == 3);
        FixedReal b {3.1415, 2};
        REQUIRE(b.toDouble() == 3);
        REQUIRE(b.toInt() == 3);
        FixedReal c {3.1415, 16};
        REQUIRE(c.toDouble() - 3.14149 < 0.00001);
        REQUIRE(c.toInt() == 3);
        FixedReal d {3.1415, 0};
        REQUIRE(d.toDouble() == 3);
        REQUIRE(d.toInt() == 3);
    }
}

TEST_CASE("FixedReal supports basic arithmetic", "[FixedReal]") {
    FixedReal a {3.1415, 8};
    SECTION("two FixedReal with the same precision can be added") {
        FixedReal b {3, 8};
        REQUIRE((a + b).toDouble() - 6.140625 < 0.00001);
        FixedReal c {3.1415, 8};
        REQUIRE((a + c).toDouble() - 6.2578 < 0.00002);
    }
    SECTION("two FixedReal with different precision can be added") {
        FixedReal b {3, 0};
        REQUIRE((a + b).toDouble() - 6.140625 < 0.00001);
        FixedReal c {3.1415, 16};
        REQUIRE((a + c).toDouble() - 6.2821 < 0.00002);
    }

    SECTION("two FixedReal with the same precision can be substracted") {
        FixedReal b {3, 8};
        REQUIRE((a - b).toDouble() - 0.140625 < 0.00001);
        FixedReal c {3.1415, 8};
        REQUIRE((a - c).toDouble() - 0.2578 < 0.00002);
    }
    SECTION("two FixedReal with different precision can be substracted") {
        FixedReal b {3, 0};
        REQUIRE((a - b).toDouble() - 0.140625 < 0.00001);
        FixedReal c {3.1415, 16};
        REQUIRE((a - c).toDouble() - 0.2821 < 0.00002);
    }

    SECTION("two FixedReal with the same precision can be multiplied") {
        FixedReal b {3, 8};
        REQUIRE((a * b).toDouble() - 9.42187 < 0.00001);
        FixedReal c {3.1415, 8};
        REQUIRE((a * c).toDouble() - 9.86352 < 0.00001);
    }
    SECTION("two FixedReal with different precision can be multiplied") {
        FixedReal b {3, 0};
        REQUIRE((a * b).toDouble() - 9.42187 < 0.00001);
        FixedReal c {3.1415, 16};
        REQUIRE((a * c).toDouble() - 9.86627 < 0.00002);
    }

    SECTION("two FixedReal with the same precision can be divided") {
        FixedReal b {3, 8};
        REQUIRE((a / b).toDouble() - 1.04716 < 0.00001);
        FixedReal c {3.1415, 8};
        REQUIRE((a / c).toDouble() - 1 < 0.00001);
    }
    SECTION("two FixedReal with different precision can be divided") {
        FixedReal b {3, 0};
        REQUIRE((a / b).toDouble() - 1.04716 < 0.00001);
        FixedReal c {3.1415, 16};
        REQUIRE((a / c).toDouble() - 1 < 0.00002);
    }
}

TEST_CASE("FixedReal supports comparisons", "[FixedReal]") {
    FixedReal a {3.1415, 8};
    SECTION("two FixedReal with the same precision can be compared") {
        FixedReal b {3, 8};
        REQUIRE(a < b);
        REQUIRE(a <= b);
        REQUIRE_FALSE(a == b);
        REQUIRE_FALSE(a >= b);
        REQUIRE_FALSE(a > b);
        FixedReal c {3.1415, 8};
        REQUIRE(a <= c);
        REQUIRE(a == c);
        REQUIRE(a >= c);
        REQUIRE_FALSE(a > c);
    }
    SECTION("two FixedReal with different precision can be compared") {
        FixedReal b {3, 0};
        REQUIRE(a < b);
        REQUIRE(a <= b);
        REQUIRE_FALSE(a == b);
        REQUIRE_FALSE(a >= b);
        REQUIRE_FALSE(a > b);
        FixedReal c {3.1415, 16};
        REQUIRE(a <= c);
        REQUIRE(a == c);
        REQUIRE(a >= c);
        REQUIRE_FALSE(a > c);
    }
}

}  // namespace FixedRealTests

#endif
