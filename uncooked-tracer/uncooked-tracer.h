#ifndef UNCOOKED_TRACER
#define UNCOOKED_TRACER

#include <cmath>
#include <limits>
#include <memory>

//Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility functions

inline double degreesToRadians(double degrees) {
	return degrees * pi / 180.0;
}

// Common headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif