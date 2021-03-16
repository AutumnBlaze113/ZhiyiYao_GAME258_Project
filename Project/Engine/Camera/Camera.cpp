#include "Camera.h"
#include "../Core/CoreEngine.h"

Camera::Camera()
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView,
		CoreEngine::GetInstance()->GetScreenWidth() /
		CoreEngine::GetInstance()->GetScreenHeight(),
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(),
		0.0f, CoreEngine::GetInstance()->GetScreenHeight(),
		-1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

void Camera::AddLightSource(LightSource* LightSource_)
{
	light.position = LightSource_->GetPosition();
	light.ambient = LightSource_->GetAmbient();
	light.diffuse = LightSource_->GetDiffuse();
	light.specular = LightSource_->GetSpecular();
	light.colour = LightSource_->GetColour();
}

Light Camera::GetLight()
{
	return light;
}

/*
void Camera::AddLightSource(LightSource* LightSource_)
{
	light.reserve(1);
	light.push_back(LightSource_);
}

std::vector<Light>& Camera::GetLightSourceList()
{
	return light;
}
*/




glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::UpdateCameraVectors()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));

	view = glm::lookAt(position, position + forward, up);
}
