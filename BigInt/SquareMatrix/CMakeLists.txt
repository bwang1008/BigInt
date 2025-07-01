include (CTest)

add_library(
    SquareMatrixLib
    src/constructor.cpp
    src/output.cpp
)

add_executable(
    test_square_matrix
    tests/test_constructor.cpp
)

add_test(NAME test_square_matrix COMMAND test_square_matrix)

target_include_directories(
    SquareMatrixLib PUBLIC ${CMAKE_SOURCE_DIR}
)
target_link_libraries(
    SquareMatrixLib PUBLIC RationalLib
)

target_link_libraries(
    test_square_matrix PRIVATE Catch2::Catch2WithMain SquareMatrixLib
)
