cmake_minimum_required(VERSION 3.15)

project(tuilib)

find_program(CCACHE_BINARY ccache)
if(CCACHE_BINARY)
	set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_BINARY} CACHE FILEPATH "C compiler cache used")
	set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_BINARY} CACHE FILEPATH "CXX compiler cache used")
else()
	message(WARNING "ccache not found")
endif()


add_library(tuilib)

target_sources(tuilib
	PUBLIC
	include/tuilib/hello.h
	PRIVATE
	src/hello.cpp
)
target_include_directories(tuilib
	PUBLIC
	include/
	PRIVATE
	src/
)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tuilibtests)
target_sources(tuilibtests
	PRIVATE
	tests/hello_test.cpp
)
target_link_libraries(tuilibtests PRIVATE tuilib gtest_main)
