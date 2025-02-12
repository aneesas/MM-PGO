find_package(Boost 1.60 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# Download GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  # v1.15.2
  URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_all test_dpgo_utils.cpp)
target_include_directories(test_all PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(test_all DPGO DChordal SESync ${Boost_LIBRARIES} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_all)
