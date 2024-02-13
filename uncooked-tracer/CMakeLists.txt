# CMakeList.txt : CMake project for uncooked-tracer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (uncooked-tracer "uncooked-tracer.cpp"  "vec3.h" "colour.h" "ray.h" "hittable.h" "sphere.h" "hittableList.h" "uncooked-tracer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET uncooked-tracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
