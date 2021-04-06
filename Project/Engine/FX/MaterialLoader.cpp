#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{

}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}

	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}

		//SHININESS
		if (line.substr(0, 4) == "	Ns ") {
			
			std::stringstream v(line.substr(4));
			float x; 
			v >> x;
			m.shininess = x;
		}

		//TRANSPARENCY
		if (line.substr(0, 3) == "	d ") {
			
			std::stringstream v(line.substr(3));
			float x;
			v >> x;
			m.transparency = x;
		}

		//AMBIENT
		if (line.substr(0, 4) == "	Ka ") {
			
			std::stringstream v(line.substr(4));
			float x, y, z;
			v >> x >> y >> z;
			m.ambient = glm::vec3(x,y,z);
		}


		//DIFFUSE
		if (line.substr(0, 4) == "	Kd ") {
			
			std::stringstream v(line.substr(4));
			float x, y, z;
			v >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}

		//SPECULAR
		if (line.substr(0, 4) == "	Ks ") {
			
			std::stringstream v(line.substr(4));
			float x, y, z;
			v >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}


	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
