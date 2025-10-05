include(CTest)

add_library(
    MultiplierLib STATIC
    src/base_multiply.cpp
    src/grade_school.cpp
    src/karatsuba.cpp
)

add_executable(
    test_multiplier
    tests/test_base_multiply.cpp
    tests/test_multiplication_methods.cpp
)
add_test(
    NAME test_multiplier COMMAND test_multiplier
)

target_include_directories(
    MultiplierLib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
)
target_link_libraries(
    MultiplierLib PUBLIC BigIntLib
)

target_link_libraries(
    test_multiplier PRIVATE Catch2::Catch2WithMain MultiplierLib
)
