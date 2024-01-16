cmake_minimum_required(VERSION 3.5)

project(NETLOG)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED TRUE)

set(BOOST_ROOT "/usr/local/vcpkg/installed/x64-linux/")
set(Boost_INCLUDE_DIR  "/usr/local/vcpkg/installed/x64-linux/include")
set(Boost_LIBRARY_DIR  "/usr/local/vcpkg/installed/x64-linux/lib")

SET(Boost_DEBUG ON)
find_package(Boost 1.83.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    # include_directories(${NETLOG_SOURCE_DIR}/src)

   add_executable(
        netlog
        netlog.cpp
        src/Device.cpp
        src/Net.cpp
        src/Nets.cpp
        src/exec.cpp
    )
    target_link_libraries(netlog ${Boost_LIBRARIES})

    target_compile_options(netlog PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W4>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror -pedantic -ggdb -std=c++2a -std=gnu++20>
            )

# add_subdirectory(gtests)
endif()
