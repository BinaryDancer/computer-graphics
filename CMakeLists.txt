cmake_minimum_required (VERSION 3.8)
project (rt)

# get rid of annoying MSVC warnings.
add_definitions(-D_CRT_SECURE_NO_WARNINGS)


set (CMAKE_CXX_STANDARD 11)

#include_directories("/usr/local/include" "/usr/local/opt/llvm/include")
#link_directories("/usr/local/lib" "/usr/local/opt/llvm/lib")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(rt main.cpp Bitmap.cpp Scene.cpp)

#target_link_libraries(rt ${ALL_LIBS} omp)
target_link_libraries(rt ${ALL_LIBS})

