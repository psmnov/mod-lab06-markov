cmake_minimum_required (VERSION 3.10.2)

project (mod-lab06-markov)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")


set(tool_dest "bin")
set(lib_dest "lib")
set(include_dest "include/")

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Запрещает переопределение компилятора/рантайма родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_subdirectory(src)
add_subdirectory(test)
