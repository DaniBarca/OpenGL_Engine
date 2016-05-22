#include "Light.h"

Light::Light(Color _color, float _intensity) : Object3D(), color(_color), intensity(_intensity)
{}

Light::~Light()
{}

void Light::Update(double dt) {
	Object3D::Update(dt);
}
