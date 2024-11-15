#pragma once
#include "Material.h"

class PhongMaterial : public Material
{
public:
	PhongMaterial();
	PhongMaterial(std::string sourcePath);
	void Apply();
};