#pragma once

#include "Header.h"

class TextureManager
{
	TextureManager();
public:
	static TextureManager* GetInstance();

	TextureManager* LoadImage(GLuint* texture_buffer, char* bytes, unsigned int length);
};

