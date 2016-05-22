#pragma once

#include "Header.h"
#include "Color.h"

class Material
{
	Color diffuse_color;

public:
	Material();
	Material(Color _diffuse_color);
	~Material();

	Material* setDiffuseColor(Color);
	Color getDiffuseColor();
};

