#pragma once

//OpenGL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
//Bullet Physics
#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
//std
#include <iostream>
#include <list>
#include <vector>
//our scripts
#include "shader.h"
#include "Skybox.h"
#include "Transform.h"
#include "Geometry.h"
#include "FilepathsAndDefinitions.h"
#include "UsefulFunctions.h"

class Scene{
public:
	Scene();
	~Scene();

	void update(float deltaTime);
	void drawStaticObjects(glm::mat4 projection, glm::mat4 modelview, Shader* shaderProgram);
	void drawObjects(glm::mat4 projection, glm::mat4 modelview, Shader* shaderProgram, Shader* colorShader, int indexL, int indexR);

	std::vector<glm::vec3> getListOfPositions();
	glm::mat4 getObjMatrix(int index);
	void setObjMatrix(int index, glm::mat4 m);
	void resetObj(int index);
	glm::vec3 getForwardVector(int index);
	glm::vec3 getPosition(int index);
	
	glm::vec3 shootRaycast(glm::vec3 dir, glm::vec3 pos);
	bool removeLastHit(int index);
	bool getCheckIfHit(int index);
	void resetCans();
	void setRigitBody(btRigidBody * rb);

	int lastHit = -1;

private:
	//BulletPhysicsVars
	btBroadphaseInterface * broadphase;
	btDefaultCollisionConfiguration * collisionConfiguration;
	btCollisionDispatcher * dispatcher;
	btSequentialImpulseConstraintSolver * solver;
	btDiscreteDynamicsWorld * dynamicsWorld;
	

	//Objects
	std::vector<Transform*> staticObjects;
	std::vector<Transform*> objects;
	std::vector<Transform*> cans;

	//Init functions
	void initBullet();
	void initObjects();

	bool drawCan[15];
};

