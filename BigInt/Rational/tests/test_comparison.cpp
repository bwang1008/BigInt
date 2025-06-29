#include "BigInt/Rational/include/rational.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("less-than", "[comparison]") {
    REQUIRE(BigInt::Rational(-1, 2) < BigInt::Rational(-1, 3));
    REQUIRE_FALSE(BigInt::Rational(-1, 3) < BigInt::Rational(-1, 2));

    REQUIRE(BigInt::Rational(-1, 2) < BigInt::Rational());
    REQUIRE_FALSE(BigInt::Rational() < BigInt::Rational(-1, 2));

    REQUIRE(BigInt::Rational(-1, 2) < BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) < BigInt::Rational(-1, 2));

    REQUIRE(BigInt::Rational() < BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) < BigInt::Rational());

    REQUIRE(BigInt::Rational(1, 3) < BigInt::Rational(1, 2));
    REQUIRE_FALSE(BigInt::Rational(1, 2) < BigInt::Rational(1, 3));
}

TEST_CASE("less-than-equals", "[comparison]") {
    REQUIRE(BigInt::Rational(-1, 2) <= BigInt::Rational(-1, 3));
    REQUIRE_FALSE(BigInt::Rational(-1, 3) <= BigInt::Rational(-1, 2));

    REQUIRE(BigInt::Rational(-1, 2) <= BigInt::Rational());
    REQUIRE_FALSE(BigInt::Rational() <= BigInt::Rational(-1, 2));

    REQUIRE(BigInt::Rational(-1, 2) <= BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) <= BigInt::Rational(-1, 2));

    REQUIRE(BigInt::Rational() <= BigInt::Rational());

    REQUIRE(BigInt::Rational() <= BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) <= BigInt::Rational());

    REQUIRE(BigInt::Rational(1, 3) <= BigInt::Rational(1, 2));
    REQUIRE_FALSE(BigInt::Rational(1, 2) <= BigInt::Rational(1, 3));
}

TEST_CASE("greater-than", "[comparison]") {
    REQUIRE(BigInt::Rational(-1, 3) > BigInt::Rational(-1, 2));
    REQUIRE_FALSE(BigInt::Rational(-1, 2) > BigInt::Rational(-1, 3));

    REQUIRE(BigInt::Rational() > BigInt::Rational(-1, 2));
    REQUIRE_FALSE(BigInt::Rational(-1, 2) > BigInt::Rational());

    REQUIRE(BigInt::Rational(1, 3) > BigInt::Rational(-1, 2));
    REQUIRE_FALSE(BigInt::Rational(-1, 2) > BigInt::Rational(-1, 3));

    REQUIRE(BigInt::Rational(1, 3) > BigInt::Rational());
    REQUIRE_FALSE(BigInt::Rational() > BigInt::Rational(1, 3));

    REQUIRE(BigInt::Rational(1, 2) > BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) > BigInt::Rational(1, 2));
}

TEST_CASE("greater-than-equals", "[comparison]") {
    REQUIRE(BigInt::Rational(-1, 3) >= BigInt::Rational(-1, 2));
    REQUIRE_FALSE(BigInt::Rational(-1, 2) >= BigInt::Rational(-1, 3));

    REQUIRE(BigInt::Rational() >= BigInt::Rational(-1, 2));
    REQUIRE_FALSE(BigInt::Rational(-1, 2) >= BigInt::Rational());

    REQUIRE(BigInt::Rational(1, 3) >= BigInt::Rational(-1, 2));
    REQUIRE_FALSE(BigInt::Rational(-1, 2) >= BigInt::Rational(-1, 3));

    REQUIRE(BigInt::Rational() >= BigInt::Rational());

    REQUIRE(BigInt::Rational(1, 3) >= BigInt::Rational());
    REQUIRE_FALSE(BigInt::Rational() >= BigInt::Rational(1, 3));

    REQUIRE(BigInt::Rational(1, 2) >= BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) >= BigInt::Rational(1, 2));
}

TEST_CASE("equals", "[comparison]") {
    REQUIRE(BigInt::Rational(-1, 3) == BigInt::Rational(-1, 3));
    REQUIRE(BigInt::Rational() == BigInt::Rational(0));
    REQUIRE(BigInt::Rational(1, 3) == BigInt::Rational(1, 3));

    REQUIRE_FALSE(BigInt::Rational(-1, 3) == BigInt::Rational());
    REQUIRE_FALSE(BigInt::Rational() == BigInt::Rational(-1, 3));
    REQUIRE_FALSE(BigInt::Rational(-1, 3) == BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) == BigInt::Rational(-1, 3));
    REQUIRE_FALSE(BigInt::Rational() == BigInt::Rational(1, 3));
    REQUIRE_FALSE(BigInt::Rational(1, 3) == BigInt::Rational());
}

TEST_CASE("not-equals", "[comparison]") {
    REQUIRE_FALSE(BigInt::Rational(-1, 3) != BigInt::Rational(-1, 3));
    REQUIRE_FALSE(BigInt::Rational() != BigInt::Rational(0));
    REQUIRE_FALSE(BigInt::Rational(1, 3) != BigInt::Rational(1, 3));

    REQUIRE(BigInt::Rational(-1, 3) != BigInt::Rational());
    REQUIRE(BigInt::Rational() != BigInt::Rational(-1, 3));
    REQUIRE(BigInt::Rational(-1, 3) != BigInt::Rational(1, 3));
    REQUIRE(BigInt::Rational(1, 3) != BigInt::Rational(-1, 3));
    REQUIRE(BigInt::Rational() != BigInt::Rational(1, 3));
    REQUIRE(BigInt::Rational(1, 3) != BigInt::Rational());
}
