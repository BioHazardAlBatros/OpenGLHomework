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

	if(jsonFile.GetParseError()!=0)
	{
		//https://rapidjson.org/group___r_a_p_i_d_j_s_o_n___e_r_r_o_r_s.html#ga7d3acf640886b1f2552dc8c4cd6dea60
		std::cerr << jsonFile.GetParseError()<<std::endl;
		return false;
	}
	
	for (auto& type : jsonFile.GetObject())
	{
		std::cout << '\n'<<type.name.GetString() << ':';
//		if (!type.value.HasMember("material") || !type.value.HasMember("mesh")) break;
		//to do: figure out how to use exclude mesh copies
		Meshes.emplace_back(std::make_shared<Mesh>(jsonFile[type.name]["mesh"].GetString()));

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
		//what the fuck?
	}
	std::endl(std::cout<<std::endl); //https://www.youtube.com/watch?v=GS1-255aj3c

	//	Materials[1] = (std::make_shared<Material>(R"(assets\materials\mat2.txt)"));//Blue Shiny  <--- fuck you

	chambox.SetMesh(Meshes[GameObjectType::LIGHT_OBJECT]);
	chambox.SetMaterial(Materials[GameObjectType::LIGHT_OBJECT]);

	graybox.SetMesh(Meshes[GameObjectType::HEAVY_OBJECT]);
	graybox.SetMaterial(Materials[GameObjectType::HEAVY_OBJECT]);

	darkbox.SetMesh(Meshes[GameObjectType::BORDER]);
	darkbox.SetMaterial(Materials[GameObjectType::BORDER]);

	sphere.SetMesh(Meshes[GameObjectType::PLAYER]); 
	sphere.SetMaterial(Materials[GameObjectType::PLAYER]);
	return true;
};
std::shared_ptr<GameObject> GameObjectFactory::Create(GameObjectType type, glm::vec2 pos) 
{
	std::shared_ptr<GameObject> newObject = std::make_shared<GameObject>();
	newObject->SetPosition(pos);
	switch (type)
	{
		default:break;
		case BORDER: 
			newObject->SetGraphicObject(darkbox);
			break;
		case LIGHT_OBJECT:
			newObject->SetGraphicObject(chambox);
			break;
		case HEAVY_OBJECT:
			newObject->SetGraphicObject(graybox);
			break;
		case ENEMY: break;
		case PLAYER: 
			newObject->SetGraphicObject(sphere);
			break;
		case BOMB: break;

	}
	return newObject; 
}
std::shared_ptr<GameObject> GameObjectFactory::Create(GameObjectType type, int x, int y) 
{
	std::shared_ptr<GameObject> newObject = std::make_shared<GameObject>();
	switch (type)
	{
	default:break;
	case BORDER:
		newObject->SetGraphicObject(darkbox);
		break;
	case LIGHT_OBJECT:
		newObject->SetGraphicObject(chambox);
		break;
	case HEAVY_OBJECT:
		newObject->SetGraphicObject(graybox);
		break;
	case ENEMY: break;
	case PLAYER: 
		newObject->SetGraphicObject(sphere);
		break;
	case BOMB: break;
	}
	newObject->SetPosition({ x,y });
	return newObject;

}