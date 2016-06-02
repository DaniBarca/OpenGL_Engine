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

// Credit for this function goes to Michael Mrozek -- http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}
