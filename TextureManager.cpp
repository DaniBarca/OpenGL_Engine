#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureManager* TextureManager::LoadImage(GLuint* textureID, char* bytes, unsigned int length) {
	unsigned char *image;
	int width = 0;
	int height = 0;
	int comp = 0;
	image = stbi_load_from_memory((stbi_uc*)bytes, (int)length, &width, &height, &comp, STBI_rgb);

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);

	return GetInstance();
}

TextureManager::TextureManager()
{
}

TextureManager * TextureManager::GetInstance()
{
	static TextureManager* Instance = new TextureManager();
	return Instance;
}
