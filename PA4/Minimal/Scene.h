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
	void draw(glm::mat4 projection, glm::mat4 modelview, Shader* shaderProgram);

private:
	//BulletPhysicsVars
	btBroadphaseInterface * broadphase;
	btDefaultCollisionConfiguration * collisionConfiguration;
	btCollisionDispatcher * dispatcher;
	btSequentialImpulseConstraintSolver * solver;
	btDiscreteDynamicsWorld * dynamicsWorld;
	

	//Objects
	std::list<Transform*> staticObjects;
	std::list<Transform*> objects;

	//Init functions
	void initBullet();
	void initObjects();
};

