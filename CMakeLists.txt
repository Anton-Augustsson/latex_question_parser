cmake_minimum_required(VERSION 3.26)

project(
  LatexQuestionParser
  VERSION 1.0
  LANGUAGES CXX)

enable_testing()

set(path_test_file "${CMAKE_SOURCE_DIR}/unit_tests/test_file.tex")

add_executable(Parse main.cpp)
add_executable(ParseDebug main.cpp)
add_executable(Tests unit_tests/tests.cpp)

target_compile_options(ParseDebug PRIVATE -g)

add_test(NAME TestParse COMMAND Parse "f" "${path_test_file}" "s")

add_custom_target(run 
  COMMAND Parse "f" "${path_test_file}"
  DEPENDS Parse
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running Parse with example file"
)

add_custom_target(unit_test
  COMMAND Tests
  DEPENDS Tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running Tests"
)

add_custom_target(debug
  COMMAND "gdb" "--args" ParseDebug "f" "${path_test_file}"
  DEPENDS ParseDebug
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running gdb on Parse"
)

