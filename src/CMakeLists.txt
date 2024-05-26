set(target ${MP2_CUSTOM})

file(GLOB hdrs "*.cpp*")

add_custom_target(${target} SOURCES ${hdrs})