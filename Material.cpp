#include "Material.h"

Material::Material()
{
	Material(Color(1.0f, 1.0f, 1.0f));
}

Material::Material(Color _diffuse_color) : diffuse_color(_diffuse_color) {

}

Material::~Material()
{}

Material* Material::setDiffuseColor(Color _diffuse_color){
	diffuse_color = _diffuse_color;
	return this;
}

Color Material::getDiffuseColor() {
	return diffuse_color;
}
