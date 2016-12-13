#include "SpotLight.h"

SpotLight::SpotLight(glm::vec4 _color, glm::vec3 _position, float _shininess, float _intensity, glm::vec3 _direction, float _angle, float _angle_soft) : direction(_direction), angle(_angle), angle_soft(_angle_soft), Light(_color, _position, _shininess, _intensity, LIGHT_TYPE::SPOT)
{
	// angle_soft can't be lower than angle
	if ((angle_soft - angle) < 0.0f) {
		angle_soft = angle + 0.00001f;
	}

	// angle_soft must be higher than angle, at least with an irrelevant difference.
	if ((angle_soft - angle) < 0.000001f) {
		angle_soft += 0.00001f;
	}
}

SpotLight::~SpotLight()
{
	Light::~Light();
}

glm::vec3 SpotLight::GetDirection()
{
	return direction;
}

float SpotLight::GetAngle()
{
	return angle;
}

float SpotLight::GetAngleSoft() {
	return angle_soft;
}
