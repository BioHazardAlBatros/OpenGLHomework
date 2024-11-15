#pragma once
#include "Material.h"

class PhongMaterial final : public Material
{
public:
	PhongMaterial();
	PhongMaterial(std::string sourcePath);
	void Apply();
};