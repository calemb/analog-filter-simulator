# Check version, set project name and language
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(cpp_project LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Add program targets
add_executable(test_filters app/test_filters.cpp)
add_executable(filter_simulator app/filter_simulator.cpp)

# Set variables
set(project_headers include/ra/filters.hpp)
set(project_sources )

# Add library
add_library(project ${project_sources} ${project_headers})
set_target_properties(project PROPERTIES LINKER_LANGUAGE CXX)

# Specify include directory
target_include_directories(project PUBLIC include "/include")

# Link programs to library
target_link_libraries(test_filters project)
target_link_libraries(filter_simulator project)

# Install location
install(TARGETS test_filters DESTINATION bin)
install(TARGETS filter_simulator DESTINATION bin)
install(TARGETS project DESTINATION lib)
install(FILES demo DESTINATION bin PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)

# Run sanitizers
include(Sanitizers.cmake)

# Run $ cmake -H. -Btmp -DCMAKE_INSTALL_PREFIX=tmp/install
# Run $ cmake --build tmp --target install
# Run $ cmake --build tmp --clean-first --target install