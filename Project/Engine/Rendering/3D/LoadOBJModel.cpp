#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel()
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureCoords.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMesh()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();;
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	boundingBox.maxVert = glm::vec3(-1.0f, -1.0f, -1.0f);
	boundingBox.minVert = glm::vec3(1.0f, 1.0f, 1.0f);
	std::string line;

	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			if (x > boundingBox.maxVert.x) {
				boundingBox.maxVert.x = x;
			}
			if (y > boundingBox.maxVert.y) {
				boundingBox.maxVert.y = y;
			}
			if (z > boundingBox.maxVert.z) {
				boundingBox.maxVert.z = z;
			}

			if (x < boundingBox.minVert.x) {
				boundingBox.minVert.x = x;
			}
			if (y < boundingBox.minVert.y) {
				boundingBox.minVert.y = y;
			}
			if (z < boundingBox.minVert.z) {
				boundingBox.minVert.z = z;
			}
			
		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream n(line.substr(3));
			float x, y, z;
			n >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXCOORDS DATA
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream t(line.substr(3));
			float x, y, z;
			t >> x >> y >> z;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA
		else if (line.substr(0, 2) == "f ") {
			std::string a = line;
			std::replace(a.begin(), a.end(), '/', ' ');
			std::stringstream f(a.substr(2));
			unsigned int x1, y1, z1, x2, y2, z2, x3, y3, z3;
			f >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			indices.push_back(x1-1);// array starts at 0
			indices.push_back(x2-1);
			indices.push_back(x3-1);

			textureIndices.push_back(y1 - 1);
			textureIndices.push_back(y2 - 1);
			textureIndices.push_back(y3 - 1);

			normalIndices.push_back(z1 - 1);
			normalIndices.push_back(z2 - 1);
			normalIndices.push_back(z3 - 1);
		}

		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMatrial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
