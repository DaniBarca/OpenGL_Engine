#include "RotatingLight.h"

RotatingLight::RotatingLight(glm::vec4 _color, glm::vec3 position, float _shininess, float _intensity) : Light(_color, position, _shininess, _intensity)
{
}

RotatingLight::~RotatingLight()
{
}

RotatingLight::RotatingLight(const RotatingLight & l) : Light(l)
{}

void RotatingLight::Update(double dt) {
	static double t = 0;
	t += dt * 1.5f;
	if (t > TAU)
		t = 0;

	SetPosition(glm::vec3(
		glm::sin(t) * 0.5f,
		0.5f,
		glm::cos(t) * 0.5f
	));
}
