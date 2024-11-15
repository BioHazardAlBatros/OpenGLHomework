#pragma once
#include "Material.h"

class PhongMaterialWithTexture final: public Material
{
private:
	std::shared_ptr<Texture> texture;
public:
	PhongMaterialWithTexture();
	PhongMaterialWithTexture(std::string sourcePath);
	PhongMaterialWithTexture(std::string textureSourcePath, int);
	PhongMaterialWithTexture(std::string materialSourcePath, std::string textureSourcePath);
	PhongMaterialWithTexture(std::string materialSourcePath, std::shared_ptr<Texture> sharedTex);

	void SetTexture(std::shared_ptr<Texture> texture);
	void Apply();
};