#pragma once

#include "Header.h"

class TextureManager
{
	TextureManager();
public:
	static TextureManager* GetInstance();

	TextureManager* LoadImage(GLuint* textureID, char* bytes, unsigned int length);
};

