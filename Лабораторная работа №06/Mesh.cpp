#include "Mesh.h"

class Mesh
{
	private:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texPos;
	};
	std::vector<Vertex> vertices;
	public:
		void LoadFromFile(std::string sourcePath)
		{
			std::ifstream File(sourcePath);
			if (!File)
			{
				std::cerr << "\nFailed to load from " << sourcePath;
				return;
			}

			std::cout << "\nLoading mesh data from " << sourcePath << '\n';
			std::string currentFieldName;
			std::vector<glm::vec3> vert;
			std::vector<glm::vec3> norm;
			std::vector<glm::vec2> tex;
			std::vector<glm::ivec3> fPoints;
		}
	void Draw();

};