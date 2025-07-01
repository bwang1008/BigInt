add_library(
    SquareMatrixLib
    src/constructor.cpp
    src/output.cpp
)

target_include_directories(
    SquareMatrixLib PUBLIC ${CMAKE_SOURCE_DIR}
)
