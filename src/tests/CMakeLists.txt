project(tests)

find_package(Boost REQUIRED COMPONENTS chrono thread unit_test_framework)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/dd
    ${Boost_INCLUDE_DIRS}
)

set(SOURCE_FILES
    main.cpp
    FileWatcherTest.cpp
    ComponentCopyTest.cpp
)

add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests
    daydream
    ${Boost_LIBRARIES}
)