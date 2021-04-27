#include "OctspatialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 position_, float size_, OctNode* parent_)
	: octBounds(nullptr), parent(nullptr), children(), 
	objectList(std::vector<GameObject*>())
{
	objectList.reserve(10);

	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;

	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		children[i] = nullptr;
	}
}

OctNode::~OctNode()
{
	//std::cout << "There are " << GetChildCount() << " child nodes" << std::endl;
	if (octBounds != nullptr) {
		delete octBounds;
		octBounds = nullptr;
	}
	

	if (objectList.size() > 0) {
		for (auto obj : objectList) {
			obj = nullptr;
		}
		objectList.clear();
	}

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		if (children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth_)
{
	if (depth_ > 0 && this) {
		float half = size / 2.0f;
		children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(
			glm::vec3(octBounds->minVert.x, // x y+ z+
				octBounds->minVert.y + half,
				octBounds->minVert.z + half), half, this);
		//New!
		children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(
			glm::vec3(octBounds->minVert.x, // x y z+
				octBounds->minVert.y,      
				octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, // x+ y z+
				octBounds->minVert.y,
				octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, // x+ y+ z+
				octBounds->minVert.y + half,
				octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(
			glm::vec3(octBounds->minVert.x, // x y+ z
				octBounds->minVert.y + half,
				octBounds->minVert.z), half, this);

		children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(
			glm::vec3(octBounds->minVert.x,  // x y z
				octBounds->minVert.y,
				octBounds->minVert.z), half, this);

		children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, // x+ y z
				octBounds->minVert.y,
				octBounds->minVert.z), half, this);

		children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, // x+ y+ z
				octBounds->minVert.y + half,
				octBounds->minVert.z), half, this);

		childNum += 8;
	}

	if (depth_ > 0 && this) {
		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			children[i]->Octify(depth_ - 1);
		}
	}
	
}

OctNode* OctNode::GatParent()
{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)
{
	return children[static_cast<int>(childPos_)];
}

void OctNode::AddCollisionObject(GameObject* obj_)
{
	objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

bool OctNode::IsLeaf() const
{
	if (children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const
{
	return octBounds;
}

int OctNode::GetChildCount() const
{
	return childNum;
}

OctspatialPartition::OctspatialPartition(float worldSize_)
	: root(nullptr), rayIntersectionList(std::vector<OctNode*>())
{
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " child nodes" << std::endl;

	rayIntersectionList.reserve(20);
}

OctspatialPartition::~OctspatialPartition()
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}

void OctspatialPartition::AddObject(GameObject* obj_)
{
	AddObjectToCell(root, obj_);
}

GameObject* OctspatialPartition::GetCollision(Ray ray_)
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	PrepareCollisionQuery(root, ray_);
	GameObject* result = nullptr;
	float shorttestDistance = FLT_MAX;
	for (auto cell : rayIntersectionList) {
		for (auto obj : cell->objectList) {
			if (ray_.IsColliding(&obj->GetBoundingBox())) {
				if (ray_.intersectionDist < shorttestDistance) {
					result = obj;
					shorttestDistance = ray_.intersectionDist;
				}
			}
		}
		if (result != nullptr) {
			return result;
		}
	}
	
	return nullptr;
}

// New!
void OctspatialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_)
{
	//OctChildren temp;
	// check if the specific node that is passed in
	//If it is a leaf node, it will check to see if the GameObject's BoundingBox collides with that node's bounding box
	//If those 2 BoundingBox collide or they intersect, then the GameObject gets added to that node;
	if (cell_->IsLeaf()) {
		if (obj_->GetBoundingBox().Intersects(cell_->GetBoundingBox())) {
			cell_->AddCollisionObject(obj_);
			// When actually add a node (leaf node), prints out that specific GameObject (node's positions) 
			std::cout << "Add " << obj_->GetTag() << " to cell vec3( " <<
				obj_->GetPosition().x << ", " <<
				obj_->GetPosition().y << ", " <<
				obj_->GetPosition().z << ") " << std::endl;
				
		}

	}
	
	//If not a leaf node, there is a for loop where it goes each of that (child nodes)
	// recursively calls the function on each child
	else {
		//for (auto child : temp)
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_BLF), obj_);
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_BLR), obj_);
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_BRF), obj_);
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_BRR), obj_);
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_TLF), obj_);
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_TLR), obj_);
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_TRF), obj_);
		AddObjectToCell(cell_->GetChild(OctChildren::OCT_TRR), obj_);
		}	
}

void OctspatialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{
	//If it is a leaf node, it checks if the ray_ intersects with that node's bounding box
	//true - node added to rayIntersectionList
	if (cell_->IsLeaf()) {
		if (ray_.IsColliding(cell_->GetBoundingBox())) {
			rayIntersectionList.push_back(cell_);
		}
	}
	//If it is not a leaf node, for loop where goes each of that (child nodes) and call to each child node
	else {
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_BLF), ray_);
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_BLR), ray_);
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_BRF), ray_);
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_BRR), ray_);
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_TLF), ray_);
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_TLR), ray_);
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_TRF), ray_);
		PrepareCollisionQuery(cell_->GetChild(OctChildren::OCT_TRR), ray_);
	}

}
