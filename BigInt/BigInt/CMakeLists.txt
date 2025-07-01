include(CTest)

add_library(
	BigIntLib STATIC
	src/arithmetic/add_subtract.cpp
	src/arithmetic/division/grade_school.cpp
	src/arithmetic/division/operators.cpp
	src/arithmetic/misc.cpp
	src/arithmetic/multiplication/grade_school.cpp
	src/arithmetic/multiplication/karatsuba.cpp
	src/arithmetic/multiplication/operators.cpp
	src/comparison.cpp
	src/constructor.cpp
	src/misc.cpp
	src/output.cpp
)

add_executable(
	test_bigint
	tests/arithmetic/division/test_division.cpp
	tests/arithmetic/division/test_remainder.cpp
	tests/arithmetic/multiplication/test_karatsuba.cpp
	tests/arithmetic/test_add_subtract.cpp
	tests/arithmetic/test_misc.cpp
	tests/test_comparison.cpp
	tests/test_constructor.cpp
	tests/test_output.cpp
)

add_test(NAME test_bigint COMMAND test_bigint)

target_include_directories(
    BigIntLib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
)

# test coverage: see https://danielsieger.com/blog/2024/08/03/code-coverage-with-cmake.html
target_link_options(test_bigint PRIVATE
    $<$<CONFIG:Debug>:
        "-fsanitize=address" "--coverage"
    >
)
target_link_libraries(test_bigint PRIVATE Catch2::Catch2WithMain BigIntLib)
