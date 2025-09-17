cmake_minimum_required(VERSION 3.15)

project(tuilib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(CREATE_LINK
  ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
  ${CMAKE_SOURCE_DIR}/compile_commands.json
  SYMBOLIC
)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message(STATUS "Found ccache in ${CCACHE_PROGRAM}")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
  message(STATUS "Install ccache to speed up compilation")
endif()

add_library(tuilib INTERFACE)

target_sources(tuilib
 INTERFACE
 include/tuilib/line.h
 include/tuilib/border.h
)
target_include_directories(tuilib
 INTERFACE
 include/
)
target_compile_features(tuilib INTERFACE cxx_std_23)

include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(tuilibtests)
target_sources(tuilibtests
 PRIVATE
 tests/border_test.cpp
)
target_link_libraries(tuilibtests PRIVATE tuilib gtest_main)
gtest_discover_tests(tuilibtests)
