# find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

# include_directories (${TEST_SOURCE_DIR}/src)

# ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

# add_executable (test test.cpp ${TEST_SOURCE_DIR}/src/sqr.cpp)
# add_executable (test test.cpp ${TEST_SOURCE_DIR}/src/sqr.cpp)
# add_executable (test test.cpp ${TEST_SOURCE_DIR}/src/sqr.cpp)
# add_executable (test test.cpp ${TEST_SOURCE_DIR}/src/sqr.cpp)
add_executable (effects effects.cpp)
add_executable (mixer mixer.cpp)
add_executable (localtest test.cpp)

target_link_libraries(effects tsal)
target_link_libraries(mixer tsal)
target_link_libraries(localtest tsal)

# target_link_libraries(test
#                       ${Boost_FILESYSTEM_LIBRARY}
#                       ${Boost_SYSTEM_LIBRARY}
#                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
#                       )

enable_testing()
add_test(MyEffectsTest effects)
# add_test(MyMixerTest mixer)
# add_test(MyTest localtest)
