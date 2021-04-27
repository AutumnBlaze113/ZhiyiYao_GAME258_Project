#ifndef COLLISIONHANDLER
#define COLLISIONHANDLER

#include "Ray.h"
#include "../Rendering/3D/GameObject.h"
#include "../Core/OctspatialPartition.h"

class CollisionHandler
{
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();

	void OnCreate(float worldSize_);
	void AddObject(GameObject* go_);
	void MouseUpdate(glm::vec2 mousePosition_, int buttonType_);
	void OnDestroy();

private: 
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;

	//static std::vector<GameObject*> colliders;
	static std::vector<GameObject*> prevCollisions;
	static OctspatialPartition* scenePartition;
};

#endif

