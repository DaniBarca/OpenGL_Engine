#include "Color.h"

Color::Color() : glm::vec4()
{}

Color::Color(glm::vec4 v) : glm::vec4(v) {}
Color::Color(glm::vec3 v) : glm::vec4(v.x,v.y,v.z,1.0f) {}
Color::Color(float x, float y, float z) : Color(x, y, z, 1.0f) {}
Color::Color(float x, float y, float z, float t) : glm::vec4(x, y, z, t) {}

Color::~Color()
{
}

Color Color::clamp() {
	return Color(x*I_256, y*I_256, z*I_256, t);
}
