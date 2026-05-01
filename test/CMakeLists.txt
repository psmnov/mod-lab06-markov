add_executable(${PROJECT_NAME}.test
  AllTests.cpp
  tests.cpp)
target_link_libraries(${PROJECT_NAME}.test
  ${PROJECT_NAME}
  gtest
  gtest_main
)
# pthread только на Linux/Mac
if(UNIX)
  target_link_libraries(${PROJECT_NAME}.test pthread)
endif()
target_compile_definitions(${PROJECT_NAME}.test 
  PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test")

install(TARGETS ${PROJECT_NAME}.test
        DESTINATION "${tool_dest}")
