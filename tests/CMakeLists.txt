add_executable (effects effects.cpp)
add_executable (mixer mixer.cpp)
add_executable (localtest test.cpp)

target_link_libraries(effects tsal)
target_link_libraries(mixer tsal)
target_link_libraries(localtest tsal)

enable_testing()
add_test(MyEffectsTest effects)
add_test(MyMixerTest mixer)
add_test(MyTest localtest)
