cmake_minimum_required(VERSION 3.15)
project(dlx_solver VERSION 0.1)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(dlx_lib STATIC dlx.c dlx_node_stack.c dlx_util.c)
add_executable(dlx_solver sudoku.c main.c)
target_link_libraries(dlx_solver dlx_lib)
target_include_directories(dlx_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

option(ENABLE_TESTS "Build tests" ON)
if(ENABLE_TESTS)
  # Check for criterion
  find_package(Criterion REQUIRED)

  # Add tests
  enable_testing()
  add_subdirectory(test)
endif()
