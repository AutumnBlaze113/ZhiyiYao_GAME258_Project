#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, float specular_, glm::vec3 colour_)
{
	position = position_;
	ambient = ambient_;
	diffuse = diffuse_;
	specular = specular_;
	colour = colour_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition()
{
	return position;
}

float LightSource::GetAmbient()
{
	return ambient;
}

float LightSource::GetDiffuse()
{
	return diffuse;
}

float LightSource::GetSpecular()
{
	return specular;
}

glm::vec3 LightSource::GetColour()
{
	return colour;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetAmbient(float ambient_)
{
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_)
{
	diffuse = diffuse_;
}

void LightSource::SetSpecular(float specular_)
{
	specular = specular_;
}

void LightSource::SetColour(glm::vec3 colour_)
{
	colour = colour_;
}
