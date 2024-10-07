#include "Mesh.h"
		Mesh::Mesh() = default;
		Mesh::Mesh(std::string sourcePath)
		{
			this->LoadFromFile(sourcePath);
		}
		void Mesh::LoadFromFile(std::string sourcePath)
		{
			//Parsing OBJ File data (all fields should be present though)
			std::ifstream File(sourcePath);
			if (!File)
			{
				std::cerr << "\nFailed to load from " << sourcePath;
				return;
			}

			std::cout << "\nLoading mesh data from " << sourcePath << '\n';
			std::vector<glm::vec3> vert;
			std::vector<glm::vec3> norm;
			std::vector<glm::vec2> tex;
			std::vector<glm::ivec3> fPoints;
			int vertCount=0, normCount=0, texCount=0, facesCount=0;

			enum Field {VERTEXPOS,NORMAL, TEXPOS,FACE,NONE} currentField;
			while (!File.eof())
			{
				std::string str,currentFieldName;
				std::getline(File, str, '\n');
				std::istringstream currentLine(str);

				currentField = NONE;
				currentLine >> currentFieldName;
				
				if (currentFieldName == "v")  currentField = VERTEXPOS;
				if (currentFieldName == "vn") currentField = NORMAL;
				if (currentFieldName == "vt") currentField = TEXPOS;
				if (currentFieldName == "f")  currentField = FACE;

				if (currentField == NONE) continue;
		//		std::cout << currentFieldName << ' ';

				switch (currentField)
				{
					case VERTEXPOS:
						vert.emplace_back(); ++vertCount;
						currentLine >> vert.back().x 
									>> vert.back().y 
									>> vert.back().z;
		//				std::cout << vert.back().x << ' ' <<vert.back().y << ' ' << vert.back().z << '\n';
						break;
					case NORMAL:
						norm.emplace_back(); ++normCount;
						currentLine >> norm.back().x 
									>> norm.back().y 
									>> norm.back().z;
		//				std::cout << norm.back().x << ' '  << norm.back().y << ' ' << norm.back().z << '\n';

						break;
					case TEXPOS:
						float discard; //third coordinate usually equals zero
						tex.emplace_back(); ++texCount;
						currentLine >> tex.back().x 
									>> tex.back().y >> discard;
		//				std::cout << tex.back().x << ' '  << tex.back().y << ' ' << discard << '\n';
						break;
					case FACE:
						while(!currentLine.eof())
						{
							fPoints.emplace_back();
							char discard; // used to store '/' symbol 
							currentLine >> fPoints.back()[0] >> discard
										>> fPoints.back()[1] >> discard
										>> fPoints.back()[2];

							if (fPoints.back() == glm::ivec3())
							{
								fPoints.pop_back();
								break;
							}
		//					std::cout  << fPoints.back()[0] << '/' << fPoints.back()[1] << '/' << fPoints.back()[2] << ' ';
						}
						++facesCount;
		//				std::cout << '\n';
						break;
				}
			}
			std::cout << vertCount << " vertices, " << normCount << " vertex normals, " << texCount << " texture coords, " << facesCount << " faces loaded."<<std::endl;

			vertices.reserve(fPoints.size());
			for (glm::ivec3& index : fPoints)
			{
				vertices.emplace_back();

				vertices.back().pos	   = vert[index[0]-1];
				vertices.back().texPos =  tex[index[1]-1];
				vertices.back().normal = norm[index[2]-1];
			}
		}
		void Mesh::Draw() 
		{
			if (vertices.size() == 0) return;
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			
			glVertexPointer  (3, GL_FLOAT, sizeof(Vertex), glm::value_ptr(vertices[0].pos));
			glNormalPointer  (GL_FLOAT,	   sizeof(Vertex), glm::value_ptr(vertices[0].normal));
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), glm::value_ptr(vertices[0].texPos));
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);

		};