#include "Texture.h"

void Texture::DisableAll() 
{
	glDisable(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadFromFile(std::string sourcePath)
{
	wchar_t unicodeStr[256];
	ILuint imageID = ilGenImage();
	ilBindImage(imageID);

	wsprintf(unicodeStr, L"%S", sourcePath.c_str());
	if (IL_FALSE == ilLoadImage(unicodeStr))
	{
		std::cerr << "\nFailed to load from " << sourcePath;
		return;
	}
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	int format = ilGetInteger(IL_IMAGE_FORMAT);
	int type = ilGetInteger(IL_IMAGE_TYPE);

	std::vector<BYTE> pixmap(width * height * 3);

	ilCopyPixels(0,0,0,width, height,1,format,type,pixmap.data());
	ilBindImage(0);
	ilDeleteImage(imageID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &this->tIndex);
	glBindTexture(GL_TEXTURE_2D, this->tIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, type, pixmap.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	
}

void Texture::Apply(TextureFilter texFilter) 
{
	glBindTexture(GL_TEXTURE_2D, tIndex);

	switch (texFilter) {
	case TextureFilter::POINT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;

	case TextureFilter::BILINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;

	case TextureFilter::TRILINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;

	case TextureFilter::ANISOTROPIC:
		GLfloat anisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
		break;
	}
}