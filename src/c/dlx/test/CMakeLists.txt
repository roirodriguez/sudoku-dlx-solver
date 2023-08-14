add_executable (test_dlx_solver test.c)

target_link_libraries (test_dlx_solver ${CRITERION_LIBRARIES})

# use C99
set_property (TARGET test_dlx_solver PROPERTY C_STANDARD 99)

# Enable a few warnings
if (CMAKE_COMPILER_IS_GNUCC)
  target_compile_options (test_dlx_solver PRIVATE -Wall -Wextra)
endif (CMAKE_COMPILER_IS_GNUCC)
if (MSVC)
  target_compile_options (test_dlx_solver PRIVATE /W4)
endif (MSVC)

add_test (test_dlx_solver test_dlx_solver)
