cmake_minimum_required(VERSION 3.16)

project(BigInt
	VERSION 0.0
	DESCRIPTION "Big-integer library for C++"
	LANGUAGES CXX
)

####################
### Dependencies ###
####################

include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v3.8.0
)
FetchContent_MakeAvailable(Catch2)

# from https://github.com/catchorg/Catch2/issues/2927
get_target_property(catch2_includes Catch2 INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(Catch2 SYSTEM INTERFACE ${catch2_includes})

####################
### Main targets ###
####################

include(CTest)

add_library(
	BigIntLib STATIC
	BigInt/include/big_int.hpp
	BigInt/src/big_int.cpp
	BigInt/src/comparison.cpp
	BigInt/src/constructor.cpp
	BigInt/src/arithmetic/add_subtract.cpp
	BigInt/src/arithmetic/division/grade_school.cpp
	BigInt/src/arithmetic/multiplication/grade_school.cpp
	BigInt/src/arithmetic/multiplication/karatsuba.cpp
	BigInt/src/arithmetic/multiplication/operators.cpp
)

add_executable(
	tests
	BigInt/tests/test_big_int.cpp
	BigInt/tests/test_comparison.cpp
	BigInt/tests/test_constructor.cpp
	BigInt/tests/arithmetic/test_add_subtract.cpp
	BigInt/tests/arithmetic/division/test_division.cpp
	BigInt/tests/arithmetic/multiplication/test_karatsuba.cpp
)

add_test(NAME tests COMMAND tests)

##############################
### Compile and link flags ###
##############################

include("cmake/warnings.cmake")

# build types have different flags
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

foreach(TARG BigIntLib tests)
  target_compile_features(${TARG} PUBLIC cxx_std_20)
  set_target_properties(${TARG} PROPERTIES CXX_EXTENSIONS OFF)
  target_compile_options(${TARG} PRIVATE "${WARNINGS}")
endforeach()

target_include_directories(
    BigIntLib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
)

# test coverage: see https://danielsieger.com/blog/2024/08/03/code-coverage-with-cmake.html
target_link_options(tests PRIVATE
    $<$<CONFIG:Debug>:
        "-fsanitize=address" "--coverage"
    >
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain BigIntLib)
