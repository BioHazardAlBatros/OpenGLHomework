#include "GameObjectFactory.h"
bool GameObjectFactory::Init(std::string sourcePath) 
{
	std::ifstream File(sourcePath);

	if (!File)
	{
		std::cerr << "\nFailed to load from " << sourcePath;
		return false;
	}

	rapidjson::IStreamWrapper buffer(File);
	rapidjson::Document jsonFile;
	jsonFile.ParseStream(buffer);
	File.close();
	if(jsonFile.GetParseError()!=0)
	{
		//https://rapidjson.org/group___r_a_p_i_d_j_s_o_n___e_r_r_o_r_s.html#ga7d3acf640886b1f2552dc8c4cd6dea60
		std::cerr << jsonFile.GetParseError()<<std::endl;
		return false;
	}

//	std::set<std::string> MeshPaths;
	for (auto& type : jsonFile.GetObject())
	{
		std::cout << '\n'<<type.name.GetString() << ':';
		//auto MeshPtr = MeshPaths.find(type.name.GetString());
		//if (MeshPtr == MeshPaths.end())
			Meshes.emplace_back(std::make_shared<Mesh>(jsonFile[type.name]["mesh"].GetString()));
		//else
		//	Meshes.emplace_back(Meshes[0]);
		//MeshPaths.insert(type.name.GetString()); |to do

		std::cout << "Getting material data:\n";
		Materials.emplace_back(std::make_shared<Material>());
		auto tempArr = jsonFile[type.name]["material"]["diffuse"].GetArray();
		Materials.back()->SetDiffuse({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble()});

		tempArr = jsonFile[type.name]["material"]["ambient"].GetArray();
		Materials.back()->SetAmbient({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble() });
		
		tempArr = jsonFile[type.name]["material"]["specular"].GetArray();
		Materials.back()->SetSpecular({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble() });
		
		tempArr = jsonFile[type.name]["material"]["emission"].GetArray();
		Materials.back()->SetEmission({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble() });
		
		Materials.back()->SetShininess(jsonFile[type.name]["material"]["shininess"].GetDouble());
	}
	std::endl(std::cout<<std::endl); //https://www.youtube.com/watch?v=GS1-255aj3c
	return true;
};
std::shared_ptr<GameObject> GameObjectFactory::Create(GameObjectType type, glm::vec2 pos) 
{
	std::shared_ptr<GameObject> newObject = std::make_shared<GameObject>();
	GraphicObject graphObj;
	graphObj.SetMesh(Meshes[type]);
	graphObj.SetMaterial(Materials[type]);
	newObject->SetPosition(pos);
	newObject->SetGraphicObject(graphObj);
	return newObject; 
}
std::shared_ptr<GameObject> GameObjectFactory::Create(GameObjectType type, int x, int y) 
{
	std::shared_ptr<GameObject> newObject = std::make_shared<GameObject>();
	GraphicObject graphObj;
	graphObj.SetMaterial(Materials[type]);
	graphObj.SetMesh(Meshes[type]);
	newObject->SetPosition({ x,y });
	newObject->SetGraphicObject(graphObj);
	return newObject;
}