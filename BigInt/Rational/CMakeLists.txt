include(CTest)

add_library(
    RationalLib STATIC
    src/arithmetic.cpp
    src/comparison.cpp
    src/constructor.cpp
    src/output.cpp
)

add_executable(
    test_rational
    tests/test_arithmetic.cpp
    tests/test_comparison.cpp
    tests/test_constructor.cpp
    tests/test_output.cpp
)

add_test(NAME test_rational COMMAND test_rational)

target_include_directories(
    RationalLib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
)
target_link_libraries(
    RationalLib PUBLIC BigIntLib
)

target_link_libraries(
    test_rational PRIVATE Catch2::Catch2WithMain RationalLib
)
