include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(
        netlog_tests tests.cpp
        ../src/Nets.cpp
        ../src/Device.cpp
        ../src/Net.cpp
        ../src/exec.cpp
)

target_link_libraries(netlog_tests PUBLIC -Wl,--start-group  ${Boost_LIBRARIES} ${PROJECT_LIB} -Wl,--end-group  gtest gtest_main)
