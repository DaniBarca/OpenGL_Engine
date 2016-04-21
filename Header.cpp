#include "Header.h"
#include <fstream>

glm::mat4 getRotationMatrix(double radians, glm::vec3 axis)
{
	axis = glm::normalize(axis);

	glm::mat4 m = glm::mat4(1.0f); //Identity matrix

	double c = cos(radians);
	double s = sin(radians);
	double t = 1 - c;

	m[0][0] = ((float)(t * axis[0] * axis[0] + c));
	m[1][0] = ((float)(t * axis[0] * axis[1] - s * axis[2]));
	m[2][0] = ((float)(t * axis[0] * axis[2] + s * axis[1]));

	m[0][1] = ((float)(t * axis[0] * axis[1] + s * axis[2]));
	m[1][1] = ((float)(t * axis[1] * axis[1] + c));
	m[2][1] = ((float)(t * axis[1] * axis[2] - s * axis[0]));

	m[0][2] = ((float)(t * axis[0] * axis[2] - s * axis[1]));
	m[1][2] = ((float)(t * axis[1] * axis[2] + s * axis[0]));
	m[2][2] = ((float)(t * axis[2] * axis[2] + c));

	return m;
}
