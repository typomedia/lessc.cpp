
cmake_minimum_required(VERSION 3.5)
project(clessc)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

# Disable shared libraries and enforce static linking
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Add cmake modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Add the libless subdirectory and make sure it builds as a static library
add_subdirectory(libless)

# Add the executable target for clessc
add_executable(clessc src/lessc.cpp)

# Include directories
target_include_directories(clessc PRIVATE src .)

# Link the less static library to the clessc target
target_link_libraries(clessc less)

target_compile_definitions(clessc PRIVATE PACKAGE_STRING="LESS CSS Compiler")
target_compile_definitions(clessc PRIVATE PACKAGE_NAME="clessc")
target_compile_definitions(clessc PRIVATE PACKAGE_URL="https://github.com/BramvdKroef/clessc")
target_compile_definitions(clessc PRIVATE PACKAGE_BUGREPORT="bram@vanderkroef.net")

install(TARGETS clessc DESTINATION bin)
# TODO separate headers and sources to install library more easily

enable_testing()
find_package(GTest)
if (GTest_FOUND)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    set(testlessc_SOURCES
            tests/CssParser_test.cpp
            tests/CssTokenizer_test.cpp
            tests/CssSelectorParser_test.cpp
            tests/LessRuleset_test.cpp
            tests/LessSelectorParser_test.cpp
            tests/LessParser_test.cpp
            tests/ValueProcessor_test.cpp
            tests/Color_test.cpp
            )

    add_executable(testlessc ${testlessc_SOURCES})
    target_include_directories(testlessc PRIVATE src ${GTEST_INCLUDE_DIRS})
    target_link_libraries(testlessc less ${GTEST_BOTH_LIBRARIES} Threads::Threads)
    add_test(lesscTest testlessc)
else (GTest_FOUND)
    message(WARNING "Did not find libgtest. Unable to test.")
endif (GTest_FOUND)
