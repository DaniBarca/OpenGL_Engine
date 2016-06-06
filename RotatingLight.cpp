#include "RotatingLight.h"

RotatingLight::RotatingLight(glm::vec4 _color, glm::vec3 position, float _intensity) : Light(_color, position, _intensity)
{
}

RotatingLight::~RotatingLight()
{
}

RotatingLight::RotatingLight(const RotatingLight & l) : Light(l)
{}

void RotatingLight::Update(double dt) {
	static double t = 0;
	t += dt * 3.0f;
	if (t > TAU)
		t = 0;

	SetPosition(glm::vec3(
		glm::sin(t) * 15.0f,
		5.0f,
		glm::cos(t) * 15.0f
	));
}
