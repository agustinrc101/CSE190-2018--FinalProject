#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<list>
#include<glm/gtc/matrix_transform.hpp>
#include<stack>
#include <btBulletDynamicsCommon.h>
#include"Node.h"
#include"shader.h"
#include "ShaderLoader.h"

enum SHAPE {
	PLANE = 0,
	SPHERE = 1,
	RECTANGLE = 2,
};

class Transform : public Node
{
public:
	Transform();
	Transform(glm::mat4 M);
	~Transform();
	int draw(glm::mat4 C, Shader* shaderProgram, int n = 0);
	void update();
	Transform& addChild(Node* node);
	Transform& removeChild(Node* node);
	Transform& translate(float x, float y, float z);
	Transform& translate(glm::vec3 trans);
	Transform& scale(float amount);
	Transform& scale(float x, float y, float z);
	Transform& rotate(glm::vec3 rotAxis, float deg);
	Transform& rotate(glm::mat4 M);
	Transform& resetTranslate();
	Transform& resetScale();
	Transform& setAnimation(glm::mat4 (*animate)(glm::mat4 M));
	glm::mat4 getToWorld(glm::mat4 C = glm::mat4(1.0f)) final;

	glm::vec3 getForwardVector();
	void setToWorld(glm::mat4 m);
	glm::mat4 extraRot = glm::mat4(1.0f);

	//BulletPhysics
	btCollisionShape * collider;
	btDefaultMotionState * motionState;
	btRigidBody * rigidbody;
	btScalar mass;

	void setCollisionShapeSphere(float radius);
	void setCollisionShapePlane(btVector3 planeNormal = btVector3(0, 1, 0));

	btRigidBody * getRigidbody();

protected:

private:
	glm::mat4 M; //Transformation Matrix
	glm::mat4 totalRot;
	glm::mat4 totalTrans;
	glm::mat4 totalScale;
	std::list<Node*> children;
	glm::mat4 (*animate)(glm::mat4 M);
};



#endif
