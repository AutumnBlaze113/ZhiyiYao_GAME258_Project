#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"

struct Light
{
	glm::vec3 position;
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 colour;
};

class Camera
{
public: 
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	//Frustum GetPerspectiveFrustum() const;
	float GetNearPlane() const;
	float GetFarPlane() const;

	void AddLightSource(LightSource* LightSource_);
	//std::vector<LightSource>& GetLightSourceList();
	Light GetLight();
	

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

private:
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	Light light;
	//std::vector<LightSource> light;
};


#endif // !CAMERA_H


