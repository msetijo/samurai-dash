#include "Math.h"

#include <glm/glm.hpp>

using namespace glm;
using namespace math;

vec3 math::anyBasis(vec3 v) {

	vec3 i = vec3(1, 0, 0);
	vec3 j = vec3(0, 1, 0);

	return abs(dot(v, i)) <= abs(dot(v, j)) ? i : j;
}

vec3 math::anyOrthogonalVector(vec3 v) {

	return normalize(cross(v, anyBasis(v)));
}