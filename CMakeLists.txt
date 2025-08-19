# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(osprocess C)

add_executable(parent ./os/fork_wait_exec.c)
add_executable(child ./os/child.c)

# This is the corrected line.
# CMAKE_CURRENT_BINARY_DIR points to the build directory.
target_compile_definitions(parent PUBLIC CHILD_PATH="${CMAKE_CURRENT_BINARY_DIR}/child")
