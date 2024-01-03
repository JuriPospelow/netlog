cmake_minimum_required(VERSION 3.5)

project(NETLOG)

add_executable(
	netlog
	netlog.cpp
	# Device.cpp
	# Net.cpp
)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED TRUE)
target_compile_options(netlog PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror -pedantic -ggdb -std=c++2a -std=gnu++20>
        )

# add_subdirectory(gtests)
