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

# Warnings for gcc version "Ubuntu 9.4.0-1ubuntu1~20.04.2"
# Found supported warning flags by looking in "info gcc"
# and subtracting out the flags enabled by -Wall, -Wextra, -Wpedantic
# by checking "gcc -Q -x c++ -Wall --help=warnings" (and for other warnings)

set(WARNINGS
	-Wall                         # enable many other warnings
	-Wextra                       # more warnings
	-Wpedantic                    # strict ISO C++
	-pedantic-errors              # depends on c++ standard used
	-Wno-aggregate-return
	-Waligned-new
	-Walloc-zero
	-Walloca
	-Wc++17-compat
	-Wcast-align
	-Wcast-align=strict
	-Wcast-qual                   # warn if casting removes type-qualifiers
	-Wconditionally-supported
	-Wconversion                  # warn about conversions that may change the value
	-Wdate-time                   # do not use __TIME__, __DATE__, or __TIMESTAMP__ to get reproducible builds
	-Wdisabled-optimization
	-Wdouble-promotion            # warn if float implicitly casts to double
	-Wduplicated-branches         # prevent branch statements that provide same value
	-Wduplicated-cond             # prevent same condition in if and else if
	-Wextra-semi
	-Wfloat-equal                 # do not use equality on floating-points
	-Wformat-contains-nul
	-Wformat-extra-args
	-Wformat=2
	-Wformat-overflow=1
	-Wformat-signedness
	-Wformat-truncation=1
	-Wframe-address
	-Winline
	-Winvalid-pch
	-Wlogical-op                  # warn about suspicious usages of logical operations ||, &&, ^
	-Wno-missing-braces           # -Wmissing-braces was removed from -Wall
	-Wmissing-format-attribute
	-Wmissing-include-dirs        # warn if include directory not valid
	-Wmissing-noreturn            # if we should have attribute [[noreturn]]
	-Wmultichar
	-Wnull-dereference
	-Wpacked
	-Wpacked-not-aligned
	-Wno-padded
	-Wredundant-decls             # warn when multiple declarations
	-Wshadow=global               # prevent shadowing of other variables
	-Wshift-overflow=2
	-Wsign-conversion             # warn about conversions between signed and unsigned integers
	-Wno-scalar-storage-order
	-Wstack-protector
	-Wstringop-truncation
	-Wsuggest-attribute=pure      # warn if some functions should have these attributes
	-Wsuggest-attribute=const
	-Wsuggest-attribute=noreturn
	-Wsuggest-attribute=format
	-Wsuggest-attribute=cold
	-Wsuggest-attribute=malloc
	-Wsuggest-final-types
	-Wsuggest-final-methods
	-Wsuggest-override
	-Wswitch-default              # case statements should have default case
	-Wswitch-enum
	-Wno-system-headers
	-Wtrampolines
	-Wundef
	-Wunused                      # all -Wunused-* warnings
	-Wunused-macros               # warn about macros that are not expanded anywhere
	-Wuseless-cast
	-Wvector-operation-performance
	-Wzero-as-null-pointer-constant
	-Wctor-dtor-privacy
	-Wdeprecated-copy-dtor
	-Wno-multiple-inheritance
	-Wno-namespaces
	-Wnoexcept
	-Wnon-virtual-dtor
	-Wregister
	-Weffc++
	-Wstrict-null-sentinel
	-Wno-templates
	-Wold-style-cast
	-Woverloaded-virtual
	-Wsign-promo
	-Wno-virtual-inheritance
	-Wstrict-overflow=2
	-Wmissing-declarations
	-fno-operator-names           # do not use "and", "or", and "xor" (and others) as keywords
	-fno-common                   # prevent tentative definitions
	-fstack-protector-all         # stack protection
)

# build types have different flags
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

foreach(TARG BigIntLib tests)
  target_compile_features(${TARG} PUBLIC cxx_std_20)
  set_target_properties(${TARG} PROPERTIES CXX_EXTENSIONS OFF)
  target_compile_options(${TARG} PRIVATE "${WARNINGS}")
endforeach()

target_include_directories(BigIntLib PRIVATE ${CMAKE_SOURCE_DIR})

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})
# test coverage: see https://danielsieger.com/blog/2024/08/03/code-coverage-with-cmake.html
target_link_options(tests PRIVATE
    $<$<CONFIG:Debug>:
        "-fsanitize=address" "--coverage"
    >
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain BigIntLib)
