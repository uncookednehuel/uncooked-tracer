# CMakeList.txt : CMake project for RaytracingNehuel1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (RaytracingNehuel1 "RaytracingNehuel1.cpp"  "vec3.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RaytracingNehuel1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
