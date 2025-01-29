# List all executables.
file(
  GLOB app_files .
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "*.cpp")

# Create executables for each file.
foreach(file IN LISTS app_files)
  string(REPLACE ".cpp" "" name ${file})
  message(STATUS "Adding executable ${name}")
  add_executable(${name} ${file})
  target_link_libraries(${name} utils)
endforeach()
