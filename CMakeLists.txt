CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(BigInt
	VERSION 0.0
	DESCRIPTION "Big-integer library for C++"
	LANGUAGES CXX
)

####################
### Dependencies ###
####################

INCLUDE(FetchContent)
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

ADD_LIBRARY(
	BigIntLib SHARED
	BigInt/include/big_int.hpp
	BigInt/src/big_int.cpp
	BigInt/src/comparison.cpp
	BigInt/src/constructor.cpp
	BigInt/src/arithmetic/add_subtract.cpp
	BigInt/src/arithmetic/multiplication/grade_school.cpp
	BigInt/src/arithmetic/multiplication/karatsuba.cpp
)

ADD_EXECUTABLE(
	tests
	BigInt/tests/test_big_int.cpp
	BigInt/tests/test_comparison.cpp
	BigInt/tests/test_constructor.cpp
	BigInt/tests/test_multiplication.cpp
)

ADD_TEST(NAME tests COMMAND tests)

##############################
### Compile and link flags ###
##############################

SET(WARNINGS
	-Wall                         # enable many other warnings
	-Wextra                       # more warnings
	-Wpedantic                    # strict ISO C++
	-pedantic-errors              # depends on c++ standard used
	-Wmissing-braces              # initalizers have proper braces
	-Wmissing-include-dirs        # if include directory not valid
	-Wswitch-default              # case statements should have default case
	-Wunused                      # all -Wunused-* warnings
	-Wuninitialized               # use without initialization
	-Wunknown-pragmas             # do not use unknown   #pragma
	-Wmissing-noreturn            # if we should have attribute [[noreturn]]
	-Wsuggest-attribute=pure      # warn if some functions should have these attributes
	-Wsuggest-attribute=const
	-Wsuggest-attribute=noreturn
	-Wsuggest-attribute=malloc
	-Wbool-compare                # prevent comparing boolean with int
	-Wduplicated-branches         # prevent branch statements that provide same value
	-Wduplicated-cond             # prevent same condition in if and else if
	-Wdouble-promotion            # warn if float implicitly casts to double
	-Wfloat-equal                 # do not use equality on floating-points
	-Wshadow                      # prevent shadowing of local variables
	-Wunsafe-loop-optimizations   # warn if compiler cannot optimize loop
	-Wunused-macros               # warn about macros that are not expanded anywhere
	-Wcast-qual                   # warn if casting removes type-qualifiers
	-Wconversion                  # warn about conversions that may change the value
	-Wdate-time                   # do not use __TIME__, __DATE__, or __TIMESTAMP__ to get reproducible builds
	-Wsign-conversion             # warn about conversions between signed and unsigned integers
	-Wlogical-op                  # warn about suspicious usages of logical operations ||, &&, ^
	-Wredundant-decls             # warn when multiple declarations
	-fno-operator-names           # do not use "and", "or", and "xor" (and others) as keywords
	-fno-common                   # prevent tentative definitions
	-fsanitize=address            # detect memory access errors
	-fstack-protector-all         # stack protection
)

FOREACH(TARG BigIntLib tests)
  TARGET_COMPILE_FEATURES(${TARG} PUBLIC cxx_std_20)
  SET_TARGET_PROPERTIES(${TARG} PROPERTIES CXX_EXTENSIONS OFF)
  TARGET_COMPILE_OPTIONS(${TARG} PRIVATE "${WARNINGS}")
ENDFOREACH()

TARGET_INCLUDE_DIRECTORIES(BigIntLib PRIVATE ${CMAKE_SOURCE_DIR})

TARGET_INCLUDE_DIRECTORIES(tests PRIVATE ${CMAKE_SOURCE_DIR})
# test coverage: see https://danielsieger.com/blog/2024/08/03/code-coverage-with-cmake.html
TARGET_COMPILE_OPTIONS(tests PRIVATE "-coverage")
TARGET_LINK_OPTIONS(tests PRIVATE "-fsanitize=address" "--coverage")
TARGET_LINK_LIBRARIES(tests PRIVATE Catch2::Catch2WithMain BigIntLib)
