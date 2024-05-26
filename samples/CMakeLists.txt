# Get all cpp-files in the current directory
file(GLOB samples_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


foreach(sample_filename ${samples_list})
  # Get file name without extension
  get_filename_component(sample ${sample_filename} NAME_WE)

  # Add and configure executable file to be produced
  add_executable(${sample} ${sample_filename}
          ../src/Polynomial.cpp
          ../include/LinearMas.h
          ../include/LinearList.h
          ../include/SortedList.h
          ../include/AVLTree.h
          ../src/AVLTree.cpp
          ../src/LinearMas.cpp
          ../src/LinearList.cpp
          ../src/SortedList.cpp
          ../src/SortedList.cpp
          ../include/HashTable.h
  )
  target_link_libraries(${sample} ${MP2_LIBRARY})
  set_target_properties(${sample} PROPERTIES
    OUTPUT_NAME "${sample}"
    PROJECT_LABEL "${sample}"
    RUNTIME_OUTPUT_DIRECTORY "../")
endforeach()