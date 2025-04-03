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

###################
### Build types ###
###################

# build types have different flags
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

####################
### Main targets ###
####################

add_subdirectory(BigInt)

##############################
### Compile and link flags ###
##############################

include("cmake/warnings.cmake")

foreach(TARG BigIntLib tests)
  target_compile_features(${TARG} PUBLIC cxx_std_20)
  set_target_properties(${TARG} PROPERTIES CXX_EXTENSIONS OFF)
  target_compile_options(${TARG} PRIVATE "${WARNINGS}")
endforeach()
