#include <string>

#include <catch2/catch_test_macros.hpp>

#include "BigInt/BigInt/include/big_int.hpp"

TEST_CASE("Copy", "[copy]") {
    const BigInt::BigInt x{"3"};
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    const BigInt::BigInt y = x;
    REQUIRE(y.str() == x.str());
}

TEST_CASE("Copy of large number", "[copy]") {
    const BigInt::BigInt x{"12345678901234567890234568790"};
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    const BigInt::BigInt y = x;
    REQUIRE(y.str() == x.str());
}
