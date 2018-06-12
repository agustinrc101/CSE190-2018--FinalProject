#include "Transform.h"

Transform::Transform()
{
	M = glm::mat4(1.0f);
	totalRot = glm::mat4(1.0f);
	totalTrans = glm::mat4(1.0f);
	totalScale = glm::mat4(1.0f);
}

Transform::Transform(glm::mat4 M)
{
	this->M = M;
	totalRot = glm::mat4(1.0f);
	totalTrans = glm::mat4(1.0f);
	totalScale = glm::mat4(1.0f);
}

Transform::~Transform()
{
	delete(collider);
	delete(motionState);
	delete(rigidbody);


	std::list<Node*>::iterator it = children.begin();
	std::list<Node*>::iterator end = children.end();
	for (it; it != end; ++it)
	{
		if(!(*it)->isManualDelete())
		{
			delete (*it);
		}
	}
}

int Transform::draw(glm::mat4 C, Shader* shaderProgram, int n)
{
	glm::mat4 totalTransformation = C * totalTrans * totalRot * M * extraRot * totalScale;
	
	std::list<Node*>::iterator it = children.begin();
	std::list<Node*>::iterator end = children.end();
	for (it; it != end; ++it)
	{
		n = (*it)->draw(totalTransformation, shaderProgram, n);
        ++n;
	}
    return n;
}

void Transform::update()
{
	//Do regular stuff
	if (animate)
	{
		M = animate(M);
	}
	std::list<Node*>::iterator it = children.begin();
	std::list<Node*>::iterator end = children.end();
	for (it; it != end; ++it)
	{
		(*it)->update();
	}
}

Transform& Transform::addChild(Node* node)
{
	if(node != NULL)
	{
		children.push_back(node);
	}
	return *this;
}

Transform& Transform::removeChild(Node * node)
{
	children.remove(node);
	return *this;
}

Transform& Transform::translate(float x, float y, float z)
{
	totalTrans = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * totalTrans;
	return *this;
}

Transform& Transform::translate(glm::vec3 trans)
{
	totalTrans = glm::translate(glm::mat4(1.0f), trans) * totalTrans;
	return *this;
}

Transform& Transform::scale(float amount)
{
	totalScale = glm::scale(glm::mat4(1.0f), glm::vec3(amount, amount, amount)) * totalScale;
	return *this;
}

Transform& Transform::scale(float x, float y, float z)
{
	totalScale = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z)) * totalScale;
	return *this;
}

Transform& Transform::rotate(glm::vec3 rotAxis, float deg)
{
	totalRot = glm::rotate(glm::mat4(1.0f), deg / 180.0f * glm::pi<float>(), rotAxis) * totalRot;
	return *this;
}

Transform & Transform::rotate(glm::mat4 M)
{
	totalRot = M * totalRot;
	return *this;
}

Transform& Transform::resetTranslate()
{
	totalTrans = glm::mat4(1.0f);
	return *this;
}

Transform& Transform::resetScale()
{
	totalScale = glm::mat4(1.0f);
	return *this;
}

Transform& Transform::setAnimation(glm::mat4 (*animate)(glm::mat4 M))
{
	this->animate = animate;
	return *this;
}

glm::mat4 Transform::getToWorld(glm::mat4 C)
{
	return C * totalTrans * totalRot * M;//totalScale;
}

glm::vec3 Transform::getForwardVector() {
	glm::mat4 m = totalTrans * totalRot * M * extraRot;
	return glm::normalize(glm::vec3(children.back()->getToWorld(m)[3]) - glm::vec3(m[3]));
}

//BULLET PHYSICS FUNCTIONS
void Transform::setCollisionShapeSphere(float radius) {
	collider = new btSphereShape(radius);
	glm::vec3 pos = totalTrans[3];
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));
	mass = 1;
	btVector3 fallInertia(0, 0, 0);
	collider->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo  rigidbodyCI(mass, motionState, collider, fallInertia);
	rigidbody = new btRigidBody(rigidbodyCI);
}

void Transform::setCollisionShapeCylinder(btVector3 halfExtents) {
	collider = new btCylinderShape(btVector3(0.125f, .25f, 0.125f));
	glm::vec3 pos = totalTrans[3];
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));
	mass = 1;
	btVector3 fallInertia(0, 0, 0);
	collider->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo  rigidbodyCI(mass, motionState, collider, fallInertia);
	rigidbody = new btRigidBody(rigidbodyCI);

	int * i = &id;
	collider->setUserPointer(i);
}

void Transform::setCollisionShapePlane(btVector3 planeNormal) {
	glm::vec3 pos = totalTrans[3];
	collider = new btStaticPlaneShape(planeNormal, pos.y);
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));
	btRigidBody::btRigidBodyConstructionInfo rigidbodyCI(0, motionState, collider, btVector3(0, 0, 0));
	rigidbody = new btRigidBody(rigidbodyCI);
}

btRigidBody * Transform::getRigidbody() {
	return rigidbody;
}

void Transform::setToWorld(glm::mat4 m, bool useBullet) {
	M = m ;

	totalRot = glm::mat4(1.0f);
	totalTrans = glm::mat4(1.0f);
	
	if (useBullet) {
		btScalar t[16];

		int counter = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				t[counter] = m[i][j];
				counter++;
			}
		}

		btTransform transform;
		transform.setFromOpenGLMatrix(t);
		rigidbody->getMotionState()->setWorldTransform(transform);
		rigidbody->setWorldTransform(transform);
	}
}