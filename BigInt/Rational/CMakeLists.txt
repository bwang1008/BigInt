include(CTest)

add_library(
    RationalLib STATIC
    src/arithmetic.cpp
    src/constructor.cpp
    src/rational.cpp
)

add_executable(
    test_rational
    tests/test_constructor.cpp
)

add_test(NAME test_rational COMMAND test_rational)

target_include_directories(
    RationalLib
    PUBLIC ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    test_rational PRIVATE RationalLib BigIntLib Catch2::Catch2WithMain
)
